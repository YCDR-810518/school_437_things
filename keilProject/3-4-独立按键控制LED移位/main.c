#include <REGX52.H>

unsigned char LedNum;

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

void main()
{
	P2 = 0x01;
	while(1)
	{
		
		if(P3_1 == 0)
		{
			delay(10);
			while(P3_1==0);
			delay(10);
			LedNum ++;
			if(LedNum>=8)
				LedNum=0;
			P2 = ~ (0x01 << LedNum);  //Ϊ0ʱ����1ʱ�𣬹�ȡ��
			
		}
		if(P3_0 == 0)
		{
			delay(10);
			while(P3_0==0);
			delay(10);
			LedNum --;
			if(LedNum>=8)
				LedNum=0;
			P2 = ~ (0x01 << LedNum);  //Ϊ0ʱ����1ʱ�𣬹�ȡ��
			
		}
	}

}
