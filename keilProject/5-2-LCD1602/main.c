#include <REGX52.H>
#include <LCD1602.H>
#include <delay.h>
#include <strlen.h>
void main()
{		
	unsigned int i;
		LCD_Init();
						for(i = 0; i <= 999; i++){
						LCD_ShowNum(1,1,i,3);
						delay(100);
										if(i == 60){
											LCD_Clear();
											LCD_ShowString(1,1,"1 miniute have passed!");
											delay(3000);
											i = i + 3;
											LCD_Clear();
										}
										else if(i == 520){
											LCD_Clear();
											LCD_ShowString(1, 1, "I love you");
											LCD_Clear();
										}
										else if(i == 0){  //i = xx是赋值，i == xx才是比较
											LCD_Clear();
											LCD_ShowString(1,1,"Timer start!!");
											delay(3000);
											LCD_Clear();
										}
									
		}
		LCD_Clear();
		LCD_ShowString(1,1,"Timer stop QAQ");				
}
				
				
				