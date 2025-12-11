//
//  logic.h
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/25.
//
#ifndef _LOGIC_H_
#define _LOGIC_H_
#include <iostream>
#include <vector>
#include <string>
//起落点逻辑判断
//横向是字母，竖向是数字
/*
int logic_PointCheck(char x1, int y1, char x2, int y2);
bool logic_PathCheck(char x1, int y1, char x2, int y2);
*/
bool moveChess(char stalength, int stavertical, char endlength, int endvertical);
#endif
