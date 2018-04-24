/*
 * File Name: split.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Fri Dec 22 14:45:12 2017
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <set>
#include "NLPIR.h"

using namespace std;

//停用词表和白名单的存储滤路径
const string stop_words_path = "/www/web/default/info_extract/stop_words";
const string white_words_path = "/www/web/default/info_extract/white_words";

set<string> split_words; //用于记录分词结果
set<string> stop_words;  //停用词表
set<string> white_words; //白名单表
set<string>::iterator iter; //迭代器

void load_pass_words(set<string>& myset, const string path)
{
    ifstream fin(path.c_str());
    string s;  
    while(getline(fin,s))
    {    
        myset.insert(s);
        //cout << s.c_str() << endl;
    }
    fin.close();
}

bool contain_num_alpha(string str)    
{    
    //cout << endl <<endl;
    //cout << str << "\t";
    for (int i = 0; i < str.size(); i++)  
    { 
        int tmp = (int)str[i];  
        //cout << tmp << "\t";
        if (tmp >= 0 && tmp <= 127)
        {  
            return true;
        }  
    }   
    return false;  
}  

bool contain_special_words(string str){
    if(    str.find("年") < str.length() 
        || str.find("月") < str.length() 
        || str.find("日") < str.length() 
        || str.find("第") < str.length() 
        || str.find("省") < str.length() 
        || str.find("市") < str.length() 
        || str.find("县") < str.length() 
        || str.find("村") < str.length() 
        || str.find("乡") < str.length() 
        || str.find("区") < str.length() 
        || str.find("某") < str.length() 
        || str.find("Ｘ") < str.length() 
        || str.find("×")  < str.length() 
        || str.find("审") < str.length()
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
        || str.find("者") < str.length()
      ){
        return true;
    } 

    return false;
} 
int main(int argc, char** argv){
    //加载停用词表到内存
    load_pass_words(stop_words, stop_words_path);
    //加载白名单到内存
    load_pass_words(white_words, white_words_path);

    //cout << stop_words.size() << endl;
    //cout << white_words.size() << endl;

    //for(iter = white_words.begin(); iter != white_words.end(); iter++){
    //    cout << *iter << endl;
    //} 
    
    string contents = string(argv[1]);

    if(!NLPIR_Init("", UTF8_CODE, "0")){ //the 2nd para means UTF-8 encoding 
        cout <<  "Sorry, NLP工具初始化失败" << endl;
        return -1;
    }
    
    int nCount; //the count of split words
 
    //result_t is a struct, it contains some elems
    const result_t* pResult = NLPIR_ParagraphProcessA(contents.c_str(), &nCount);
	char *sWhichDic;
	char sWord[100];
    string wordstype;

	for(int i=0; i<nCount; i++){
        strncpy(sWord, contents.c_str() + pResult[i].start, pResult[i].length);
		sWord[pResult[i].length] = 0;
       
        //过滤停用词表和白名单
        if( pResult[i].length > 3 //词语只有一个字
            && !contain_num_alpha(sWord) //词语全部是数字情况
            && !contain_special_words(sWord) //词语是否是年月日
            && (iter = stop_words.find(sWord)) == stop_words.end() //过滤停用词表
            && (iter = white_words.find(sWord)) == white_words.end() //过滤白名单
          )
        {
            //cout << pResult[i].length << "\n" <<sWord << endl;
            //cout <<sWord <<  endl;
            split_words.insert(sWord); //存储分词结果
        } 
	}
    
    for(iter = split_words.begin(); iter != split_words.end(); iter++){
        cout << *iter << endl;
    }
    cout << endl << "=================" << endl;
    NLPIR_Exit();
    return 0;
} 
