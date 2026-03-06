#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
#include "MartrixKey.h"

void main()
{
    unsigned char KeyNum;
    unsigned char NumLockarr[9]; // 设置密码的缓冲区
    unsigned char NumKeyarr[9];  // 密码输入的缓冲区
    int i, j, k;  // 定义所有循环变量

    // 初始化1602液晶屏
    LCD_Init();
    LCD_ShowString(1, 1, "DigitalNumLock!");
    LCD_ShowString(2, 1, "Loading...");
    Delay(2000);

    LCD_Init();
    LCD_ShowString(1, 1, "SetYourKey");
    LCD_ShowString(2, 1, "NumShouldUnder9");
    Delay(2000);

    while (1)
    {
        // 设置密码部分
        i = 0;
        LCD_Init();
        LCD_ShowString(1, 10, "len[9]");
        Delay(1000);

        // 清空密码数组
        for (k = 0; k < 9; k++)
        {
            NumLockarr[k] = 0;
        }

        LCD_Init();
        LCD_ShowString(1, 1, "EnterTheKey:");
				LCD_Init();
        LCD_ShowString(2, 1, "Press10ToDelete");
					
        for (i = 0; i < 9; i++)
        {
            while (1)
            {
                KeyNum = MartrixKey();

                // 判断当其按下时触发
                if (KeyNum)
                {
                    if (KeyNum == 10)  // 删除键
                    {
                        if (i == 0)  // 已经是第一个字符，无法删除
                        {
                            KeyNum = 0;
                            break;
                        }
                        else
                        {
                            // 先清除当前显示
                            LCD_ShowString(1, i, " ");
                            // 清除数组中的数据
                            if (i > 0)
                            {
                                NumLockarr[i - 1] = 0;
                            }
                            i--;  // 回退一个位置，因为for循环会加回来
                            i--;  // 再减一次，抵消for循环的i++
                            KeyNum = 0;  // 重置KeyNum
                            break;
                        }
                    }

                    if (KeyNum < 10)  // 数字键
                    {
                        NumLockarr[i] = KeyNum;
                        break;
                    }
                }
            }

            if (KeyNum != 10 && KeyNum < 10)
            {
                // 显示设置的密码
                LCD_ShowNum(1, i + 1, KeyNum, 1);
            }

            // 重置KeyNum
            KeyNum = 0;

            // 显示密码设置完毕并退出密码设置程序
            if (i == 8)
            {
                LCD_Init();
                LCD_ShowString(1, 1, "KeyIsSet!!");
                Delay(2000);
                break;
            }
        }

        // 询问是否重置密码
        LCD_Init();
        LCD_ShowString(1, 1, "ResetKey?");
        LCD_ShowString(2, 1, "Yes->1 No->2");

        while (1)
        {
            KeyNum = MartrixKey();

            // 判断当其按下时触发
            if (KeyNum)
            {
                if (KeyNum == 1)  // 选择重置
                {
                    LCD_Init();
                    LCD_ShowString(1, 1, "KeyIsReset");
                    Delay(2000);
                    KeyNum = 0;  // 重置KeyNum
                    break;  // 跳出循环，重新设置密码
                }
                else if (KeyNum == 2)  // 不重置，进入解锁
                {
                    while (1)
                    {
                        int unlock = 0;  // 表示是否成功解锁

                        // 清空输入数组
                        for (j = 0; j < 9; j++)
                        {
                            NumKeyarr[j] = 0;
                        }

                        LCD_Init();
                        KeyNum = 0;  // 重置KeyNum

                        // 显示解锁画面
                        LCD_ShowString(1, 1, "PleaseEnterYour");
                        LCD_ShowString(2, 1, "Key:");

                        // 输入密码
                        for (j = 0; j < 9; j++)
                        {
                            while (1)
                            {
                                KeyNum = MartrixKey();

                                if (KeyNum)
                                {
                                    if (KeyNum < 10)
                                    {
                                        NumKeyarr[j] = KeyNum;
                                        KeyNum = 0;
                                        LCD_ShowString(2, 5 + j, "*");
                                        break;
                                    }
                                }
                            }
                        }

                        // 验证密码
                        unlock = 1;  // 先假设解锁成功
                        for (j = 0; j < 9; j++)
                        {
                            if (NumKeyarr[j] != NumLockarr[j])
                            {
                                unlock = 0;  // 密码错误
                                break;
                            }
                        }

                        if (unlock == 1)
                        {
                            LCD_Init();
                            LCD_ShowString(1, 1, "I Love You!!");
                            LCD_ShowString(2, 1, "My Dear ~ ");
                            Delay(2000);
                            break;
                        }
                        else
                        {
                            LCD_Init();
                            LCD_ShowString(1, 1, "WrongKey!");
                            Delay(2000);
                        }

                        // 解锁失败后询问
                        LCD_Init();
                        LCD_ShowString(1, 1, "1:Retry 2:Reset");

                        while (1)
                        {
                            KeyNum = MartrixKey();

                            if (KeyNum)
                            {
                                if (KeyNum == 1)  // 重试
                                {
                                    break;
                                }
                                else if (KeyNum == 2)  // 重置密码
                                {
                                    // 跳出多层循环，回到最外层重新设置密码
                                    KeyNum = 0;
                                    goto reset_password;
                                }
                            }
                        }
                    }
                    break;
                }
                KeyNum = 0;  // 重置KeyNum
            }
        }

    reset_password:  // 标签，用于跳转到这里重新设置密码
        continue;
    }
}