//
//  menu.h
//  randomTwoColorBall
//
//  Created by 姚晨 on 2025/11/11.
//
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <vector>
using namespace std;
//主菜单
void showMenu();
//随机取号次级菜单
void showMenu_1_sec();

//结果输出函数,分左右输出两个区的内容
void showAns(int doubleR[],int doubleB);
//可以接受vector数组
void showAns_vec(vector<int>doubleR,int doubleB);
//作者的留言区
void func02();
#endif
