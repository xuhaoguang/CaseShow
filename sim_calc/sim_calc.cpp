/*
 * File Name: sim_calc.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Thu Apr 26 20:06:17 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 
#include <iostream>
#include <sstream>
#include <math.h>
#include "sim_calc.h"

namespace caseshow{

//@brief 根据指定分隔符分割字符串
//@param [in] str: 待分割的字符串
//       [in] sep: 分隔符
//       [out]  v: 存放分割结果的向量
//return void
//retval
void SimCalc::split_string(const std::string& str, std::vector<std::string>& v, const std::string& sep){
    std::string::size_type pos1, pos2;
    pos2 = str.find(sep);
    pos1 = 0;
    
    while(std::string::npos != pos2){
        v.push_back(str.substr(pos1, pos2-pos1));
        pos1 = pos2 + sep.size();
        pos2 = str.find(sep, pos1);
    }

    if(pos1 != str.length()){
        v.push_back(str.substr(pos1));
    }
}

//@brief 工具类：打印向量
//@param [in] v: 待打印的向量
//return void
//retval
void SimCalc::print_vector(std::vector<int>& v){
    for(size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << "\t";
    }
    
    std::cout << "\n\n";
} 

//@brief 工具类：打印set集合
//@daaram [in] s: 待打印的seT集
//return void
//retval
void SimCalc::print_set(std::set<std::string>& s){
    std::set<std::string>::iterator iter;
    for(iter = s.begin(); iter != s.end(); iter++){
        std::cout << *iter << "\t";
    } 
    std::cout << std::endl;
}

//@brief 工具类：打印map集合
//@param [in] m: 待打印的map集合
//return void
//retval
void SimCalc::print_map(std::map<std::string, int>& m){
    std::map<std::string, int>::iterator iter;
    for(iter = m.begin(); iter != m.end(); iter++){
        std::cout << iter->first << "\t" << iter->second << std::endl;
    } 
}

//@brief 计算两个字符串的相交关键词向量的词频和词序向量
//@param [in] str1: 字符串1
//       [in] str2: 字符串2
//       [out] join_str1_freq: 字符串1中相交关键词的词频向量
//       [out] join_str1_order: 字符串1中相交关键词的词序向量
//       [out] join_str2_freq: 字符串2中相交关键词的词频向量
//       [out] join_str2_order: 字符串2中相交关键词的词序向量
//return void
//retval
void SimCalc::get_freq_order_vector(std::string& str1, std::string& str2, std::vector<int>& join_str1_freq, std::vector<int>& join_str1_order, std::vector<int>& join_str2_freq, std::vector<int>& join_str2_order){
    std::set<std::string> str1_words; //记录字符串1中的关键词
    std::set<std::string> join_words; //记录两个字符串的相交词汇
    std::set<std::string>::iterator iter; 
    
    std::map<std::string, int> str1_freq; //记录字符串1中关键词的词频信息
    std::map<std::string, int> str1_order; //记录字符串1中关键词的词序信息
    std::map<std::string, int> str2_freq; //记录字符串2中关键词的词频信息
    std::map<std::string, int> str2_order; //记录字符串2中关键词的词序信息
    
    //统计字符串1的词频和词序信息
    std::vector<std::string> v1; 
    split_string(str1, v1, sep1);
    
    for(size_t i = 0; i < v1.size(); i++){
        std::vector<std::string> tmp1;
        split_string(v1[i], tmp1, sep2);
    
        std::vector<std::string> tmp2;
        split_string(tmp1[1], tmp2, sep3);
    
        //将字符串类型的词频数据和词序数据转为int
        int freq, order;
        std::stringstream stream1(tmp2[0]);
        stream1 >> freq;  
        
        std::stringstream stream2(tmp2[1]);
        stream2 >> order;  

        str1_words.insert(tmp1[0]);
        str1_freq[tmp1[0]] = freq;
        str1_order[tmp1[0]] = order;
    } 
    
    //统计字符串2的词频和词序信息
    std::vector<std::string> v2; 
    split_string(str2, v2, sep1);
    
    for(size_t i = 0; i < v2.size(); i++){
        std::vector<std::string> tmp1;
        split_string(v2[i], tmp1, sep2);
    
        std::vector<std::string> tmp2;
        split_string(tmp1[1], tmp2, sep3);
        
        int freq, order;
        std::stringstream stream1(tmp2[0]);
        stream1 >> freq;  
        
        std::stringstream stream2(tmp2[1]);
        stream2 >> order;  

        str2_freq[tmp1[0]] = freq;
        str2_order[tmp1[0]] = order;

        //统计字符串1和字符串2的相交词汇
        if ((iter = str1_words.find(tmp1[0])) != str1_words.end()){ //相交词汇
            join_words.insert(tmp1[0]);
        } 
    }
   
    //统计相交关键词的词频和词序向量
    for(iter = join_words.begin(); iter != join_words.end(); iter++){
        join_str1_freq.push_back(str1_freq[*iter]);
        join_str2_freq.push_back(str2_freq[*iter]);
        join_str1_order.push_back(str1_order[*iter]);
        join_str2_order.push_back(str2_order[*iter]);
    } 
} 

//@brief 计算两个向量之间的夹角余弦值VSM
//@param [in] v1: 向量1
//       [in] v2: 向量2 
//return float
//retval 两个向量之间的余弦值
float SimCalc::vsm_res(std::vector<int> v1, std::vector<int> v2){
    int fenzi = 0;
    double fenmu1 = 0.0;
    double fenmu2 = 0.0;

    for(size_t i = 0; i < v1.size(); i++){
        fenzi += v1[i] * v2[i];
        fenmu1 += v1[i] * v1[i];
        fenmu2 += v2[i] * v2[i];
    }

    return fenzi / (sqrt(fenmu1) * sqrt(fenmu2));
}

//@brief 计算两个向量之间的词频相似度
//@param [in] v1: 向量1
//       [in] v2: 向量2 
//return float
//retval 两个向量之间的词频相似度
float SimCalc::sim_freq(std::vector<int> v1, std::vector<int> v2){
    return vsm_res(v1, v2);
}


}
