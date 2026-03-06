#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"

unsigned char MartrixKey()
{
    unsigned char KeyNum = 0;
    unsigned char i, j, q;

    // 扫描4列
    for (j = 0; j < 4; j++)
    {
        // 设置所有列为高电平
        P1 = 0xFF;

        // 将当前列设置为低电平
        switch (j)
        {
        case 0: P1_3 = 0; break;  // 第1列
        case 1: P1_2 = 0; break;  // 第2列
        case 2: P1_1 = 0; break;  // 第3列
        case 3: P1_0 = 0; break;  // 第4列
        }

        // 检测行状态
        switch (j)
        {
        case 0:  // 第1列
            for (i = 7, q = 1; i >= 5; i--, q++)
            {
                if (i == 7 && P1_7 == 0) KeyNum = q;
                else if (i == 6 && P1_6 == 0) KeyNum = q;
                else if (i == 5 && P1_5 == 0) KeyNum = q;

                if (KeyNum != 0)
                {
                    Delay(10);  // 消抖
                    // 等待按键释放
                    if (i == 7) while (P1_7 == 0);
                    else if (i == 6) while (P1_6 == 0);
                    else if (i == 5) while (P1_5 == 0);
                    Delay(10);  // 消抖
                    return KeyNum;
                }
            }
            break;

        case 1:  // 第2列
            for (i = 7, q = 4; i >= 5; i--, q++)
            {
                if (i == 7 && P1_7 == 0) KeyNum = q;
                else if (i == 6 && P1_6 == 0) KeyNum = q;
                else if (i == 5 && P1_5 == 0) KeyNum = q;

                if (KeyNum != 0)
                {
                    Delay(10);
                    if (i == 7) while (P1_7 == 0);
                    else if (i == 6) while (P1_6 == 0);
                    else if (i == 5) while (P1_5 == 0);
                    Delay(10);
                    return KeyNum;
                }
            }

            // 检查特殊按键
            if (P1_4 == 0)
            {
                Delay(10);
                while (P1_4 == 0);
                Delay(10);
                return 0;  // 返回0
            }
            break;

        case 2:  // 第3列
            for (i = 7, q = 7; i >= 5; i--, q++)
            {
                if (i == 7 && P1_7 == 0) KeyNum = q;
                else if (i == 6 && P1_6 == 0) KeyNum = q;
                else if (i == 5 && P1_5 == 0) KeyNum = q;

                if (KeyNum != 0)
                {
                    Delay(10);
                    if (i == 7) while (P1_7 == 0);
                    else if (i == 6) while (P1_6 == 0);
                    else if (i == 5) while (P1_5 == 0);
                    Delay(10);
                    return KeyNum;
                }
            }
            break;

        case 3:  // 第4列
            // 检查特殊按键
            if (P1_7 == 0)
            {
                Delay(10);
                while (P1_7 == 0);
                Delay(10);
								KeyNum = 0;
                return KeyNum;							// 返回0
            }

            // 检查其他按键
            for (i = 6, q = 10; i >= 5; i--, q++)
            {
                if (i == 6 && P1_6 == 0) KeyNum = q;
                else if (i == 5 && P1_5 == 0) KeyNum = q;

                if (KeyNum != 0)
                {
                    Delay(10);
                    if (i == 6) while (P1_6 == 0);
                    else if (i == 5) while (P1_5 == 0);
                    Delay(10);
                    return KeyNum;
                }
            }
            break;
        }
    }

    return KeyNum;  // 没有按键按下返回0
}