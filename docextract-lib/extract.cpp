/*
 * File Name: extract.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Sun Jan 28 12:36:12 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 

#include <iostream>
#include "DocExtractor.h"
#include "stdio.h"
#include <string.h>
using namespace std;

int main(int argc, char** argv){
    if (!DE_Init("./", 1, "")){
        cout << "初始化失败" << endl;;
        return 0;
    } 
    string content = string(argv[1]);
    cout << "初始化成功" << endl;
    DOC_PARSER_HANDLE handle = DE_ParseDocE(content.c_str(), "", true, ALL_REQUIRED);

    printf("抽取的人名为-->%s\n", DE_GetResult(handle, 0));
    printf("抽取的地名为-->%s\n", DE_GetResult(handle, 1));
    printf("抽取的机构名为-->%s\n", DE_GetResult(handle, 2));
    printf("抽取的关键词为-->%s\n", DE_GetResult(handle, 3));
    printf("抽取的文章作者为-->%s\n", DE_GetResult(handle, 4));
    printf("抽取的媒体为-->%s\n", DE_GetResult(handle, 5));
    printf("抽取的文章对应的所在国别为-->%s\n", DE_GetResult(handle, 6));
    printf("抽取的文章对应的所在省份为-->%s\n", DE_GetResult(handle, 7));
    printf("抽取的文章摘要为-->%s\n", DE_GetResult(handle, 8));
    printf("输出文章的正面情感词为-->%s\n", DE_GetResult(handle, 9));
    printf("输出文章的副面情感词-->%s\n", DE_GetResult(handle, 10));
    printf("输出文章去除网页等标签后的正文-->%s\n", DE_GetResult(handle, 11)); 



    DE_ReleaseHandle(handle);
    DE_Exit();
    return 0;
} 
