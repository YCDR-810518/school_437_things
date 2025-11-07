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
#include <iomanip>
using namespace std;
string to_hex(const string& binary_str);
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


string PubKey_Lock(string pubKey,string statistic){

    //密钥缓冲区
    vector <char> pubKeyArr;
    //明文缓冲区
    vector <char> staArr;
    //密文缓冲区
    vector<char> jmStaArr;
    //密文储存区
    string jmstatistic;
    stringstream ss;
    ss << hex << uppercase << setfill('0');
    //分别输入
    for(unsigned char c : pubKey){
        pubKeyArr.push_back(c);
    }
    for(unsigned char c : statistic){
        staArr.push_back(c);
    }
    
    //密钥长度
    unsigned long pubKeyLeng = pubKeyArr.size();
    //加密
    for(int i=0;i<statistic.size();i++){
        //计算要用到的多字符密钥索引
        unsigned long long keyIndex = i % pubKeyLeng;
        jmStaArr.push_back(statistic[i] ^ pubKeyArr[keyIndex]);
    }
    
    // 检查密钥是否为空
        if(pubKeyLeng == 0) {
            return "=====密钥为空！====="; // 或者返回原始数据，或者抛出异常
        }
        
        // 加密并直接转换为十六进制
        for(int i = 0; i < statistic.size(); i++) {
            // 计算要用到的多字符密钥索引
            unsigned long long keyIndex = i % pubKeyLeng;
            
            // 加密
            unsigned char encrypted_char = statistic[i] ^ pubKeyArr[keyIndex];
            
            // 直接转换为十六进制并添加到字符串流
            ss << setw(2) << static_cast<int>(encrypted_char);
        }
        
        // 将字符串流的内容赋给输出
        jmstatistic = ss.str();
    
    return jmstatistic;
}

//解密函数,接收公钥，私钥，加密数据（先解锁公钥，后解锁私钥）
string sta_unlock(string pubKey,string priKey, string lock_sta){
    //临时存储区域
    stringstream temp;
    temp << oct;
    int temp1;
    //密文储存区
    vector <char> strLockArr;
    vector <int> lockArr;
    //明文储存区
    vector<char> plainArr;
    //输入过程
    for(int i=0;i<lock_sta.size();i += 2){
        temp << lock_sta[i] ;
        temp << lock_sta[i+1];
        temp1 =
        strLockArr.push_back(temp);
        temp.clear();
    }
    //转换解密过程
    for (int i=0; i<; <#increment#>) {
        <#statements#>
    }
}

// 将二进制字符串转换为十六进制字符串
string to_hex(const string& binary_str) {
    stringstream ss;
    ss << hex << setfill('0');
    
    for(unsigned char c : binary_str) {
        ss << setw(2) << static_cast<int>(c) << " ";
        
    }
    
    return ss.str();
}


