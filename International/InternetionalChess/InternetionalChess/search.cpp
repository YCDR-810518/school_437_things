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
#include <fstream>
#include "search.h"
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
//全局指针
ProcessRecordNode* headptr = NULL;
ProcessRecordNode* currentptr = NULL;
ProcessRecordNode* lastptr = NULL;

//这里弄反了，不好改，将就着用吧
void transferPoint(int *y1,int *y2,char *x1, char *x2){
    *y1 = abs(*y1 - 8);
    *y2 = abs(*y2 - 8);
    *x1-='a';
    *x2-='a';
}

void transferPoint2(int *y1,char *x1){
    *y1 = abs(*y1 - 8);
    *x1-='a';
}


string searchChessBox(char x, int y){
    return chessMap[y][x];
}

string searchColor(char x, int y){
    if (chessColorMap[y][(int)x] == 1) {
        return "White";
    }
    if (chessColorMap[y][(int)x] == 0) {
        return "Blank";
    }
    if (chessColorMap[y][(int)x] == -1) {
        return "Black";
    } else {
        return "ChessColorError ";
    }
}


ProcessRecordNode* creat(char lastx, int lasty, char currentx, int currenty){
    ProcessRecordNode* node = (ProcessRecordNode*)malloc(sizeof(ProcessRecordNode));
    if (node == NULL) return NULL;
    
    
    headptr = node;
    
    node->lastx = lastx;
    node->lasty = lasty;
    node->currentx = currentx;
    node->currenty = currenty;  // ← 修复：原来漏了或错了
    
    node->num = 1;
    node->next = NULL;

    // 正确转换坐标
    char tx1 = lastx;
    int ty1 = lasty;
    char tx2 = currentx;
    int ty2 = currenty;
    transferPoint(&ty1, &ty2, &tx1, &tx2);

    node->movedColor = searchColor(tx1, ty1);
    node->movedType = searchChessBox(tx1, ty1);

    if (!searchChessBox(tx2, ty2).empty()) {
        node->eatType = searchChessBox(tx2, ty2);
        node->eatColor = searchColor(tx2, ty2);
    } else {
        node->eatType = node->eatColor = "";
    }
    
    return node;
}


// 新增链表节点（添加到末尾）
ProcessRecordNode* newNode(char lastx, int lasty, char currentx, int currenty, ProcessRecordNode* prev) {
    lastptr = prev;
    ProcessRecordNode* node = (ProcessRecordNode*)malloc(sizeof(ProcessRecordNode));
    if (node == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    // 基本位置信息
    node->lastx = lastx;
    node->lasty = lasty;
    node->currentx = currentx;
    node->currenty = currenty;

    // 连接到链表：prev 是上一个节点
    prev->next = node;   // 关键：上一个节点的 next 指向新节点
    node->next = NULL;   // 新节点是尾巴，next 为 NULL
    
    // 步数：上一节点 +1
    node->num = prev->num + 1;

    // 更新 endptr 指向最新节点

    // ====== 正确记录移动和吃子信息（用临时变量转换坐标）======
    int from_y = lasty;       // 用户输入的行号（如 2）
    int to_y   = currenty;    // 如 4
    char from_x = lastx;      // 'e'
    char to_x   = currentx;   // 'e'

    transferPoint(&from_y, &to_y, &from_x, &to_x);

    node->movedColor = searchColor(from_x, from_y);
    node->movedType  = searchChessBox(from_x, from_y);

    string targetPiece = searchChessBox(to_x, to_y);
    if (!targetPiece.empty()) {
        node->eatType  = targetPiece;
        node->eatColor = searchColor(to_x, to_y);
    } else {
        node->eatType  = "";
        node->eatColor = "";
    }
    // ============================================================

    return node;
}

// 使用双重指针操作（保持你原来的风格）
void deleteNode() {
    if (headptr == nullptr) {
        cout << "链表为空，无法删除" << endl;
        return;
    }
    
    // 情况1: 如果只有一个节点
    if (headptr->next == nullptr) {
        delete headptr;
        headptr = nullptr;
        currentptr = nullptr; // [关键] 更新全局指针
        lastptr = nullptr;
        cout << "删除唯一节点成功" << endl;
        return;
    }
    
    // 情况2: 有多个节点，寻找倒数第二个节点
    ProcessRecordNode* p = headptr;
    while (p->next->next != nullptr) {
        p = p->next;
    }
    
    // 此时 p 是倒数第二个节点
    ProcessRecordNode* tailNode = p->next;
    p->next = nullptr;  // 断开连接
    
    delete tailNode;    // 释放内存
    
    //更新全局指针指向新的末尾
    currentptr = p;
    // 如果需要的话，也可以在这里尝试修复 lastptr，但对于单向链表，lastptr通常指"前一个"，
    // 在下一次newNode时会被重置，所以这里核心是保证 currentptr 指向有效的末尾。

    cout << "删除尾节点成功" << endl;
}


void outputNode(){
    if (headptr == NULL) {
        cout << "历史记录为空！" << endl;
        return;
    }

    ProcessRecordNode *p = headptr;  // 从头开始

    int step = 1;
    while (p != NULL) {
        cout << "第 " << step << " 步（记录编号 " << p->num << "）：\n";
        cout << "  移动： " << p->lastx << p->lasty
             << " -> " << p->currentx << p->currenty << endl;
        cout << "  移动棋子： " << p->movedType
             << "  颜色： " << p->movedColor << endl;

        if (p->eatType != "") {
            cout << "  吃子： " << p->eatType
                 << "  颜色： " << p->eatColor << endl;
        }
        cout << endl;  // 分隔每一步

        p = p->next;
        step++;
    }
    cout << "=== 历史移动记录（共 " << step-1 << " 步） ===\n" << endl;
    
    cout << "=== 记录结束 ===\n" << endl;
}

void outputTXT(){
    if (headptr == NULL) {
        cout << "历史记录为空！" << endl;
        return;
    }
    
    ProcessRecordNode *p = headptr;  // 从头开始
    unsigned long long step = 1;
    ofstream outfile;
    outfile.open("outfile.txt");
    while (p != NULL) {
        outfile << "第 " << step << " 步（记录编号 " << p->num << "）：\n";
        outfile << "  移动： " << p->lastx << p->lasty
             << " -> " << p->currentx << p->currenty << endl;
        outfile << "  移动棋子： " << p->movedType
             << "  颜色： " << p->movedColor << endl;

        if (p->eatType != "") {
            outfile << "  吃子： " << p->eatType
                 << "  颜色： " << p->eatColor << endl;
        }
        outfile << endl;  // 分隔每一步

        p = p->next;
        step++;
    }
    outfile << "=== 历史移动记录（共 " << step-1 << " 步） ===\n" << endl;
    
    outfile << "=== 记录结束 ===\n" << endl;
    outfile.close();
}

void outputPGN(){
    ofstream outfile;
    outfile.open("game.pgn");
    outfile << "[Event \"Casual Game\"]"<<endl;
    outfile << "[White\"YaoChen\"]"<<endl;
}
/*
 #include <cctype>
 
 char lower = 'n';
 char upper = std::toupper(lower); // 结果为 'N'
 
 
 if()
 */
