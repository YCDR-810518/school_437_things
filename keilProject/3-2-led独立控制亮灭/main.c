#include <REGX52.H>
void Delay(unsigned int xms)	//@12.000MHz
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
	while(1)
	{
			if(P3_1==0)
			{
				Delay(15); 
				while(P3_1==0);//��ѭ���壬��ִ���κβ��������ֵȴ�
				Delay(15);
				
				P2_0 =~ P2_0; //��λȡ����ֵ
				
				
				
			
			}
			/*
			P2_0=0;
			Delay(500);
			P2_0=1;
			Delay(500);
			*/
		
	}
	

}