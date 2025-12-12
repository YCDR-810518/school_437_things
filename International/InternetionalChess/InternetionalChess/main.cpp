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
// ==================== 跨平台 UTF-8 设置 ====================
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

int main(int argc, const char* argv[]) {

#if defined(_WIN32) || defined(_WIN64)
    // Windows 强制使用 UTF-8 编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 >nul");
#endif
    // macOS 和 Linux 默认就是 UTF-8，无需处理
    // =========================================================
    int choice;
        
        do {
            cout << "\n=== 国际象棋程序 ===" << endl;
            cout << "1. 显示当前棋盘" << endl;
            cout << "2. 移动棋子" << endl;
            cout << "3. 搜索棋盘上的棋子"<<endl;
            cout << "4. 批量处理棋子移动" <<endl;
            //cout <<"显示历史记录（十条）"<<endl;
            cout << "5. 退出程序" << endl;
            cout << "请选择操作: ";
            if(cin >> choice){
                
            }else{
                cout << "输入错误！\n";
                break;
            }
            
            
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
                    
                case 3:
                    char x; int y;
                    cout << "请输入要查询的区间 格式（字母+空格+数字）:";
                    cin >> x >> y;
                    transferPoint2(&y, &x);  // 用 transferPoint2
                    if (y < 0 || y > 7) {  // 添加检查
                        cout << "坐标越界！" << endl;
                        break;
                    }
                    cout << searchChessBox(x, y) << endl;
                    break;
                case 4:
                    displayChess();
                    batch_display();
                    break;
                case 5:
                    cout << "谢谢使用！" << endl;
                    break;
                    
                default:
                    cout << "无效选择，请重新输入！" << endl;
                    break;
            }
            
        } while (choice != 5);
    return 0;
}
