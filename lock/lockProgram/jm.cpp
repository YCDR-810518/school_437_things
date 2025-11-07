//
//  jm.cpp
//  异或对称加解密算法实现
//
//  Created by 姚晨 on 2025/11/5.
//

#include "jm.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

//生成公钥
string PubKey_generate(int length){
    //启动随机数引擎
    unsigned pubKeySeed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(pubKeySeed);
    
    //输出池
    string pubKey;
    pubKey.resize(length);
    
    // 直接生成到字符串，不需要缓冲池
    for (int i = 0; i < length; i++) {
        // 使用 unsigned char 避免符号问题
        //生成可答应的
        uniform_int_distribution<int> pubKeyChar(33, 126);
        unsigned char random_char = static_cast<unsigned char>(pubKeyChar(generator));
        pubKey += random_char;
    }
    /*
    //输出缓冲池
    //一级
    vector<int> pubKeyNumArr;
    //二级
    vector<char> pubKeyArr;
    
    //根据设定的长度输出公钥
    for (int i=0; i<length; i++) {
        uniform_int_distribution <int> pubKeyChar(0, 255); //范围是-128～127
        pubKeyNumArr.push_back(pubKeyChar(generator));
    }
    
    //将生成的公钥存进二级缓冲池
    for(const char c : pubKeyNumArr){
        pubKeyArr.push_back(c);
    }
    
    //将二级缓冲池中的数据输出
    for(char c : pubKeyArr){
        pubKey += c;
    }
    */
    
    return pubKey;
}


string PubKey_Lock(string pubKey,
                string statistic){

    //密钥缓冲区
    vector <char> pubKeyArr;
    //明文缓冲区
    vector <char> staArr;
    //密文缓冲区
    vector<char> jmStaArr;
    //密钥长度
    unsigned long pubKeyLeng = pubKeyArr.size();
    //密文储存区
    string jmstatistic;
    //分别输入
    for(char c : pubKey){
        pubKeyArr.push_back(c);
    }
    for(char c : statistic){
        staArr.push_back(c);
    }
    
    //加密
    for(int i=0;i<statistic.size();i++){
        //计算要用到的多字符密钥索引
        unsigned long long keyIndex = i % pubKeyLeng;
        
        jmStaArr.push_back(statistic[i] ^ pubKeyArr[keyIndex]);
    }
    
    //将加密数据丢到储存区（输出）
    for(const char c : jmStaArr){
        jmstatistic += c;
    }
    
    return jmstatistic;
}

