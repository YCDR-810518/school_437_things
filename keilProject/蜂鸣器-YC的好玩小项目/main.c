#include <REGX52.H>
#include <delay.h>
#include <intrins.h>
//为io口设定好记的名字
sbit BUZZER = P2^5;
sbit ST_BU = P3^1;
sbit UP_BU = P3^0;
sbit DOWN_BU = P3^2;

unsigned char pwm_duty = 255;  // 0~255，值越大声音越大（占空比越高）

//该程序测试蜂鸣器是否正常运作
void Timer0_Init(void)  // 示例：产生约1kHz PWM
{
	TMOD = 0x01;     // T0 方式1
	TH0 = (65536 - 1000) / 256;   // 调整这个值改变频率
	TL0 = (65536 - 1000) % 256;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}
void Timer0_ISR() interrupt 1
{
	static unsigned char cnt = 0;
	TH0 = 0xFC;     // ← 这里填重载值（保持频率不变）
	TL0 = 0x18;

	cnt++;
	if (cnt >= 256) cnt = 0;

	if (cnt < pwm_duty)
		BUZZER = 0;   // 假设低电平导通蜂鸣器（响）
	else
		BUZZER = 1;   // 关
}
main(){
	//给蜂鸣器初始化为低电平
	BUZZER = 0;
	while(1){
		//独立按键启动蜂鸣器
		if(ST_BU == 0)
		{
			//消除抖动
			delay(10);
			//启动蜂鸣器
			BUZZER = ~BUZZER;
		}
		if (UP_BU == 0)
		{
			delay(10);
			if (pwm_duty < 255) pwm_duty+=5;  // 增大占空比

		}
		if (DOWN_BU == 0)
		{
			delay(10);
			if (pwm_duty > 5) pwm_duty -= 5;  // 减小占空比
		}
	}
}