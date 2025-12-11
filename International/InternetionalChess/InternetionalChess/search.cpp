//
//  search.cpp
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/18.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int chessColorMap[8][8] = {
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {0,0,0,0,0,0,0,0},  // 修正了数组初始化
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

void transferPoint(int *x1,int *x2,char *y1, char *y2){
    *x1 = abs(*x1 - 8);
    *x2 = abs(*x2 - 8);
    *y1-='a';
    *y2-='a';
}
// 全局棋盘数组 - 使用 vector 避免数组问题
vector<vector<string>> chessMap = {
    {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"},
    {"pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"Pawn", "Pawn", "Pawn", "Pawn", "Pawn", "Pawn", "Pawn", "Pawn"},
    {"Rook", "Knight", "Bishop", "Queen", "King", "Bishop", "Knight", "Rook"}
};

string searchChessBox(char x, int y){
    return chessMap[y][x];
}

string searchColor(char x, int y){
    if (chessColorMap[y][x] == -1) {  // 注意行列顺序
        return "White";
    }
    if (chessColorMap[y][x] == 0) {
        return "Blank";
    }
    if (chessColorMap[y][x] == 1) {
        return "Black";
    } else {
        return "ChessColorError ";
    }
}

// 删除了 searchRecord 函数的重复定义
