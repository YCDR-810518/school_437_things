//
//  jm.cpp
//  异或对称加解密算法实现
//
//  Created by 姚晨 on 2025/11/5.
//

#include "jm.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// 生成公钥
string PubKey_generate(int length) {
    // 启动随机数引擎
    unsigned pubKeySeed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(pubKeySeed);
    
    string pubKey;
    
    // 生成可打印字符 (33-126)
    for (int i = 0; i < length; i++) {
        uniform_int_distribution<int> pubKeyChar(33, 126);
        char random_char = static_cast<char>(pubKeyChar(generator));
        pubKey += random_char;
    }
    
    return pubKey;
}

string PubKey_Lock(string key, string data) {
    // 检查密钥是否为空
    if(key.empty()) {
        return "=====密钥为空！=====";
    }
    
    if(data.empty()) {
        return "=====数据为空！=====";
    }
    
    stringstream ss;
    ss << hex << uppercase << setfill('0');
    
    size_t keyLength = key.size();
    
    // 加密并转换为十六进制
    for(size_t i = 0; i < data.size(); i++) {
        size_t keyIndex = i % keyLength;
        unsigned char encrypted_char = data[i] ^ key[keyIndex];
        ss << setw(2) << static_cast<int>(encrypted_char);
    }
    
    return ss.str();
}

// 解密函数
string sta_unlock(string& pubKey, string& priKey, string& lock_sta) {
    // 检查输入是否为空
    if(pubKey.empty() || priKey.empty() || lock_sta.empty()) {
        return "=====输入参数不能为空=====";
    }
    
    // 检查十六进制字符串长度是否为偶数
    if(lock_sta.size() % 2 != 0) {
        return "=====密文格式错误（长度应为偶数）=====";
    }
    
    // 将十六进制字符串转换为字节数组
    vector<unsigned char> encryptedBytes;
    for(size_t i = 0; i < lock_sta.size(); i += 2) {
        string byteStr = lock_sta.substr(i, 2);
        try {
            int byteValue = stoi(byteStr, nullptr, 16);
            encryptedBytes.push_back(static_cast<unsigned char>(byteValue));
        } catch (...) {
            return "=====密文格式错误=====";
        }
    }
    
    // 先用私钥解密
    vector<unsigned char> tempDecrypted;
    size_t priKeyLength = priKey.size();
    for(size_t i = 0; i < encryptedBytes.size(); i++) {
        size_t keyIndex = i % priKeyLength;
        unsigned char decrypted_char = encryptedBytes[i] ^ priKey[keyIndex];
        tempDecrypted.push_back(decrypted_char);
    }
    
    // 再用公钥解密
    string result;
    size_t pubKeyLength = pubKey.size();
    for(size_t i = 0; i < tempDecrypted.size(); i++) {
        size_t keyIndex = i % pubKeyLength;
        unsigned char final_char = tempDecrypted[i] ^ pubKey[keyIndex];
        result += final_char;
    }
    
    return result;
}


