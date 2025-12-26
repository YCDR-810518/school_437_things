//
//  search.h
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/18.
//
#ifndef _SEARCH_H_
#define _SEARCH_H_
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 查询各个位置的情况
string searchChessBox(char x, int y);
string searchColor(char x, int y);
void transferPoint(int *y1,int *y2,char *x1, char *x2);
void transferPoint2(int *x1,char *y1);

//链表相关说明
/*
 使用说明：
 1.一定要在执行移动，改变map之前记录！！！
 2.内置转换，不影响外界（独立）
 */
typedef struct ProcessRecordNode {
    char lastx;       // 上次位置的 x（列，通常 'a' 到 'h'）
    int lasty;        // 上次位置的 y（行，通常 1 到 8）
    char currentx;    // 当前位置的 x
    int currenty;     // 当前位置的 y
    string movedColor; // 移动棋子时的颜色
    string movedType;   //移动棋子的类型
    string eatType;     //被吃掉棋子的类型（没吃子则为空）
    string eatColor;     // 吃子时的颜色（没吃子则为空）
    int num;          //表明这是第几步
    struct ProcessRecordNode* next;  // 指向下一个节点（链表用）
} ProcessRecordNode;


extern ProcessRecordNode* headptr;
extern ProcessRecordNode* currentptr;
extern ProcessRecordNode* lastptr;
//开辟链表
ProcessRecordNode* creat(char lastx, int lasty, char currentx, int currenty);
//新增链表
ProcessRecordNode* newNode(char lastx, int lasty, char currentx, int currenty,ProcessRecordNode* next);
//删除最后一个节点（悔棋）
void deleteNode();
//输出节点内容(从末尾开始)
void outputNode();
//输出节点内容(从末尾开始)
void outputTXT();

//以下是建立棋谱所需的函数声明
#include <fstream>
#endif
