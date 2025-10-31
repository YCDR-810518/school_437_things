#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
# include "MartrixKey.h"
unsigned char KeyNum;
void main(){
	//初始化1602液晶屏
	LCD_Init();
	LCD_ShowString(1,1,"DigitalNumLock!");
	LCD_ShowString(2,1,"Loading...");
	Delay(2000);
	
	LCD_Init();
	LCD_ShowString(1,1,"SetYourKey");
	LCD_ShowString(2,1,"NumShouldUnder9");
	Delay(2000);
	
	//初始化LCD
	LCD_Init();
	while(1){
		int i = 0;
	  int NumLockarr[9];
		LCD_ShowString(1,8,"Reset[10]");
		
		for(i=1; i<=9; i++){
			NumLockarr[i-1] = MartrixKey();
			KeyNum = MartrixKey();
				if(KeyNum)
				{
					LCD_ShowNum(1,1,KeyNum,2);
				}
			if(i==9){
				LCD_Init();
				LCD_ShowString(1,1,"KeyIsSet!!");
				Delay(2000);
			}
			if(MartrixKey() == 10){
				
			}
		}
		

	}
}