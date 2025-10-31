void delay(unsigned int xms)	//@12.000MHz下正常工作
{
	unsigned char i, j;
	while (xms)
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
