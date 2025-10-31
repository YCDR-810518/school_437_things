#ifndef __LCD12864_H__
#define __LCD12864_H__

#include <reg52.h>
#include <intrins.h>

// 引脚定义
sbit LCD_RS = P2 ^ 6;   // RS: 数据/指令选择
sbit LCD_RW = P2 ^ 5;   // RW: 读/写
sbit LCD_E = P2 ^ 7;   // E: 使能
sbit LCD_BL = P3 ^ 4;   // 背光

#define LCD_DATA P0    // 数据总线

// 函数声明
void delay_ms(unsigned int ms);
void lcd_write_cmd(unsigned char cmd);	//直接根据手册输入命令
void lcd_write_data(unsigned char dat);	//写数据
void lcd_init(void);	//12864使用前的初始化
void lcd_clear(void);	//清屏
void lcd_set_ddram(unsigned char addr);	//设置ddram地址
void lcd_display_string(unsigned char addr, unsigned char* str); //显示字符串（ASCII编码）
void lcd_display_chinese(unsigned char addr, unsigned char high, unsigned char low); //显示单个汉字
void lcd_backlight(unsigned char on);	//设置背光 0为关 其他数字都是开
void lcd_display_gb2312(unsigned char addr, unsigned char* str);	//显示GB2312中限定范围的内容
#endif
