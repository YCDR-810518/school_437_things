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
#include "display.h"
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
    
    for (int i = startIndex; i < (int)colorHistory.size(); i++) {
        cout << (i - startIndex + 1) << "\t"
             << colorHistory[i] << "\t"
             << chessTypeHistory[i] << "\t("
             << lengthHistory[i] << ","
             << verticalHistory[i] << ")\n";
    }
}

#include <vector>
#include <limits>

void batch_display() {
    char startPointx, endPointx;
    int startPointy, endPointy;
    int count = 0;
    string line;
    vector<string> commandPool; // 用于存储所有粘贴进来的指令
    
    // 清理之前输入 4 和 1 时留在缓冲区里的回车符
    if (cin.peek() == '\n') cin.ignore();

    cout << '\n' << "-----------------" << endl;
    cout << "【单步执行模式】" << endl;
    cout << "请粘贴/输入多行数据，输入完后请【连按两次回车】开始执行：" << endl;

    // 1. 阶段一：一次性读入所有行，直到遇到空行
    while (getline(cin, line) && !line.empty()) {
        commandPool.push_back(line);
    }
    
    // 2. 阶段二：遍历指令池，实现单步控制
    for (const string& currentLine : commandPool) {
        // 每一步开始前，先等待按键
        cout << "\n>>> [待机] 按任意键执行下一步..." << flush;
        waitAnyKey();

        stringstream ss(currentLine);
        string cmd;
        ss >> cmd;

        if (cmd == "悔棋") {
            if (regret()) {
                cout << "悔棋成功！！" << endl;
                if (count > 0) count--;
            } else {
                cout << "悔棋失败！！" << endl;
            }
            displayChess();
            continue;
        } else {
            // 解析坐标
            stringstream ss2(currentLine);
            if (ss2 >> startPointx >> startPointy >> endPointx >> endPointy) {
                cout << '\n' << "----------------------" << endl;
                
                int sy = startPointy, ey = endPointy;
                char sx = startPointx, ex = endPointx;
                transferPoint(&sy, &ey, &sx, &ex);
                string color = searchColor(sx, sy);

                // 轮次检查
                if (!excPosit(color)) {
                    cout << "轮次错误！请等待对方走棋。" << endl;
                    displayChess();
                    continue;
                }

                cout << "第" << ++count << "步 (" << currentLine << ")：" << endl;

                // 记录历史节点
                if (headptr == NULL) {
                    currentptr = creat(startPointx, startPointy, endPointx, endPointy);
                } else {
                    currentptr = newNode(startPointx, startPointy, endPointx, endPointy, currentptr);
                }

                // 执行移动
                bool success = moveChess(sx, sy, ex, ey);

                if (!success) {
                    deleteNode();
                    cout << "移动失败，不记录历史。" << endl;
                    count--;
                }

                displayChess();
                cout << "----------------------" << endl;
            } else {
                cout << "格式错误，跳过：" << currentLine << endl;
            }
        }
    }
    cout << "\n所有批量指令处理完毕！" << endl;
}
//处理文本批量输入并输出显示
void batch_displayTXT() {
    char startPointx, endPointx;
    int startPointy, endPointy;
    int count = 0;
    string line;
    vector<string> commandPool;

        // 1. 彻底清理进入函数前的缓冲区残留
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string fileName = "inputstep.txt";
        ifstream infile(fileName);

        // 如果直接打不开，尝试在常见的 macOS 编译输出目录下查找
        if (!infile.is_open()) {
            // 尝试上一级目录（通常源码在 build 文件夹的上一层）
            infile.open("../" + fileName);
        }
        
        if (!infile.is_open()) {
            // 针对你的截图路径进行特定尝试
            infile.open("InternetionalChess/InternetionalChess/" + fileName);
        }

        if (!infile.is_open()) {
            cout << "错误：找不到 inputstep.txt 文件！" << endl;
            cout << "[提示] 请确保文件位于程序运行的当前目录中。" << endl;
            // 打印出当前程序到底在哪个目录下运行，方便排查
            // system("pwd"); // macOS/Linux 可用
            return;
        }

    // 3. 预读文件所有指令到 vector
    while (getline(infile, line)) {
        if (!line.empty()) {
            commandPool.push_back(line);
        }
    }
    infile.close();

    if (commandPool.empty()) {
        cout << "文件为空，没有指令可执行。" << endl;
        return;
    }

    cout << "成功读取 " << commandPool.size() << " 条指令，准备单步执行。" << endl;

    // 4. 开始单步循环
    for (const string& currentLine : commandPool) {
        // 阻塞等待按键，实现“按一次走一步”
        cout << "\n>>> [文件模式] 下一步: " << currentLine << " | 按任意键继续..." << flush;
        waitAnyKey();

        stringstream ss(currentLine);
        string cmd;
        ss >> cmd;

        if (cmd == "悔棋") {
            if (regret()) {
                cout << "悔棋成功！！" << endl;
                if (count > 0) count--;
            }
            displayChess();
            continue;
        }

        // 解析坐标
        stringstream ss2(currentLine);
        if (ss2 >> startPointx >> startPointy >> endPointx >> endPointy) {
            cout << '\n' << "----------------------" << endl;
            
            // 预转换坐标用于检查
            int sy = startPointy, ey = endPointy;
            char sx = startPointx, ex = endPointx;
            transferPoint(&sy, &ey, &sx, &ex);
            
            // 轮次检查
            string color = searchColor(sx, sy);
            if (!excPosit(color)) {
                cout << "轮次错误！跳过此步。" << endl;
                displayChess();
                continue;
            }

            cout << "第" << ++count << "步：" << endl;

            // 记录节点
            if (headptr == NULL) {
                currentptr = creat(startPointx, startPointy, endPointx, endPointy);
            } else {
                currentptr = newNode(startPointx, startPointy, endPointx, endPointy, currentptr);
            }

            // 执行移动 (这里注意不要重复转换坐标)
            bool success = moveChess(sx, sy, ex, ey);

            if (!success) {
                deleteNode(); // 失败回滚
                cout << "移动失败，不记录历史。" << endl;
                count--;
            }

            displayChess();
            cout << "----------------------" << endl;
        } else {
            cout << "忽略非法格式行：" << currentLine << endl;
        }
    }
    cout << "\n文件批量指令执行完毕！" << endl;
}
void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        // Windows 系统代码
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__)
        // Linux 或 macOS 系统代码
        system("clear");
    #else
        // 其他未知系统
        std::cout << std::endl;
    #endif
}


#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

void waitAnyKey() {
    cout << ">>> 按任意键(不要按回车，程序会卡死)继续下一步...";
#if defined(_WIN32) || defined(_WIN64)
    _getch(); // Windows 直接读一个键
#else
    // Linux/macOS 关闭缓冲区读一个键
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    cout << "\r" << string(30, ' ') << "\r"; // 清除提示行
}
