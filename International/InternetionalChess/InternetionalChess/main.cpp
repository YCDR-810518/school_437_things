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
#define CHOICEERROR 0
#define CHOICEMAX 8
using namespace std;
// ==================== 跨平台 UTF-8 设置 ====================
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
    #define PLATFORM_MACOS 1
#elif defined(__linux__)
    #define PLATFORM_LINUX 1
#endif

int main(void) {

#if PLATFORM_WINDOWS
    // Windows 强制使用 UTF-8 编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 >nul");
#endif

#if PLATFORM_MACOS
    // macOS 默认使用 UTF-8，无需特别设置
    // 可以添加 macOS 特定代码
#endif

#if PLATFORM_LINUX
    // Linux 默认使用 UTF-8，无需特别设置
#endif

    int choice;
        
        do {
            cout << "\n=== 国际象棋程序 ===" << endl;
            cout << "1. 显示当前棋盘" << endl;
            cout << "2. 移动棋子" << endl;
            cout << "3. 搜索棋盘上的棋子"<<endl;
            cout << "4. 批量处理棋子移动" <<endl;
            cout << "5. 显示历史记录（all）"<<endl;
            cout << "6. 悔棋（QAQ）"<<endl;
            cout << "7. 将下棋的历史输出为文本文件"<<endl;
            cout << "8. 退出程序" << endl;
            cout << "请选择操作: ";
            if(cin >> choice){
                
            }else{
                cout << "输入错误！\n";
                break;
            }
            
            
            switch (choice) {
                case 1:{
                    displayChess();
                    break;
                }
                case 2:{
                        displayChess();
                        char stalength; int stavertical;
                        char endlength; int endvertical;
                        cout << "起点/终点格式（字母+空格+数字）\n";
                        cout << "请输入起点:";
                        cin >> stalength >> stavertical;
                        cout << "请输入终点:";
                        cin >> endlength >> endvertical;
                        
                        // 先转换坐标（注意：transferPoint 修改原变量）
                        int start_y = stavertical, end_y = endvertical;
                        char start_x = stalength, end_x = endlength;
                        transferPoint(&start_y, &end_y, &start_x, &end_x);
                        
                        // 计算当前 color
                        string color = searchColor(start_x, start_y);
                        
                        // 提前检查轮次
                        if (!excPosit(color)) {
                            cout << "不能一人走两步！！" << endl;
                            displayChess();  // 还是显示棋盘
                            break;  // 跳过
                        }
                        
                        // 轮次OK，才创建节点
                        ProcessRecordNode* new_ptr = NULL;
                        if(headptr==NULL){
                            new_ptr = creat(stalength, stavertical, endlength, endvertical);
                            currentptr = new_ptr;
                        }else{
                            new_ptr = newNode(stalength, stavertical, endlength, endvertical, currentptr);
                            currentptr = new_ptr;
                        }
                        
                        // 已转换，再调用 moveChess
                        bool success = moveChess(start_x, start_y, end_x, end_y);
                        
                        if (!success) {
                            deleteNode();
                            currentptr = lastptr;
                            cout << "移动失败，不记录历史。" << endl;
                        } else {
                            lastptr = currentptr;
                        }
                        
                        displayChess();
                        break;
                }
                case 3:{
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
                }
                case 4:{
                    cout << "请选择使用控制台输入 (1)\n还是文本（txt）输入 (2)\n";
                    cout << "使用文本文件输入时请放在与程序相同的文件夹下" <<endl;
                    int input_choice;
                    cout << "请输入1/2:";
                    cin >>input_choice;
                    if(input_choice==1){
                        displayChess();
                        batch_display();
                    }
                    if (input_choice==2) {
                        displayChess();
                        batch_displayTXT();
                    }
                    break;
                }
                case 5: {//显示当前棋盘历史
                    if(headptr!=NULL){
                        outputNode();
                    }else{
                        cout <<"历史为空！！"<<endl;
                    }
                    break;
                }
                case 6:{     //悔棋
                    if(regret()){
                        cout <<"悔棋成功！！"<<endl;
                        displayChess();  // 显示悔棋后的棋盘
                    }else{
                        cout <<"悔棋失败！！"<<endl;
                    }
                    break;
                }
                case 7:{
                    cout << "正在将全部历史输出为TXT文件" <<endl;
                    outputTXT();
                    break;
                }
                case CHOICEMAX:{
                    cout << "谢谢使用！" << endl;
                    break;
                }
                default:{
                    cout << "无效选择，请重新输入！" << endl;
                    
                    break;
                }
            }
            
        } while (choice != 7 && (choice>CHOICEERROR && choice<CHOICEMAX));
    return 0;
}
