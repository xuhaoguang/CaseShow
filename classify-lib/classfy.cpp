/*
 * File Name: classfy.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Sun Jan 28 13:52:46 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 

#include <iostream>
#include "stdio.h"
#include "LJClassifier.h"
using namespace std;

int main(){
    if (!classifier_init("", "")){
        cout << "初始化失败" << endl;
    }


    cout << "初始化成功" << endl;
    return 0;
} 
