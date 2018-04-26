/*
 * File Name: extract_main.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Wed Apr 25 20:42:28 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 
#include <iostream>
#include "extract.h"

using namespace caseshow;

int main(int argc, char** argv){
    Extractor robot;
    std::string contents = std::string(argv[1]);
    std::cout << robot.extract(contents) << std::endl; 
    return 0;
} 
