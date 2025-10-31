#include <REGX52.H>

#define LCD_COLS 16      // 每行列数，常见 16 或 20
#define LCD_ROWS 4       // 行数，常见 2 或 4

//引脚配置：
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

/**
  * @brief  在LCD1602上逐块显示长字符串（每块16字符）
  * @param  String 要显示的字符串
  * @param  charDelay 每个字符出现的延时(ms)，0 表示直接整行显示
	* @param  unsigned int LongDelay 
  */
void LCD_ShowLongString(char *String, unsigned int charDelay)
{
    unsigned int i = 0;        // 字符串当前位置
    unsigned int block = 0;    // 当前块序号
    unsigned char col;         // 列位置

    while(String[i] != '\0')
    {
        // 每两行显示一个块（最多 32 个字符）
        // 第1行
        LCD_Clear();
        LCD_SetCursor(1, 1);
        for(col = 0; col < 16 && String[i] != '\0'; col++, i++)
        {
            LCD_WriteData(String[i]);
            if(charDelay > 0) delay(charDelay); // 打字机效果
        }

        // 第2行
        LCD_SetCursor(2, 1);
        for(col = 0; col < 16 && String[i] != '\0'; col++, i++)
        {
            LCD_WriteData(String[i]);
            if(charDelay > 0) delay(charDelay); // 打字机效果
        }

        // 如果字符串还没结束，长延时再清屏
        if(String[i] != '\0')
        {
            LCD_LongDelay();   // 自定义的长延时（比如 2~3 秒）
        }
    }
}


//函数定义：
/**
  * @brief  LCD1602延时函数，12MHz调用可延时1ms
  * @param  无
  * @retval 无
  */
void LCD_Delay() //短延时，用于给指令运行的时间
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}
/**
  * @brief  LCD1602长延时函数，12MHz调用可任意延时，<仅可在LCD1602中调用！>
  * @param  无
  * @retval 无
  */
void LCD_LongDelay(unsigned int xms)	//@12.000MHz
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

/**
  * @brief  LCD1602写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602设置光标位置
  * @param  Line 行位置，范围：1~2
  * @param  Column 列位置，范围：1~16
  * @retval 无
  */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}

/**
  * @brief  LCD1602初始化函数
  * @param  无
  * @retval 无
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//光标复位，清屏
}
/**
  * @brief  LCD1602清屏
  * @param  无
  * @retval 无
  */
void LCD_Clear()
{
    LCD_WriteCommand(0x01);  // 清屏命令
    // 清屏执行时间 > 1.6ms，这里延时 2~5ms
    LCD_Delay();
}
/**
  * @brief  计算字符串长度（类似标准库 strlen）
  * @param  String 指向字符串的指针
  * @retval 字符串长度（不包含结尾的 '\0'）
  */
unsigned char LCD_StrLen(char* String)
{
	unsigned char len = 0;
	while (String[len] != '\0')
	{
		len++;
	}
	return len;
}

/**
  * @brief  LCD1602清屏（写空格覆盖，推荐）
  * @param  无
  * @retval 无
  */
/*void LCD_Clear()
{
    unsigned char i;
    // 清第一行
    LCD_SetCursor(1,1);
    for(i=0;i<16;i++)
    {
        LCD_WriteData(' ');
    }
    // 清第二行
    LCD_SetCursor(2,1);
    for(i=0;i<16;i++)
    {
        LCD_WriteData(' ');
    }
    // 光标回到左上角
    LCD_SetCursor(1,1);
}
*/

/**
  * @brief  在LCD1602指定位置上显示一个字符
  * @param  Line 行位置，范围：1~2
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的字符
  * @retval 无
  */

	void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/**
  * @brief  在LCD1602指定位置开始显示所给字符串
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串
  * @retval 无
  */
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		if(i > 15)
		{
			Line = Line + 1;
		
		}
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief  返回值=X的Y次方
  */
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
  * @brief  在LCD1602指定位置开始显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~65535
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  在LCD1602指定位置开始以有符号十进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-32768~32767
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  在LCD1602指定位置开始以十六进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFF
  * @param  Length 要显示数字的长度，范围：1~4
  * @retval 无
  */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i,SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}

/**
  * @brief  在LCD1602指定位置开始以二进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0');
	}
}
