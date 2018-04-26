/*
 * File Name: extract.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Wed Apr 25 19:48:30 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 
#include "extract.h"
#include <string>

namespace caseshow{

//@brief 导入过滤关键词
//@param [in]  path : 过滤词汇文本路径
//       [out] myset: 过滤词汇内存镜像
//@return void
//@retval
void Extractor::load_pass_words(std::set<std::string>& myset, const std::string& path)
{
    std::ifstream fin(path.c_str());
    std::string s;  
    while(getline(fin,s))
    {    
        myset.insert(s);
    }
    fin.close();
}

//@brief 判断关键是否包含特殊字眼
//@param [in]  path : 关键词
//@return bool
//@retval true: 关键词包含特殊词汇  false: 关键词不包含特殊词汇
bool Extractor::contain_special_words(std::string str){
    //判断关键词是否包括ascii码在0-127中，关键词应排除这种词汇
    //如1993这种年份词汇 或者 book这种英文词汇
    for (int i = 0; i < str.size(); i++)  
    { 
        int tmp = (int)str[i];  
        if (tmp >= 0 && tmp <= 127)
        {  
            return true;
        }  
    }   

    //判断关键词是否包含一些特殊汉字，包括这种汉字的关键词一般没有重要价值
    if(    str.find("年") < str.length() //如1949年
        || str.find("月") < str.length() //如五月
        || str.find("日") < str.length() //如12日
        || str.find("第") < str.length() //如第十五号
        || str.find("省") < str.length() //如安徽省
        || str.find("市") < str.length() //如安庆市
        || str.find("县") < str.length() //如龙头县
        || str.find("村") < str.length() //如名山村
        || str.find("乡") < str.length() //如大坝乡
        || str.find("区") < str.length() //如朝阳区
        || str.find("某") < str.length() //如赵某
        || str.find("Ｘ") < str.length() //如赵XX
        || str.find("×")  < str.length() //如赵xx
        || str.find("审") < str.length() //如一审
        || str.find("一") < str.length()
        || str.find("二") < str.length()
        || str.find("三") < str.length()
        || str.find("四") < str.length()
        || str.find("五") < str.length()
        || str.find("六") < str.length()
        || str.find("七") < str.length()
        || str.find("八") < str.length()
        || str.find("九") < str.length()
        || str.find("十") < str.length()
        || str.find("百") < str.length()
        || str.find("千") < str.length()
        || str.find("万") < str.length()
        || str.find("亿") < str.length()
        || str.find("者") < str.length() //如目击者
        || str.find("#") < str.length()
      ){
        return true;
    } 

    return false;
} 

//@brief 文本内容关键词抽取
//@param [in]  contents: 文本内容
//@return string
//@retval 关键词信息，单词:词频_词序#单词:词频_词序   
std::string Extractor::extract(std::string& contents){
    //加载停用词表到内存
    load_pass_words(stop_words, stop_words_path);
    
    //加载白名单到内存
    load_pass_words(white_words, white_words_path);

    if(!NLPIR_Init("", UTF8_CODE, "0")){ //the 2nd para means UTF-8 encoding 
        return  "Sorry, NLP工具初始化失败";
    }
    
    int nCount; //the count of split words
 
    //result_t is a struct, it contains some elems
    const result_t* pResult = NLPIR_ParagraphProcessA(contents.c_str(), &nCount);
	char *sWhichDic;
	char sWord[100];
    std::string wordstype;
    int word_order = 1;

	for(int i=0; i<nCount; i++){
        strncpy(sWord, contents.c_str() + pResult[i].start, pResult[i].length);
		sWord[pResult[i].length] = 0;
       
        //过滤停用词表和白名单
        if( pResult[i].length > 3 //词语只有一个字
            && !contain_special_words(sWord) //词语是否含有特殊字眼
            && (iter = stop_words.find(sWord)) == stop_words.end() //过滤停用词表
            && (iter = white_words.find(sWord)) == white_words.end() //过滤白名单
          )
        {
            iter1 = split_words_freq.find(sWord);
            if(iter1 != split_words_freq.end()){
                split_words_freq[sWord] += 1;
            }else{
                split_words_freq[sWord] = 1;
            } 
                
            split_words_order[sWord] = word_order++;
        } 
	}
    
    std::string keywords_res = ""; //返回到数据库中的关键词抽取信息
    std::string tmp_str;
    
    //note: to_string是C++11的库，编译时应加上-std=c++11
    for(iter1 = split_words_freq.begin(); iter1 != split_words_freq.end(); iter1++){
        tmp_str = iter1->first + ":" + std::to_string(iter1->second) + "_" + std::to_string(split_words_order[iter1->first]) + "#";
        keywords_res += tmp_str;
    }

    NLPIR_Exit();
    return keywords_res;
}

}
