//
//  main.cpp
//  randomTwoColorBall
//
//  Created by 姚晨 on 2025/11/11.
//

//双色球自动取号 2025年11月10日22:20:11 @by hjc

#include<iostream>
#include<ctime>
#include "display.h"
#include "randomEngine.h"
using namespace std;

int main()
{
    srand((unsigned int)time(NULL));
    cout << "欢迎使用双色球随机取号器，很高兴能为您服务！" << endl;
    cout << endl;
    system("pause");
    system("cls");

    while (true)
    {
        showMenu();

        int ans = 0;
        cout << endl;
        cout << "请输入对应数字：";
        cin >> ans;

        switch (ans)
        {

        case 1:
        {
            
            func01();
            system("pause");
            system("cls");
            break;
        }

        case 2:
        {
            showMenu_1_sec();
            ans = 0;
            cout << endl;
            cout << "请输入对应数字：";
            cin >> ans;
            switch (ans) {
                case 1:
                    func02();
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    int lukyNum;
                    cout << endl;
                    cout << "请输入你的幸运数字：";
                    cin >> lukyNum;
                    lukyNumRandom(lukyNum);
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    pureRandom();
                    system("pause");
                    system("cls");
                    break;
                case 4:
                default:
                    cout << "您输入的内容无效，请重试！" << endl;
                    system("pause");
                    system("cls");
                    break;
            }
        }

        case 3:
        {
            cout << "再见，欢迎下次使用，祝您生活愉快！" << endl;
            system("pause");
            return 0;
        }

        default:
        {
            cout << "您输入的内容无效，请重试！" << endl;
            system("pause");
            system("cls");
            break;
        }

        }

    }
    
    system("pause");
    return 0;
}
