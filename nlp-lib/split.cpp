/*
 * File Name: split.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Fri Dec 22 14:45:12 2017
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 

#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include "NLPIR.h"
#include "DocExtractor.h"
#include "json.h"
#include "json-forwards.h"

using namespace std;

//词性标识对照表
map<string, string> wordtype_map;
map<string, string>::iterator it;

//词频统计
map<string, int> word_freq_map; //所有的词频统计
map<string, int> word_freq_N_map; //名词词频统计
map<string, int> word_freq_V_map; //动词词频统计
map<string, int> word_freq_Adj_map; //形容词词频统计
map<string, int>::iterator it_freq;

//Json组装器
Json::Value root;
Json::FastWriter writer;

//用于词频统计的大小排序
typedef pair<string, int> PAIR;
struct CmpByValue{
    bool operator()(const PAIR& lhs, const PAIR& rhs){
        return lhs.second > rhs.second;
    } 
}; 

int  MAX_WORD_FREQ_COUNT = 10; //名词、动词、形容词词频统计输出的最大个数
void init_wordtype_map();  //初始化词性对照表

int main(int argc, char** argv){
    init_wordtype_map();
    string contents = string(argv[1]);

    /* ======================================分词标注=========================================*/
    if(!NLPIR_Init("", UTF8_CODE, "0")){ //the 2nd para means UTF-8 encoding 
        cout <<  "Sorry, NLP工具初始化失败" << endl;
        return -1;
    }
    
    Json::Value fenciRes_word;
    Json::Value fenciRes_type;
    int nCount; //the count of split words
    //const char* pResult1 = NLPIR_ParagraphProcess(contents.c_str());
    //cout << pResult1 << endl;
 
    //result_t is a struct, it contains some elems
    const result_t* pResult = NLPIR_ParagraphProcessA(contents.c_str(), &nCount);
	char *sWhichDic;
	char sWord[100];
    string wordstype;

	for(int i=0; i<nCount; i++){   //print split words
        strncpy(sWord, contents.c_str() + pResult[i].start, pResult[i].length);
		sWord[pResult[i].length] = 0;
        
        const char* ss = pResult[i].sPOS;
        it = wordtype_map.find(ss);
        if(it != wordtype_map.end()){
            wordstype = wordtype_map[ss];
        }else{
            wordstype = "NULL";
        } 
        
        fenciRes_word[i] = sWord;
        fenciRes_type[i] = wordstype;

        //统计名词词频
        if(wordstype == "名词"){
            it_freq = word_freq_N_map.find(sWord);
            if(it_freq != word_freq_N_map.end()){
                word_freq_N_map[sWord] += 1;
            }else{
                word_freq_N_map[sWord]  = 1;
            }
        } 

        //统计动词词频
        if(wordstype == "动词"){
            it_freq = word_freq_V_map.find(sWord);
            if(it_freq != word_freq_V_map.end()){
                word_freq_V_map[sWord] += 1;
            }else{
                word_freq_V_map[sWord]  = 1;
            }
        }
        
        //统计形容词词频
        if(wordstype == "形容词"){
            it_freq = word_freq_Adj_map.find(sWord);
            if(it_freq != word_freq_Adj_map.end()){
                word_freq_Adj_map[sWord] += 1;
            }else{
                word_freq_Adj_map[sWord]  = 1;
            }
        }

        it_freq = word_freq_map.find(sWord); 
        if(it_freq != word_freq_map.end()){
            word_freq_map[sWord] += 1;
        }else{
            word_freq_map[sWord]  = 1;
        }
	}
    
    root["fenciRes"]["words"] = fenciRes_word;
    root["fenciRes"]["type"] = fenciRes_type;
    /* ======================================================================================*/
   
    
    /* ======================================词频统计=========================================*/
    //统计所有词频信息
    vector<PAIR> word_freq_sort_vector(word_freq_map.begin(), word_freq_map.end());
    sort(word_freq_sort_vector.begin(), word_freq_sort_vector.end(), CmpByValue()); 
    Json::Value wordfreqRes_word; 
    Json::Value wordfreqRes_freq;

    for(int i = 0; i != word_freq_sort_vector.size(); i++){
        wordfreqRes_word[i] = word_freq_sort_vector[i].first;
        wordfreqRes_freq[i] = word_freq_sort_vector[i].second;
    }

    root["wordfreqRes"]["words"] = wordfreqRes_word;
    root["wordfreqRes"]["freq"] = wordfreqRes_freq;
    

    //统计名词词频信息
    vector<PAIR> word_freq_N_sort_vector(word_freq_N_map.begin(), word_freq_N_map.end());
    sort(word_freq_N_sort_vector.begin(), word_freq_N_sort_vector.end(), CmpByValue());
    Json::Value wordfreqRes_N_word; 
    Json::Value wordfreqRes_N_freq; 

    int freq_length = (word_freq_N_sort_vector.size() > MAX_WORD_FREQ_COUNT) ? MAX_WORD_FREQ_COUNT : word_freq_N_sort_vector.size();
    for(int i = 0; i != freq_length; i++){
        wordfreqRes_N_word[i] = word_freq_N_sort_vector[i].first;
        wordfreqRes_N_freq[i] = word_freq_N_sort_vector[i].second;
    } 

    root["wordfreqRes_N"]["words"] = wordfreqRes_N_word;
    root["wordfreqRes_N"]["freq"] = wordfreqRes_N_freq;

    //统计动词词频信息
    vector<PAIR> word_freq_V_sort_vector(word_freq_V_map.begin(), word_freq_V_map.end());
    sort(word_freq_V_sort_vector.begin(), word_freq_V_sort_vector.end(), CmpByValue());
    Json::Value wordfreqRes_V_word; 
    Json::Value wordfreqRes_V_freq; 

    freq_length = (word_freq_V_sort_vector.size() > MAX_WORD_FREQ_COUNT) ? MAX_WORD_FREQ_COUNT : word_freq_V_sort_vector.size();
    for(int i = 0; i != freq_length; i++){
        wordfreqRes_V_word[i] = word_freq_V_sort_vector[i].first;
        wordfreqRes_V_freq[i] = word_freq_V_sort_vector[i].second;
    } 

    root["wordfreqRes_V"]["words"] = wordfreqRes_V_word;
    root["wordfreqRes_V"]["freq"] = wordfreqRes_V_freq;

    //统计形容词词频信息
    vector<PAIR> word_freq_Adj_sort_vector(word_freq_Adj_map.begin(), word_freq_Adj_map.end());
    sort(word_freq_Adj_sort_vector.begin(), word_freq_Adj_sort_vector.end(), CmpByValue());
    Json::Value wordfreqRes_Adj_word; 
    Json::Value wordfreqRes_Adj_freq; 

    freq_length = (word_freq_Adj_sort_vector.size() > MAX_WORD_FREQ_COUNT) ? MAX_WORD_FREQ_COUNT : word_freq_Adj_sort_vector.size();
    for(int i = 0; i != freq_length; i++){
        wordfreqRes_Adj_word[i] = word_freq_Adj_sort_vector[i].first;
        wordfreqRes_Adj_freq[i] = word_freq_Adj_sort_vector[i].second;
    } 

    root["wordfreqRes_Adj"]["words"] = wordfreqRes_Adj_word;
    root["wordfreqRes_Adj"]["freq"] = wordfreqRes_Adj_freq;
    /* ======================================================================================*/


    /* ======================================抽关键词========================================*/
    root["keywordsRes"] = NLPIR_GetKeyWords(contents.c_str());
    /* ======================================================================================*/
   

    /* ======================================新词发现========================================*/
    root["newwordsRes"] = NLPIR_GetNewWords(contents.c_str());
    /* ======================================================================================*/
    

    /* =============================实体抽取 & 自动摘要 & 情感分析===========================*/
    if (!DE_Init("./", 1, "")){
        cout << "初始化失败" << endl;;
        return -1;
    } 
    
    DOC_PARSER_HANDLE handle = DE_ParseDocE(contents.c_str(), "", true, ALL_REQUIRED);
    root["shitiRes"]["person"] = DE_GetResult(handle, 0);
    root["shitiRes"]["location"] = DE_GetResult(handle, 1);
    root["shitiRes"]["organization"] = DE_GetResult(handle, 2);
    root["summaryRes"] = DE_GetResult(handle, 8);
    root["sentimentRes"]["positive"] = DE_GetResult(handle, 9);
    root["sentimentRes"]["negative"] = DE_GetResult(handle, 10);
    /* ======================================================================================*/
    //printf("抽取的人名为-->%s\n", DE_GetResult(handle, 0));
    //printf("抽取的地名为-->%s\n", DE_GetResult(handle, 1));
    //printf("抽取的机构名为-->%s\n", DE_GetResult(handle, 2));
    //printf("抽取的关键词为-->%s\n", DE_GetResult(handle, 3));
    //printf("抽取的文章作者为-->%s\n", DE_GetResult(handle, 4));
    //printf("抽取的媒体为-->%s\n", DE_GetResult(handle, 5));
    //printf("抽取的文章对应的所在国别为-->%s\n", DE_GetResult(handle, 6));
    //printf("抽取的文章对应的所在省份为-->%s\n", DE_GetResult(handle, 7));
    //printf("抽取的文章摘要为-->%s\n", DE_GetResult(handle, 8));
    //printf("输出文章的正面情感词为-->%s\n", DE_GetResult(handle, 9));
    //printf("输出文章的副面情感词-->%s\n", DE_GetResult(handle, 10));
    //printf("输出文章去除网页等标签后的正文-->%s\n", DE_GetResult(handle, 11)); 

    string json_str = writer.write(root);
    cout << json_str;

    NLPIR_Exit();
    DE_Exit();
    DE_ReleaseHandle(handle);
    return 0;
} 

void init_wordtype_map(){
    wordtype_map["n"]   = "名词";
    wordtype_map["r"]   = "名词";
    wordtype_map["r1"]  = "名词";
    wordtype_map["r2"]  = "名词";
    wordtype_map["rj"]  = "名词";
    wordtype_map["rf"]  = "名词";
    wordtype_map["s"]   = "名词";
    wordtype_map["sf"]  = "名词";
    wordtype_map["t"]   = "名词";
    wordtype_map["z"]   = "名词";
    wordtype_map["l"]   = "名词";
    wordtype_map["g"]   = "名词";
    wordtype_map["t"]   = "时间词";
    wordtype_map["tg"]  = "时间词";
    wordtype_map["s"]   = "处所词";
    wordtype_map["f"]   = "方位词";
    wordtype_map["v"]   = "动词";
    wordtype_map["vd"]  = "动词";
    wordtype_map["vn"]  = "动词";
    wordtype_map["vshi"]= "动词";
    wordtype_map["vyou"]= "动词";
    wordtype_map["vf"]  = "动词";
    wordtype_map["vx"]  = "动词";
    wordtype_map["vi"]  = "动词";
    wordtype_map["vl"]  = "动词";
    wordtype_map["vg"]  = "动词";
    wordtype_map["a"]   = "形容词";
    wordtype_map["ad"]  = "形容词";
    wordtype_map["an"]  = "形容词";
    wordtype_map["ag"]  = "形容词";
    wordtype_map["al"]  = "形容词";
    wordtype_map["b"]   = "区别词";
    wordtype_map["bl"]  = "区别词";
    wordtype_map["z"]   = "状态词";
    wordtype_map["r"]    = "代词";
    wordtype_map["rr"]   = "代词";
    wordtype_map["rz"]   = "代词";
    wordtype_map["rzt"]  = "代词";
    wordtype_map["rzs"]  = "代词";
    wordtype_map["rzv"]  = "代词";
    wordtype_map["ry"]   = "代词";
    wordtype_map["ryt"]  = "代词";
    wordtype_map["rys"]  = "代词";
    wordtype_map["ryv"]  = "代词";
    wordtype_map["m"]    = "数词";
    wordtype_map["mq"]   = "数词";
    wordtype_map["q"]    = "量词";
    wordtype_map["qv"]   = "量词";
    wordtype_map["qt"]   = "量词";
    wordtype_map["d"]    = "副词";
    wordtype_map["p"]    = "介词";
    wordtype_map["pba"]  = "介词";
    wordtype_map["pbei"] = "介词";
    wordtype_map["c"]    = "连词";
    wordtype_map["cc"]   = "连词";
    wordtype_map["u"]    = "助词";
    wordtype_map["uzhe"] = "助词";
    wordtype_map["ule"]  = "助词";
    wordtype_map["uguo"] = "助词";
    wordtype_map["ude1"] = "助词";
    wordtype_map["ude2"] = "助词";
    wordtype_map["ude3"] = "助词";
    wordtype_map["usuo"] = "助词";
    wordtype_map["udeng"]= "助词";
    wordtype_map["uyy"]  = "助词";
    wordtype_map["udh"]  = "助词";
    wordtype_map["uls"]  = "助词";
    wordtype_map["uzhi"] = "助词";
    wordtype_map["ulian"]= "助词";
    wordtype_map["e"]    = "叹词";
    wordtype_map["y"]    = "语气词";
    wordtype_map["o"]    = "拟声词";
    wordtype_map["h"]    = "前缀词";
    wordtype_map["k"]    = "后缀词";
    wordtype_map["x"]    = "字符串";
    wordtype_map["xe"]   = "字符串";
    wordtype_map["xs"]   = "字符串";
    wordtype_map["xm"]   = "字符串";
    wordtype_map["xu"]   = "字符串";
    wordtype_map["w"]    = "标点符号";
    wordtype_map["wkz"]  = "标点符号";
    wordtype_map["wky"]  = "标点符号";
    wordtype_map["wyz"]  = "标点符号";
    wordtype_map["wyy"]  = "标点符号";
    wordtype_map["wj"]   = "标点符号";
    wordtype_map["ww"]   = "标点符号";
    wordtype_map["wt"]   = "标点符号";
    wordtype_map["wd"]   = "标点符号";
    wordtype_map["wf"]   = "标点符号";
    wordtype_map["wn"]   = "标点符号";
    wordtype_map["wm"]   = "标点符号";
    wordtype_map["ws"]   = "标点符号";
    wordtype_map["wp"]   = "标点符号";
    wordtype_map["wb"]   = "标点符号";
    wordtype_map["wh"]   = "标点符号";
}
