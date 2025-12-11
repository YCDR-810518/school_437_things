#include "logic.h"
#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>  // 添加cmath头文件用于abs()函数
using namespace std;


extern int chessColorMap[8][8];
extern vector<vector<string>> chessMap;

//(重要！！！)在所有逻辑判断语句之前要先转换坐标！！！
//逻辑顺序 1 起落点检测 2 路径检测 3 移动

//斜向检测
bool slant_PathCheck(char x1, int y1, char x2, int y2);
//水平垂直检测
bool VC_PathCheck(char x1, int y1, char x2, int y2);

//这个函数要检测起落点的路径上有无障碍物
bool logic_PathCheck(char x1, int y1, char x2, int y2);


//这个函数要检测起落点的路径上有无障碍物
bool logic_PathCheck(char x1, int y1, char x2, int y2) {
    
    int logic_choice;
    // 获取棋子类型
    if (const string piece = searchChessBox(x1,y1); piece == "pawn" || piece == "Pxawn") {
        logic_choice =1;
    }else if (piece == "rook" || piece == "Rook") {
        logic_choice =2;
    }else if (piece == "Knight" || piece == "knight") {
        logic_choice =3;
    }else if (piece == "bishop" || piece == "Bishop") {
        logic_choice =4;
    }else if (piece == "queen" || piece == "Queen") {
        logic_choice =5;
    }else if (piece == "king" || piece == "King") {
        logic_choice =6;
    }else{
        cout << "logic_PathCheck函数中的前半段棋子类型判断判断存在错误" << endl;
        return 0;
    }
    
    switch (logic_choice) {
        case 1:
            if(abs(y2-y1)==2)
            {if(VC_PathCheck(x1, y1, x2, y2))return true;}
            else return true;
            break;
            
        case 2:
            if(VC_PathCheck(x1, y1, x2, y2))return true;
            break;

        case 3:
            return true;
            break;
        case 4:
            if(slant_PathCheck(x1, y1, x2, y2))return true;
            break;
            
        case 5:
            if(VC_PathCheck(x1, y1, x2, y2)&&slant_PathCheck(x1, y1, x2, y2)){
                return true;
            }
            break;
            
        case 6:
            return true;
            break;
            
        default:
            cout << "路径检查逻辑存在错误"<<endl;
            break;
    }
    
    return 0;
}

//检查竖直和水平方向
bool VC_PathCheck(char x1, int y1, char x2, int y2){
    if (x1==x2) {
        for (int i = min(y1,y2); i<max(y1, y2); i++) {
            if (chessMap[i][(int)x1].empty()==0) {
                return false;
            }
        }
        return true;
    }
    if (y1==y2) {
        for (int i = min(x1,x2); i<max(x1, x2); i++) {
            if (chessMap[y1][i].empty()==0) {
                return false;
            }
        }
        return true;
    }
    else{
        throw "水平&竖直路径检查存在错误！";
        return false;
    }
}

//检查斜方向
bool slant_PathCheck(char x1, int y1, char x2, int y2){
    
    if ((int)x1<(int)x2) {
        if(y1<y2){
            for (int i=x1, j=y1; i==x2; i++,j++) {
                if(searchChessBox(i, j).empty()==0){
                    return false;
                }
            }
            return true;
        }else{
            for (int i=x1, j=y2; i==x2; i++,j++) {
                if(searchChessBox(i, j).empty()==0){
                    return false;
                }
            }
            return true;
        }
    }else{
        if (y1<y2) {
            for (int i=x2, j=y1; i==x1; i++,j++) {
                if(searchChessBox(i, j).empty()==0){
                    return false;
                }
            }
            return true;
        }else{
            for (int i=x2, j=y2; i==x1; i++,j++) {
                if(searchChessBox(i, j).empty()==0){
                    return false;
                }
            }
            return true;
        }
    }
}


//检查起点和落点的合法性（不要越界）
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
    
    if(x1==x2 && y1==y2){
        cout << "你没动！";
        return 0;
    }
    
    if (searchChessBox(x1,y1).empty()) {
        cout << "起始点象棋不存在"  << endl;
        return 0;
    }
    
    if(searchChessBox(x1, y1)=="Knight" || "knight"){
        if((abs(x2-x1)+abs(y2-y1))!=3){
            return 0;
        }
    }
    
    if(searchChessBox(x1, y1)=="Pawn" || "pawn"){
        if(searchChessBox(x1, y1)=="Pawn"){
            if((y2-y1)<0)return 0;
        }if(searchChessBox(x1, y1)=="pawn"){
            if((y2-y1)>0)return 0;
        }
        if(x1==0||x1==6){
            if (abs(y2-y1)<=2) {
                return 1;
            }
            else{
                return 0;
            }
        }else{
            if(abs(y2-y1)!=1) return 0;
        }
    }
    
    if(searchChessBox(x1, y1)=="King" || "king"){
        if((abs(x2-x1)+abs(y2-y1))!=1){
            return 0;
        }
    }
    return 1;
}

// 移动棋子函数(要先检查起落点和路径的合法性！！)
bool moveChess(char x1, int y1, char x2, int y2) {
    
    //储存移动棋子的类型，颜色
    string chessType, chessColor;
    chessType = searchChessBox(x1, y1);
    chessColor = searchColor(x1, y1);
    bool MOVE = false;
    
    if(logic_PointCheck(x1,y1,x2,y2)){
        if(logic_PathCheck( x1, y1, x2, y2)){
            //移动并改变Chess地图
            if(chessMap[y2][(int)x2].empty()){
                swap(chessMap[y2][(int)x2], chessMap[y1][(int)x1]);
                MOVE=true;
            }else{
                chessMap[y2][(int)x2].clear();
                chessMap[y2][(int)x2]=chessMap[y1][(int)x1];
                chessMap[y1][(int)x1].clear();
                MOVE=true;
            }
        }else MOVE=false;
    }
    else MOVE=false;
    //信息显示
    if(MOVE==true)
    {
        // 显示移动信息
        cout << "移动: " << x1+'a' << y1 << " -> " << x2+'a' << y2 << endl;
        cout << "移动棋子: " << "类型：（" <<chessType<<"） 颜色：（"<<chessColor<<"）";
        cout << "移动成功！" << endl;
        return true;
    }else{
        cout << "移动失败！"<<endl;
        return false;
    }
}
