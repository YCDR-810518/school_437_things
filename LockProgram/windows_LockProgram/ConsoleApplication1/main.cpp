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

int main() {
    char restart = '1';

    while (restart != ' ') {
        char mode = 'y';

        cout << "该程序用于数据的加密和解密\n"
            << "请输入y/z确定进入加密还是解密模式: ";
        cin >> mode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清空缓冲区

        if (mode == 'y') {
            // 加密程序
            cout << "=====已进入加密模式=====\n"
                << "=====在加密第一个数据前会生成公钥，请妥善保存=====" << endl;

            // 生成公钥
            int pubKeyLen = 0;
            cout << "=====请在下一行设置公钥长度（长一点会比较安全）=====\n";
            cout << "建议长度（100-1000）: ";
            cin >> pubKeyLen;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (pubKeyLen <= 0) {
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

                if (plainText.empty()) {
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

                if (goOn != 'e') {
                    cout << "=====是否更改私钥？=====\n"
                        << "1(是)/其他键(否): ";
                    string changeKey;
                    getline(cin, changeKey);
                    if (!changeKey.empty() && changeKey[0] == '1') {
                        cout << "=====请输入新私钥=====\n";
                        cout << "新私钥: ";
                        getline(cin, priKey);
                        cout << "=====私钥更改成功=====" << endl;
                    }
                }

            } while (goOn != 'e');

        }
        else if (mode == 'z') {
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

            if (pubKey.empty() || priKey.empty() || encryptedText.empty()) {
                cout << "=====输入不能为空=====" << endl;
                continue;
            }

            cout << "=====正在解密=====" << endl;
            string decryptedText = sta_unlock(pubKey, priKey, encryptedText);

            cout << "=====解密结果=====\n"
                << decryptedText << endl
                << "=====解密完成=====" << endl;

        }
        else {
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

