//
//  jm.h
//  异或对称加解密算法实现
//
//  Created by 姚晨 on 2025/11/5.

//该文件为加密的头文件
#ifndef JM_H
#define JM_H

#include <string>

std::string PubKey_generate(int length);
std::string PubKey_Lock(std::string key, std::string data);
std::string sta_unlock(std::string& pubKey, std::string& priKey, std::string& lock_sta);

#endif
