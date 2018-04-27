/*
 * File Name: sim_calc_main.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Thu Apr 26 19:55:26 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 
#include <iostream>
#include <vector>
#include <string>
#include "sim_calc.h"

using namespace caseshow;
int main(int argc, char** argv){
    std::string str1 = argv[1];
    std::string str2 = argv[2];

    SimCalc sim1;
    std::vector<int> join_str1_freq;
    std::vector<int> join_str1_order;
    std::vector<int> join_str2_freq;
    std::vector<int> join_str2_order;
    
    sim1.get_freq_order_vector(str1, str2, join_str1_freq, join_str1_order, join_str2_freq, join_str2_order);
    //sim1.print_vector(join_str1_freq);
    //sim1.print_vector(join_str2_freq);
    //sim1.print_vector(join_str1_order);
    //sim1.print_vector(join_str2_order);

    std::cout << "词频相似度为：" << sim1.sim_freq(join_str1_freq, join_str2_freq) << std::endl;
    //std::cout << sim1.sim_freq(join_str1_order, join_str2_order) << std::endl;

    return 0;
} 
