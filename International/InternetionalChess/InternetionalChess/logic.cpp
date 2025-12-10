#include "logic.h"
#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>  // 添加cmath头文件用于abs()函数
using namespace std;

extern int chessColorMap[8][8];
extern vector<vector<string>> chessMap;


//这个函数要检测起落点的路径上
int logic_PathCheck(char x1, int y1, char x2, int y2) {


    return 0;
}


int logic_PointCheck(char x1, int y1,
                     char x2, int y2){
    int logic_choice;
    
    // 基础检查 - 修复了水平方向检查逻辑
    if(x1 > 8 || x2 > 8) {
        cout << "你在竖直方向超越了棋盘";
        return 0;
    }
    if (y1 <= 0 || y2 <= 0) {
        cout << "棋盘上莫得负数，沙锅";
        return 0;
    }
    // 修复：水平方向检查条件写反了
    if (x1 < 0 || x1 > 'h'-97 || x2 < 0 || x2 > 'h'-97) {
        cout << "你在水平方向超越了棋盘";
        return 0;
    }
    if (searchChessBox(x1,y1).empty()) {
        cout << "起始点象棋不存在"  << endl;
        return 0;
    }else{
        cout<<"基础检查出现了未知错误！"<<endl;
    }
    
    // 获取棋子类型

    if (const string piece = searchChessBox(x1,y1); piece == "pawn" || piece == "Pxawn") {
        logic_choice =1;
    }else if (piece == "rook" || piece == "Rook") {
        logic_choice =2;
    }else if (piece == "knight" || piece == "Knight") {
        logic_choice =3;
    }else if (piece == "bishop" || piece == "Bishop") {
        logic_choice =4;
    }else if (piece == "queen" || piece == "Queen") {
        logic_choice =5;
    }else if (piece == "king" || piece == "King") {
        logic_choice =6;
    }else{
        cout << "logic_PointCheck函数中的前半段判断存在未知错误" << endl;
        return 0;
    }
    

    
    switch (logic_choice) {
        case 1: // 兵(Pawn)的逻辑
        {
            int foot = 1;
            if(searchColor(x1, y1)=="White"){
                foot = -1;
            }else
            {
                foot = 1;
            }
            if(y1==2||y1==7)
            {
                if(y2==(y1+foot)||y2==(y1+foot*2))return 1;
                else return 0;
            }
            if(y1!=2&&y1!=7)
            {
                if(y2==y1+foot)return 1;
                else return 0;
            }
            break;
        }
            
        case 2: // 车(Rook)的逻辑
        {
            // 车只能横向或纵向移动
            
            break;
        }
            
        case 3: // 马(Knight)的逻辑
        {
            // 马走日字 (L形移动)
            
            break;
        }
            
        case 4: // 象(Bishop)的逻辑
        {
            // 象只能斜向移动
            
            break;
        }
            
        case 5: // 后(Queen)的逻辑
        {
            // 后可以横向、纵向或斜向移动
            
            break;
        }
            
        case 6: // 王(King)的逻辑
        {
            
            break;
        }
            
        default:
            cout << "CHESS ACTION LOGIC ERROR!" << endl;
            return 0;
    }
    
    return 0;
}

// 移动棋子函数
bool moveChess(char x1, int y1, char x2, int y2) {
    // 首先检查移动是否合法
    if (logic_PointCheck(x1, y1, x2, y2) == 0) {
        cout << "移动不合法！" << endl;
        return false;
    }

    // 转换为数组索引
    int startRow = 8 - y1;
    int startCol = x1 - 'a';
    int endRow = 8 - y2;
    int endCol = x2 - 'a';
    
    // 保存移动前的棋子信息（用于显示）
    //类型
    string movedPiece = chessMap[y1][x1];
    //颜色
    int movedPieceColor = chessColorMap[y1][x1];
    
    // 执行移动 - 更新棋盘数组
    chessMap[endRow][endCol] = chessMap[y1][x1];
    chessMap[y1][x1] = "";
    
    // 执行移动 - 更新颜色映射数组
    chessColorMap[endRow][endCol] = chessColorMap[y1][x1];
    chessColorMap[y1][x1] = 0; // 0 表示空白
    
    // 显示移动信息
    cout << "移动: " << x1 << y1 << " -> " << x2 << endvertical << endl;
    cout << "移动棋子: " << movedPiece << " (";
    if(movedPieceColor==-1){
        cout << "白方" <<")" << endl;
    }else{
        cout << "黑方" <<")" << endl;
    }
    
    cout << "移动成功！" << endl;
    
    return true;
}
