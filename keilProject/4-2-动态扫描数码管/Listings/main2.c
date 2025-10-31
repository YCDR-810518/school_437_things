#include <REGX52.H>

unsigned char CharTable[]={0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};//��ĸ�������飬�ֱ�ΪA��B��C��D��E��F��[��]

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

void selectDigit(unsigned char Location) //ѡ������ܵ�λ��
{
	if (Location < 1 || Location>8) return 3; //λ�ò��Ϸ��򷵻�3
	//���������
	unsigned char codeTable[8] = {

			0b111,0b110,0b101,0b100,
			0b011,0b010,0b001,0b000 };
	//����Ӧλ�ø�ֵ
	//Location-1����Ϊ�����0��ʼ
	unsigned char val1 = codeTable[Location - 1];
	P2_4 = (val1 >> 2) & 1;
	P2_3 = (val1 >> 1) & 1;
	P2_2 = (val1 >> 0) & 1;
}

void ShuMaGuan(unsigned char Location, unsigned int Num)
	{
		selectDigit(Location);
		P0 = 0xff; //�����
		P0 = 0x00; //ʹ�������
		P0 = CharTable[Num - 1]; //��ʾ��ĸ

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
