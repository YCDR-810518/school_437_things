//
//  menu.cpp
//  randomTwoColorBall
//
//  Created by 姚晨 on 2025/11/11.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
void showMenu()
{
    cout << " * * * * * * * * * * * * * * * * *" << endl;
    cout << " *                               *" << endl;
    cout << " *           选项面板              *" << endl;
    cout << " *                               *" << endl;
    cout << " *   请输入选项前对应数字执行         *" << endl;
    cout << " *                               *" << endl;
    cout << " *          1 随机取号             *" << endl;
    cout << " *                               *" << endl;
    cout << " *          2 作者留言             *" << endl;
    cout << " *                               *" << endl;
    cout << " *          3 退出程序             *" << endl;
    cout << " *                               *" << endl;
    cout << " * * * * * * * * * * * * * * * * *" << endl;
}

void showMenu_1_sec()
{
    cout << " * * * * * * * * * * * * * * * * *" << endl;
    cout << " *                               *" << endl;
    cout << " *           选项面板              *" << endl;
    cout << " *                               *" << endl;
    cout << " *   请输入选项前对应数字执行         *" << endl;
    cout << " *                               *" << endl;
    cout << " *          1 简单随机             *" << endl;
    cout << " *                               *" << endl;
    cout << " *          2 幸运数字             *" << endl;
    cout << " *                               *" << endl;
    cout << " *          3 纯粹随机             *" << endl;
    cout << " *                               *" << endl;
    cout << " *          4 批量随机             *" << endl;
    cout << " * * * * * * * * * * * * * * * * *" << endl;
}
//接收传统数组
void showAns(int doubleR[],int doubleB)
{
    cout << "红区结果如下：" << endl;
    for (int i = 0;i < 6;i++)
    {
        cout << doubleR[i] << "\t";
    }
    cout << endl;
    cout << "蓝区结果如下：" << endl;
    cout << doubleB << endl;
    cout << endl;
}
//根据vector特化的单输出
void showAns_vec(vector<int>doubleR,int doubleB){
    cout << "红区结果如下：" << endl;
    for (int i = 0;i < 6;i++)
    {
        cout << doubleR[i] << "\t";
    }
    cout << endl;
    cout << "蓝区结果如下：" << endl;
    cout << doubleB << endl;
    cout << endl;
}
//批量输出函数
//接收一个整数设置输出的号码条数
void largeAmountoutput(int lineNum){
    for (int i=0; i<lineNum; i++) {
        if (i==0) {
            cout << "红区结果如下：" << "\t\t\t\t\t"<< "蓝区结果如下：" << endl;
        }
        // 启动随机数引擎
        unsigned randomSeed = chrono::system_clock::now().time_since_epoch().count();
        
    }
}
void func02()
{
    cout << "该模块有待创作者完善，敬请期待！" << endl;
}
