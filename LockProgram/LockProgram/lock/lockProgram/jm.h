//
//  jm.h
//  异或对称加解密算法实现
//
//  Created by 姚晨 on 2025/11/5.

//该文件为加密的头文件
# pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//对数据进行公钥加密
string PubKey_Lock(string pubKey, string statistic);

//生成公钥（字符串）
string PubKey_generate(int length);

//将二进制数据转换为十六进制
string to_hex(const string& binary_str);
