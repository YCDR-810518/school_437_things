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
void transferPoint(int *x1,int *x2,char *y1,char *y2);
void transferPoint2(int *x1,char *y1);

#endif
