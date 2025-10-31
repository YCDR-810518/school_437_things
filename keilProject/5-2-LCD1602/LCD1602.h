#ifndef __LCD1602_H__
#define __LCD1602_H__

//用户调用函数：
void LCD_Init(); //1602液晶屏初始化函数
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char); //显示字符，分别为行，列，显示的字符
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String); //显示字符串，分别为行，列，显示的字符串
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);//显示十六进制数
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);//显示二进制数
void LCD_Clear();	//清屏
unsigned char LCD_StrLen(char* String); //计算字符串长度,返回长度值，不包含结束符，与strlen功能相同
void LCD_ShowLongString(char *String, unsigned int charDelay)  //用于显示长字符串
#endif
