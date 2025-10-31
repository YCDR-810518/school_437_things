#ifndef __LCD12864_H__
#define __LCD12864_H__

#include <reg52.h>
#include <intrins.h>

// ���Ŷ���
sbit LCD_RS = P2 ^ 6;   // RS: ����/ָ��ѡ��
sbit LCD_RW = P2 ^ 5;   // RW: ��/д
sbit LCD_E = P2 ^ 7;   // E: ʹ��
sbit LCD_BL = P3 ^ 4;   // ����

#define LCD_DATA P0    // ��������

// ��������
void delay_ms(unsigned int ms);
void lcd_write_cmd(unsigned char cmd);	//ֱ�Ӹ����ֲ���������
void lcd_write_data(unsigned char dat);	//д����
void lcd_init(void);	//12864ʹ��ǰ�ĳ�ʼ��
void lcd_clear(void);	//����
void lcd_set_ddram(unsigned char addr);	//����ddram��ַ
void lcd_display_string(unsigned char addr, unsigned char* str); //��ʾ�ַ�����ASCII���룩
void lcd_display_chinese(unsigned char addr, unsigned char high, unsigned char low); //��ʾ��������
void lcd_backlight(unsigned char on);	//���ñ��� 0Ϊ�� �������ֶ��ǿ�
void lcd_display_gb2312(unsigned char addr, unsigned char* str);	//��ʾGB2312���޶���Χ������
#endif
