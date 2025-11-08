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
#include <string>
#include <limits>
#include "jm.h"

using namespace std;

int main(int argc, const char * argv[]) {
    char restart = '1';
    
    while (restart != ' ') {
        char mode = 'y';
        
        cout << "该程序用于数据的加密和解密\n"
             << "请输入y/z确定进入加密还是解密模式: ";
        cin >> mode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清空缓冲区
        
        if(mode == 'y') {
            // 加密程序
            cout << "=====已进入加密模式=====\n"
                 << "=====在加密第一个数据前会生成公钥，请妥善保存=====" << endl;
            
            // 生成公钥
            int pubKeyLen = 0;
            cout << "=====请在下一行设置公钥长度（长一点会比较安全）=====\n";
            cout << "建议长度（100-1000）: ";
            cin >> pubKeyLen;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if(pubKeyLen <= 0) {
                cout << "=====公钥长度必须大于0=====" << endl;
                continue;
            }
            
            string pubKey = PubKey_generate(pubKeyLen);
            cout << "=====下一行输出公钥=====\n"
                 << pubKey << endl
                 << "=====公钥输出完毕=====" << endl;
            
            char goOn = ' ';
            string priKey;
            bool firstTime = true;
            
            do {
                if (firstTime) {
                    cout << "=====接下来请设置私钥=====\n";
                    cout << "私钥: ";
                    getline(cin, priKey);
                    cout << "=====私钥设置成功=====" << endl;
                    firstTime = false;
                }
                
                // 接收要加密的数据
                string plainText, encryptedWithPub, finalEncrypted;
                cout << "=====请输入要加密的数据=====\n";
                cout << "数据: ";
                getline(cin, plainText);
                
                if(plainText.empty()) {
                    cout << "=====输入不能为空=====" << endl;
                    continue;
                }
                
                // 加密过程
                encryptedWithPub = PubKey_Lock(pubKey, plainText);
                cout << "=====公钥加密完成=====" << endl;
                
                finalEncrypted = PubKey_Lock(priKey, encryptedWithPub);
                cout << "=====私钥加密完成=====\n"
                     << "=====输出密文（请复制）=====\n"
                     << finalEncrypted
                     << "\n=====密文输出完毕=====" << endl;
                
                // 询问是否继续
                cout << "=====是否继续加密？=====\n"
                     << "按e退出，按其他键继续加密: ";
                string input;
                getline(cin, input);
                goOn = input.empty() ? ' ' : input[0];
                
                if(goOn != 'e') {
                    cout << "=====是否更改私钥？=====\n"
                         << "1(是)/其他键(否): ";
                    string changeKey;
                    getline(cin, changeKey);
                    if(!changeKey.empty() && changeKey[0] == '1') {
                        cout << "=====请输入新私钥=====\n";
                        cout << "新私钥: ";
                        getline(cin, priKey);
                        cout << "=====私钥更改成功=====" << endl;
                    }
                }
                
            } while(goOn != 'e');
            
        } else if(mode == 'z') {
            // 解密程序
            string pubKey, priKey, encryptedText;
            
            cout << "=====已进入解密模式=====" << endl;
            
            cout << "=====请在下一行输入公钥=====\n";
            cout << "公钥: ";
            getline(cin, pubKey);
            
            cout << "=====请在下一行输入私钥=====\n";
            cout << "私钥: ";
            getline(cin, priKey);
            
            cout << "=====请在下一行输入要解密的密文=====\n";
            cout << "密文: ";
            getline(cin, encryptedText);
            
            if(pubKey.empty() || priKey.empty() || encryptedText.empty()) {
                cout << "=====输入不能为空=====" << endl;
                continue;
            }
            
            cout << "=====正在解密=====" << endl;
            string decryptedText = sta_unlock(pubKey, priKey, encryptedText);
            
            cout << "=====解密结果=====\n"
                 << decryptedText << endl
                 << "=====解密完成=====" << endl;
            
        } else {
            cout << "=====输入错误=====\n"
                 << "=====按下空格结束程序，其他键继续=====" << endl;
            
            string input;
            getline(cin, input);
            restart = input.empty() ? ' ' : input[0];
            continue;
        }
        
        // 询问是否继续程序
        cout << "=====是否继续使用程序？=====\n"
             << "按空格结束，其他键继续: ";
        string input;
        getline(cin, input);
        restart = input.empty() ? ' ' : input[0];
    }
    
    cout << "=====程序结束，感谢使用=====" << endl;
    return 0;
}

/*
#include <iostream>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <random>
#include "jm.h"

int main(int argc, const char * argv[]) {
    char mode = 'y';
    char restart = '1';
    //询问是要加密还是解密
    std::cout << "该程序用于数据的加密和解密\n"
              << "请输入y/z确定进入加密还是解密模式" <<std::endl;
    std::cin >> mode;
    
    //加密程序
    while (restart != ' ' ) {
        
        if(mode == 'y'){
            
            //加密公钥
            string pubKey;
            int pubKeyLen = 0;
            
            //进入加密时输出公钥并提示用户保存
            std::cout << "=====已进入加密模式=====\n"
            << "=====在加密第一个数据前会生成公钥，请妥善保存====="<<std::endl;
            //生成公钥
            std::cout << "=====请在下一行设置公钥长度（长一点会比较安全）=====" <<std::endl;
            std::cin >> pubKeyLen;
            pubKey = PubKey_generate(pubKeyLen);
            
            //输出公钥
            std::cout << "=====下一行输出公钥=====\n"
            << pubKey <<std::endl;
            
            //选择是否继续加密or设置私钥（按空格键继续，按e退出加密）
            char goOn = '0';
            char skipPriKey = ' ';
            
            //私钥
            std::string priKey;
            
            for(int count=0;goOn!='e';count++){
                
                if (count == 0 || skipPriKey=='0') {
                    //提示用户设置私钥
                    std::cout << "=====接下来请设置私钥=====" <<std::endl;
                    std::cin >> priKey;
                    std::cout << "=====私钥设置成功====="<<std::endl;
                }
                
                //接收一个字符串并用公钥进行第一次加密
                std::string statistic_plain, statistic_lock_pub, statistic_lock_pri;
                std::cout << "=====请输入要加密的数据=====" <<std::endl;
                std::cin >> statistic_plain;
                statistic_lock_pub = PubKey_Lock(pubKey,statistic_plain);
                std::cout << "=====公钥加密完成=====" <<std::endl;
                
                //接着用私钥进行第二次加密
                statistic_lock_pri = PubKey_Lock(priKey, statistic_lock_pub);
                std::cout << "=====私钥加密完成=====\n"
                << "=====输出密文（请复制）=====\n"
                << statistic_lock_pri
                << "\n=====密文输出完毕====="<<std::endl;
                
                //询问是否继续加密
                std::cout << "=====是否继续加密？=====\n"
                << "=====按e退出，按空格继续加密=====(默认继续)"<<std::endl;
                std::cin >> goOn;
                
                statistic_plain.clear();
                statistic_lock_pub.clear();
                statistic_lock_pri.clear();
                
                if(goOn == ' '){
                    //询问是否更改下一次加密的私钥
                    std::cout << "=====是否更改私钥？=====\n"
                    << "=====1(yes)/0(no)=====(默认为不更改私钥)\n"
                    <<std::endl;
                    std:: cin >> skipPriKey;
                }
                if (goOn == 'e') {
                    break;
                }
            }
        }
        
        //解密程序
        if(mode =='z'){
            //公/私钥
            string pubKey, priKey;
            //解密的密文储存区
            string lockSta;
            //解密明文储存区
            string plainSta;
            //提示输入公钥
            std::cout << "=====请在下一行输入公钥=====" <<std::endl;
            std::cin >> pubKey;
            //提示输入私钥
            std::cout << "=====请在下一行输入私钥=====" <<std::endl;
            std::cin >> priKey;
            //解密并输出
            std::cout << "=====正在解密=====" <<std::endl;
            plainSta = sta_unlock(pubKey, priKey, lockSta);
            std::cout <<"=====下面为解密数据=====" <<std::endl;
            std::cin >> plainSta;
            std::cout<< "=====解密完成=====" <<std::endl;
        }else{
            std::cout << "=====输入错误=====\n"
            << "=====按下回车重启程序=====\n"
            <<"=====按下空格结束程序====="
            <<std::endl;
            restart = getchar();
        }
    }
    return EXIT_SUCCESS;
}
*/
