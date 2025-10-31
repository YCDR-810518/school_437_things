#include <REGX52.H>

unsigned char CharTable[]={0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};//字母驱动数组，分别为A，B，C，D，E，F，[空]

void delay(unsigned int xms)	//@12.000MHz
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

void selectDigit(unsigned char Location) //选择数码管的位置
{
	if (Location < 1 || Location>8) return 3; //位置不合法则返回3
	//编制译码表
	unsigned char codeTable[8] = {

			0b111,0b110,0b101,0b100,
			0b011,0b010,0b001,0b000 };
	//给对应位置赋值
	//Location-1是因为数组从0开始
	unsigned char val1 = codeTable[Location - 1];
	P2_4 = (val1 >> 2) & 1;
	P2_3 = (val1 >> 1) & 1;
	P2_2 = (val1 >> 0) & 1;
}

void ShuMaGuan(unsigned char Location, unsigned int Num)
	{
		selectDigit(Location);
		P0 = 0xff; //先清除
		P0 = 0x00; //使能数码管
		P0 = CharTable[Num - 1]; //显示字母

	}

int main()
{
	while(1)
	{
		for (i = 1; i <= 7; i++)
		{
			ShuMaGuan(i, i);
			delay(2);
		}
		delay(2);
	
	}

	return 0;
}
