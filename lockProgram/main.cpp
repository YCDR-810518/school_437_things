//
//  main.cpp
//  异或对称加解密算法实现
//
//  Created by 姚晨 on 2025/11/4.
//

//这是一个用异或算法实现简单加解密的算法实例
//公钥随机生成，并在进入加密程序时生成（在一次执行的过程中加密的所有公钥相同）
//私钥由用户设定，同时持有公私钥才可进行加解密操作


#include <iostream>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <random>
#include "jm.h"

int main(int argc, const char * argv[]) {
    char mode = 'y';
    //询问是要加密还是解密
    std::cout << "该程序用于数据的加密和解密\n"
              << "请输入y/z确定进入加密还是解密模式" <<std::endl;
    std::cin >> mode;
    
    //加密程序
    if(mode == 'y'){
        
        //加密公钥
        string pubKey;
        int pubKeyLen = 0;
        
        //进入加密时输出公钥并提示用户保存
        std::cout << "=====已进入加密模式=====\n"
        << "=====在加密前会生成公钥，请妥善保存====="<<std::endl;
        //生成公钥
        std::cout << "=====请在下一行设置公钥长度（长一点会比较安全）=====" <<std::endl;
        std::cin >> pubKeyLen;
        pubKey = PubKey_generate(pubKeyLen);
        
        //输出公钥
        std::cout << "=====下一行输出公钥=====\n"
        << pubKey <<std::endl;
        
        //私钥
        std::string priKey;
        //提示用户设置私钥并对私钥进行加密
        std::cout << "=====接下来请设置私钥=====" <<std::endl;
        std::cin >> priKey;
        std::cout << "=====私钥设置成功====="<<std::endl;
        
        
        //接收一个字符串并用公钥进行第一次加密
        std::string statistic_plain, statistic_lock;
        std::cout << "=====请输入要加密的数据=====" <<std::endl;
        std::cin >> statistic_plain;
        statistic_lock = PubKey_Lock(pubKey,statistic_plain);
        std::cout << "=====加密数据完成=====" <<std::endl;
        //接着用私钥进行第二次加密
        
        
        //询问是否继续加密
        //询问是否更改下一次加密的私钥
    }
    
    //解密程序
    //提示输入公钥
    
    //提示输入私钥
    
    //解密并输出
    
    return EXIT_SUCCESS;
}
