/*
 * File Name: extract.h
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Fri Dec 22 14:45:12 2017
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 

#ifndef SICT_CASESHOW_EXTRACT_H
#define SICT_CASESHOW_EXTRACT_H

#include <fstream>
#include <string.h>
#include <string>
#include <set>
#include <map>
#include "NLPIR.h"

namespace caseshow{

class Extractor{
public:
    //@brief 默认构造函数
    Extractor(){}

    //@brief 默认析构函数
    virtual ~Extractor(){}

    //@brief 导入过滤关键词
    //@param [in]  path : 过滤词汇文本路径
    //       [out] myset: 过滤词汇内存镜像
    //@return void
    //@retval
    void load_pass_words(std::set<std::string>& myset, const std::string& path);
    
    //@brief 判断关键是否包含特殊字眼
    //@param [in]  path : 关键词
    //@return bool
    //@retval true: 关键词包含特殊词汇  false: 关键词不包含特殊词汇
    bool contain_special_words(std::string str);
 
    //@brief 文本内容关键词抽取
    //@param [in]  contents: 文本内容
    //@return string
    //@retval 关键词信息，单词:词频_词序#单词:词频_词序
    std::string extract(std::string& contents);

private:
    //停用词表和白名单的存储路径
    const std::string stop_words_path = "/www/web/default/info_extract/stop_words";
    const std::string white_words_path = "/www/web/default/info_extract/white_words";
    
    std::map<std::string, int> split_words_freq; //记录单词和词频
    std::map<std::string, int> split_words_order; //记录单词和词序
    std::set<std::string> stop_words;  //停用词表
    std::set<std::string> white_words; //白名单表
    std::set<std::string>::iterator iter; //迭代器
    std::map<std::string, int>::iterator iter1; //迭代器1
};
}

#endif //SICT_CASESHOW_EXTRACT_H
