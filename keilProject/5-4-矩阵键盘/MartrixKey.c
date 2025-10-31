#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"

unsigned char MartrixKey()
{
    unsigned char KeyNum = 0;
    unsigned char i, j, q;

    // ɨ��4��
    for (j = 0; j < 4; j++)
    {
        // ����������Ϊ�ߵ�ƽ
        P1 = 0xFF;

        // ����ǰ������Ϊ�͵�ƽ
        switch (j)
        {
        case 0: P1_3 = 0; break;  // ��1��
        case 1: P1_2 = 0; break;  // ��2��
        case 2: P1_1 = 0; break;  // ��3��
        case 3: P1_0 = 0; break;  // ��4��
        }

        // �����״̬
        switch (j)
        {
        case 0:  // ��1��
            for (i = 7, q = 1; i >= 5; i--, q++)
            {
                if (i == 7 && P1_7 == 0) KeyNum = q;
                else if (i == 6 && P1_6 == 0) KeyNum = q;
                else if (i == 5 && P1_5 == 0) KeyNum = q;

                if (KeyNum != 0)
                {
                    Delay(10);  // ����
                    // �ȴ������ͷ�
                    if (i == 7) while (P1_7 == 0);
                    else if (i == 6) while (P1_6 == 0);
                    else if (i == 5) while (P1_5 == 0);
                    Delay(10);  // ����
                    return KeyNum;
                }
            }
            break;

        case 1:  // ��2��
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

            // ������ⰴ��
            if (P1_4 == 0)
            {
                Delay(10);
                while (P1_4 == 0);
                Delay(10);
                return 0;  // ����0
            }
            break;

        case 2:  // ��3��
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

        case 3:  // ��4��
            // ������ⰴ��
            if (P1_7 == 0)
            {
                Delay(10);
                while (P1_7 == 0);
                Delay(10);
								KeyNum = 0;
                return KeyNum;							// ����0
            }

            // �����������
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

    return KeyNum;  // û�а������·���0
}