/*
 * File Name: sim_calc.h
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Thu Apr 26 19:49:26 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 
#ifndef SICT_CASESHOW_SIM_CALC_H
#define SICT_CASESHOW_SIM_CALC_H

#include <string>
#include <vector>
#include <set>
#include <map>
namespace caseshow{
class SimCalc{
public:
    //@brief 默认构造函数
    SimCalc(){} 

    //@brief 默认析构函数
    virtual ~SimCalc(){} 

    //@brief 根据指定分隔符分割字符串
    //@param [in] str: 待分割的字符串
    //       [in] sep: 分隔符
    //       [out]  v: 存放分割结果的向量
    //
    //@return void
    //retval
    void split_string(const std::string& str, std::vector<std::string>& v, const std::string& sep);
    
    //@brief 工具类：打印向量
    //@param [in] v: 待打印的向量
    //@return void
    //@retval
    void print_vector(std::vector<int>& v);
    
    //@brief 工具类：打印set集合
    //@daaram [in] s: 待打印的seT集
    //@return void
    //@retval
    void print_set(std::set<std::string>& s);
    
    //@brief 工具类：打印map集合
    //@param [in] m: 待打印的map集合
    //@return void
    //@retval
    void print_map(std::map<std::string, int>& m);
    
    //@brief 计算两个字符串的相交关键词向量的词频和词序向量
    //@param [in] str1: 字符串1
    //       [in] str2: 字符串2
    //       [out] join_str1_freq: 字符串1中相交关键词的词频向量
    //       [out] join_str1_order: 字符串1中相交关键词的词序向量
    //       [out] join_str2_freq: 字符串2中相交关键词的词频向量
    //       [out] join_str2_order: 字符串2中相交关键词的词序向量
    //       [out] str1_max_pos: 字符串1中关键词的最大绝对位置
    //       [out] str2_max_pos: 字符串2中关键词的最大绝对位置
    //@return void
    //@retval
    void get_freq_order_vector(std::string& str1, std::string& str2, std::vector<int>& join_str1_freq, std::vector<int>& join_str1_order, std::vector<int>& join_str2_freq, std::vector<int>& join_str2_order, int& str1_max_pos, int& str2_max_pos);
    
    //@brief 计算两个向量之间的夹角余弦值VSM
    //@param [in] v1: 向量1
    //       [in] v2: 向量2 
    //@return float
    //retval 两个向量之间的余弦值
    float vsm_res(std::vector<int> v1, std::vector<int> v2);
    
    //@brief 计算向量的逆序数
    //@param [in] v: 向量
    //@return int
    //@retval 向量的逆序数
    int get_inv_num(std::vector<int> v);

    //@brief 计算两个向量之间的词频相似度
    //@param [in] v1: 向量1
    //       [in] v2: 向量2 
    //@return float
    //retval 两个向量之间的词频相似度
    float sim_freq(std::vector<int> v1, std::vector<int> v2);
    
    //@brief 计算两个向量之间的词序相似度
    //@param [in] v1: 向量1
    //       [in] v2: 向量2 
    //       [in] l1: 向量1中关键词的最大绝对位置
    //       [in] l2: 向量2中关键词的最大绝对位置
    //@return float
    //retval 两个向量之间的词序相似度
    float sim_order(std::vector<int> v1, std::vector<int> v2, int l1, int l2);

private:
    //字符串关键词信息样例：工程:7_4#建筑:3_38    
    const std::string sep1 = "#"; //关键词之间的分隔符
    const std::string sep2 = ":"; //单词和词频词序之间的分隔符
    const std::string sep3 = "_"; //词频和词序之间的分隔符
};

} 
#endif
