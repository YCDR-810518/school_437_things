//
//  randomEngine.cpp
//  randomTwoColorBall
//
//  Created by 姚晨 on 2025/11/11.
//
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include "display.h"
using namespace std;
void bubbleUp(int doubleR[])
{
    for (int i = 0;i < 6-1;i++)
    {
        for (int j = 0;j < 6 - i - 1;j++)
        {
            if (doubleR[j] > doubleR[j + 1])
            {
                int temp = doubleR[j];
                doubleR[j] = doubleR[j + 1];
                doubleR[j + 1] = temp;
            }
        }
    }
}



void func01()
{
    int doubleR[6] = {0,0,0,0,0,0};
    int doubleB = rand() % 16 + 1;
    for (int i = 0;i < 6;i++)
    {
        int temp = rand() % 33 + 1;
        int testnum = 0;
        for (int j = 0;j < i;)
        {
            if (temp == doubleR[j])
            {
                j = 0;
                testnum = 0;
                temp = rand() % 33 + 1;
            }
            else
            {
                j++;
                testnum++;
            }
                
        }
        if (testnum == i)
        {
            doubleR[i] = temp;
            testnum = 0;
        }
    }
    bubbleUp(doubleR);
    showAns(doubleR,doubleB);
}

//幸运数字随机生成（可以设定幸运数字，不返回）
void lukyNumRandom(int lukyNum){
    //初始化红蓝区
    vector<int> doubleR = {0,0,0,0,0,0};
    int doubleB;
    // 启动随机数引擎
    mt19937 generator(lukyNum);
    uniform_int_distribution<int> redBall(1, 33);
    uniform_int_distribution<int> blueBall(1, 16);
    //生成随机数并存入红区数组
    for (int i=0; i<6; i++) {
        doubleR[i] = redBall(generator);
    }
    //升序排列红区号码
    sort(doubleR.begin(),doubleR.end());
    doubleB = blueBall(generator);
    showAns_vec(doubleR,doubleB);
}

//高级随机
void pureRandom(){
    
    //初始化红蓝区
    vector<int> doubleR = {0,0,0,0,0,0};
    int doubleB;
    // 启动随机数引擎
    unsigned randomSeed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(randomSeed);
    uniform_int_distribution<int> redBall(1, 33);
    uniform_int_distribution<int> blueBall(1, 16);
    //生成随机数并存入红区数组
    for (int i=0; i<6; i++) {
        doubleR[i] = redBall(generator);
    }
    //升序排列红区号码
    sort(doubleR.begin(),doubleR.end());
    doubleB = blueBall(generator);
    showAns_vec(doubleR,doubleB);
}

vector<int>redBallrandom(int redBallseed){
    //初始化红区
    vector<int> doubleR = {0,0,0,0,0,0};
    uniform_int_distribution<int> redBall(1, 33);
    for (int i=0; i<6; i++) {
        doubleR[i] = redBall(redBallseed);
    }
    //升序排列红区号码
    sort(doubleR.begin(),doubleR.end());
    return doubleR;
}
int blueBall(int blueballseed){
    //初始化蓝球
    int doubleB;
    mt19937 generator(blueballseed);
    uniform_int_distribution<int> blueBall(1, 16);
    doubleB = blueBall(generator);
    return doubleB;
}
