//
//  main.cpp
//  InternetionalChess
//
//  Created by 姚晨 on 2025/11/11.
//
//白方开头小写，黑方开头大写
#include <iostream>
#include "display.h"
#include "search.h"
#include "logic.h"
using namespace std;
int main(int argc, const char * argv[]) {
    int choice;
        
        do {
            cout << "\n=== 国际象棋程序 ===" << endl;
            cout << "1. 显示当前棋盘" << endl;
            cout << "2. 移动棋子" << endl;
            cout << "3. 搜索棋盘上的棋子"<<endl;
            //cout <<"显示历史记录（十条）"<<endl;
            cout << "4. 退出程序" << endl;
            cout << "请选择操作: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    displayChess();
                    break;
                case 2:
                    displayChess();  // 先显示当前棋盘
                    char stalength; int stavertical;
                    char endlength; int endvertical;
                    cout << "起点/终点格式（字母+空格+数字）\n";
                    cout << "请输入起点:";
                    cin >> stalength >> stavertical;
                    cout << "请输入终点:";
                    cin >> endlength >> endvertical;
                    transferPoint(&stavertical,&endvertical,&stalength,&endlength);
                    moveChess(stalength,stavertical, endlength, endvertical);
                    displayChess();  // 显示移动后的棋盘
                    searchRecord(searchColor(endlength,endvertical),
                                 searchChessBox(endlength,endvertical),
                                 endlength,endvertical, -1);
                    
                    break;
                    
                case 4:
                    cout << "谢谢使用！" << endl;
                    break;
                default:
                    cout << "无效选择，请重新输入！" << endl;
                    break;
            }
            
        } while (choice != 4);
    return 0;
}
