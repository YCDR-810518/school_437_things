#include <REGX52.H>

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
		unsigned char LedNum = 0;
		while(1)
		{
			if(P3_1 == 0)
			{
				delay(10);
				while(P3_1 == 0);
				delay(10);
				
				LedNum++;
				//1111 1111
				P2 = ~LedNum;//所以位取反
			
			}

		}

}