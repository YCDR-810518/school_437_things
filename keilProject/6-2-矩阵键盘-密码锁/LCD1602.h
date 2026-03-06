#ifndef __LCD1602_H__
#define __LCD1602_H__

//用户调用函数：
void LCD_Init(); //1602液晶屏初始化函数
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char); //显示字符，分别为行，列，显示的字符
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String); //显示字符串，分别为行，列，显示的字符串
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif
