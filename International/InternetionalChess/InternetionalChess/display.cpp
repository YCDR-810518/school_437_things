//
//  display.cpp
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/11.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "search.h"
#include "logic.h"
#include <limits>
using namespace std;
extern vector<vector<string>> chessMap;

// 显示棋盘函数
void displayChess() {
    cout << "\t" << "a\t" << "b\t" << "c\t" << "d\t" << "e\t" << "f\t" << "g\t" << "h\t" << endl;
    cout << "   ---------------------------------------------------------" << endl;
    
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " |\t";  // 显示行号
        
        for (int j = 0; j < 8; j++) {
            if (chessMap[i][j].empty()) {
                cout << ".\t";  // 空位置用点表示
            } else {
                // 显示棋子名称的前4个字符，保持对齐
                string piece = chessMap[i][j].substr(0, 4);
                cout << piece << "\t";
            }
        }
        cout << "| " << 8 - i << endl;
    }
    
    cout << "   ---------------------------------------------------------" << endl;
    cout << "\t" << "a\t" << "b\t" << "c\t" << "d\t" << "e\t" << "f\t" << "g\t" << "h\t" << endl;
}


// 全局历史记录数组（放在函数外部）
vector<string> colorHistory;
vector<string> chessTypeHistory;
vector<int> verticalHistory;
vector<char> lengthHistory;

void searchRecord(string color, string chessType, int vertical, char length, int display) {
    // 1. 添加当前记录到历史
    colorHistory.push_back(color);
    chessTypeHistory.push_back(chessType);
    verticalHistory.push_back(vertical);
    lengthHistory.push_back(length);
    
    // 2. 保持最多10条记录
    if (colorHistory.size() > 10) {
        colorHistory.erase(colorHistory.begin());
        chessTypeHistory.erase(chessTypeHistory.begin());
        verticalHistory.erase(verticalHistory.begin());
        lengthHistory.erase(lengthHistory.begin());
    }
    
    // 3. 根据display参数决定是否显示
    if (display == -1) {
        return;  // 不显示，只记录
    }
    
    // 4. 显示逻辑
    int showCount = display;
    if (display == 0) {
        showCount = colorHistory.size();  // 显示全部
    } else {
        showCount = min(display, (int)colorHistory.size());  // 显示指定条数
    }
    
    // 5. 显示记录
    cout << "\tcolor\tchessType\tLocation\n";
    int startIndex = colorHistory.size() - showCount;  // 从最近的记录开始显示
    
    for (int i = startIndex; i < colorHistory.size(); i++) {
        cout << (i - startIndex + 1) << "\t"
             << colorHistory[i] << "\t"
             << chessTypeHistory[i] << "\t("
             << lengthHistory[i] << ","
             << verticalHistory[i] << ")\n";
    }
}

//处理批量输入并进行显示
void batch_display(){
    char startPointx, endPointx;
    int startPointy, endPointy;
    int count = 0;

    cout <<'\n'<< "-----------------" <<endl;
    cout <<"请输入多行数据（格式：e 2 e 4），输入完后直接再按一次回车结束：\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // 关键修复：改成先读一行，再用 stringstream 解析
    string line;
    while (getline(cin, line)) {
        // 如果是空行，就退出（用户按了两次回车）
        if (line.empty()) {
            cout << "\n检测到空行，批量走棋结束！" << endl;
            break;
        }

        stringstream ss(line);
        if (ss >> startPointx >> startPointy >> endPointx >> endPointy) {
            cout <<'\n'<< "----------------------" <<endl;
            cout <<"第"<< ++count <<"步："<<endl;

            transferPoint(&startPointy, &endPointy, &startPointx, &endPointx);
            moveChess(startPointx, startPointy, endPointx, endPointy);
            displayChess();

            cout << "----------------------" <<endl;
        } else {
            cout << "这行格式不对，已忽略：" << line << endl;
        }
    }
}

