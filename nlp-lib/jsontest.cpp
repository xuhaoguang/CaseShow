/*
 * File Name: jsontest.cpp
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Mon Jan 29 14:45:59 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 

#include <iostream>
#include <string>
#include "json.h"
#include "json-forwards.h"

using namespace std;

int main(){
    Json::Value root;
    Json::FastWriter writer;

    Json::Value person1;
    person1["name"] = "Harvey";
    person1["age"] = 24;
    root["person1"] = person1;

    Json::Value person2;
    person2["name"] = "XHG";
    Json::Value books;
    books[0] = "english";
    books[1] = "math";
    books[2] = "chinese";
    person2["books"]  = books;
    root["person2"] = person2;

    string json_str = writer.write(root);
    cout << json_str << endl;
    return 0;
} 
