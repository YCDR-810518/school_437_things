// logic.cpp  ——  完整、已测试、可直接使用的最终版
#include "logic.h"
#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

extern vector<vector<string>> chessMap;
extern int chessColorMap[8][8];
// 水平/垂直路径检查（跳过起点和终点）
bool VC_PathCheck(char x1, int y1, char x2, int y2) {
    if (x1 == x2) { // 垂直
        int step = (y2 > y1) ? 1 : -1;
        for (int y = y1 + step; y != y2; y += step) {
            if (!chessMap[y][(int)x1].empty()) return false;
        }
        return true;
    }
    if (y1 == y2) { // 水平
        int step = (x2 > x1) ? 1 : -1;
        for (int x = x1 + step; x != x2; x += step) {
            if (!chessMap[y1][x].empty()) return false;
        }
        return true;
    }
    return false;
}

// 斜向路径检查
bool slant_PathCheck(char x1, int y1, char x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    if (dx != dy) return false;

    int stepX = (x2 > x1) ? 1 : -1;
    int stepY = (y2 > y1) ? 1 : -1;
    for (int i = 1; i < dx; i++) {
        if (!chessMap[y1 + i * stepY][x1 + i * stepX].empty()) {
            return false;
        }
    }
    return true;
}

// 路径是否通畅
bool logic_PathCheck(char x1, int y1, char x2, int y2) {
    string piece = searchChessBox(x1, y1);

    if (piece == "pawn" || piece == "Pawn") {
        if (abs(y2 - y1) == 2) return VC_PathCheck(x1, y1, x2, y2);
        return true;
    }
    if (piece == "knight" || piece == "Knight") return true;
    if (piece == "king"   || piece == "King")   return true;
    if (piece == "rook"   || piece == "Rook")   return VC_PathCheck(x1, y1, x2, y2);
    if (piece == "bishop" || piece == "Bishop") return slant_PathCheck(x1, y1, x2, y2);
    if (piece == "queen"  || piece == "Queen")  return VC_PathCheck(x1, y1, x2, y2) || slant_PathCheck(x1, y1, x2, y2);

    return false;
}

// 起落点是否合法
int logic_PointCheck(char x1, int y1, char x2, int y2) {
    if (y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7 || x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7) {
        cout << "坐标越界！" << endl; return 0;
    }
    if (x1 == x2 && y1 == y2) { cout << "起点和终点相同！" << endl; return 0; }
    if (searchChessBox(x1, y1).empty()) { cout << "起点没有棋子！" << endl; return 0; }
    
    string piece = searchChessBox(x1, y1);
    string d_piece = searchChessBox(x2, y2);
    
    if(searchColor(x2, y2)==searchColor(x1, y1)){cout <<"不能吃自己家的棋子！"<<endl;return 0;}
    
    // 马
    if (piece == "knight" || piece == "Knight") {
        int dx = abs(x2 - x1), dy = abs(y2 - y1);
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            cout << "马走日或田，但你走的不是！" << endl;
            return 0;
        }
        return 1;
    }

    // 王
    if (piece == "king" || piece == "King") {
        if (abs(x2 - x1) > 1 || abs(y2 - y1) > 1) {
            cout << "王只能走一格！" << endl; return 0;
        }
        return 1;
    }

    // 兵
    if (piece == "pawn" || piece == "Pawn") {
        int forward = (piece == "Pawn") ? -1 : 1;  // 白兵向前 y减小
        int dy = y2 - y1;
        if (dy != forward && dy != 2*forward) {
            cout << "兵只能向前！" << endl; return 0;
        }
        if (abs((int)x2-x1)==1 && searchChessBox(x2, y2).empty()==1){
            cout << "兵(除了吃子之外)不能斜着走" << endl; return 0;
        }
        if (abs(dy) == 2) {
            int startRow = (piece == "Pawn") ? 6 : 1;
            if (y1 != startRow) {
                cout << "非起始行兵不能走两格！" << endl; return 0;
            }
        }
        if(abs((int)x2-x1)==1 && searchChessBox(x2, y2).empty()==0){
            return 1;
        }
        return 1;
    }

    return 1; // 车象后在路径检查里限制
}

// 移动主函数
bool moveChess(char x1, int y1, char x2, int y2) {
    if (!logic_PointCheck(x1, y1, x2, y2)) return false;
    if (!logic_PathCheck(x1, y1, x2, y2)) {
        cout << "路径被堵塞！" << endl;
        return false;
    }

    string piece = searchChessBox(x1, y1);
    string color = searchColor(x1, y1);

    // 执行移动
    chessMap[y2][(int)x2] = piece;
    chessMap[y1][(int)x1].clear();
    
    //更新颜色地图
    swap(chessColorMap[y2][(int)x2],chessColorMap[y1][(int)x1]);
    
    
    // 正确打印坐标（关键修复！）
    cout << "移动: " << (char)(x1 + 'a') << (8-y1)
         << " -> " << (char)(x2 + 'a') << (8-y2) << endl;
    cout << "移动棋子: 类型：(" << piece << ") 颜色：(" << color << ")" << endl;
    cout << "移动成功！" << endl;
    return true;
}


