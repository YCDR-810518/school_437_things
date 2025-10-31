#include <REGX52.H>

unsigned char NumTable1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6D,0x7d,0x07,0x7f,0x6f};	//Number 0~9 数组

unsigned char CharTable[]={0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};		//字母驱动数组，分别为A，B，C，D，E，F，[空]

void ShuMaGuan(unsigned char Location, unsigned int Num)
	{
		//多分支判断
		switch(Location)
		{
			case 1:P2_4=1;P2_3=1;P2_2=1;break;
			case 2:P2_4=1;P2_3=1;P2_2=0;break;
			case 3:P2_4=1;P2_3=0;P2_2=1;break;
			case 4:P2_4=1;P2_3=0;P2_2=0;break;
			case 5:P2_4=0;P2_3=1;P2_2=1;break;
			case 6:P2_4=0;P2_3=1;P2_2=0;break;
			case 7:P2_4=0;P2_3=0;P2_2=1;break;
			case 8:P2_4=0;P2_3=0;P2_2=0;break;
		}
		switch(Num)
		{
			case 0:P0=~0xC0;break;
			case 1:P0=~0xCF;break;
			case 2:P0=0x5B;break;
			case 3:P0=~0xB0;break;
			case 4:P0=~0x99;break;
			case 5:P0=0x6D;break;
			case 6:P0=~0x82;break;
			case 7:P0=~0xF8;break;
			case 8:P0=~0x80;break;    
			case 9:P0=~0x90;break;
		}
	}
	
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
	
/*void main()
{

	while(1)
	{
		unsigned int a,b;	//i是数码管位置，j是所显示的数字
		for(a=1;a<=8;a++)
		{
			for(b=0;b<=9;b++)
			{
				ShuMaGuan(a,b);
				delay(3000);
				
			}
		}
		ShuMaGuan(0,0);
		delay(5000);
	}
}
*/