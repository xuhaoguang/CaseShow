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
#include "NLPIR.h"
#include "DocExtractor.h"

using namespace std;

map<char*, char*> wordtype_map;

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
    wordtype_map["rg"]   = "代词";
} 
int main(int argc, char** argv){
    init_wordtype_map();
    cout << wordtype_map["sf"] << endl;
    return 0;
    
    string s = string(argv[1]);

    /* ----------------------------分词处理----------------*/
    if(!NLPIR_Init("", UTF8_CODE, "0")){ //the 2nd para means UTF-8 encoding 
        cout <<  "Sorry, NLP工具初始化失败" << endl;
        return -1;
    }
   
    int nCount; //the count of split words
    string fenci_res = "";

    //const char* pResult = NLPIR_ParagraphProcess(s.c_str());
    //const char* pResult = NLPIR_ParagraphProcess(s);
    //cout << pResult << endl;
 
    //result_t is a struct, it contains some elems
    const result_t* pResult = NLPIR_ParagraphProcessA(s.c_str(), &nCount);
	char *sWhichDic;
	char sWord[100];

    //cout << pResult << endl;

	for(int i=0; i<nCount; i++){   //print split words
		sWhichDic = "";
		switch (pResult[i].word_type){
		    case 0:
		    	sWhichDic = "核心词典";
		    	break;
		    case 1:
		    	sWhichDic = "用户词典";
		    	break;
		    case 2:
		    	sWhichDic = "专业词典";
		    	break;
		    default:
			    break;
		}
		
        strncpy(sWord, s.c_str() + pResult[i].start, pResult[i].length);
		sWord[pResult[i].length] = 0;

        //fenci_res = fenci_res + sWord + "\t";
        //cout << sWord << "\t";
        //
            
         
        cout 
            //<< "No." << i << "\t"
            //<< "start: " << pResult[i].start << "\t"
            //<< "length: " << pResult[i].length << "\t"
            << "sPOS: " << pResult[i].sPOS << "\t"
            //<< "POS_ID: " << pResult[i].iPOS << "\t"
            //<< "Word_ID: " << pResult[i].word_ID  << "\t"
            //<< "UserDefine: " << sWhichDic << "\t"
            << "Word: " << sWord << "\t"
            //<< "Weight: " << pResult[i].weight << \t"
            << endl;
	}
    
    //cout << fenci_res;

    const string keyword_res = NLPIR_GetKeyWords(s.c_str());
    //cout << keyword_res << endl;

    const char * newword_res= NLPIR_GetNewWords(s.c_str());
    //cout << newword_res;
    NLPIR_Exit();
    return 0;
} 
