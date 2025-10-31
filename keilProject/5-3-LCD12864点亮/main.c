#include <LCD12864.h>

void main()
{
	lcd_init();
	lcd_clear();

	while(1)
	{
		//lcd_display_chinese(0x80, 0xD2, 0xA6);	//Ò¦
		//lcd_display_chinese(0x81, 0xB3, 0xBF);	//³¿
		lcd_display_chinese(0x88, 0xD1, 0xA7);	//Ñ§
		lcd_display_chinese(0x89, 0xB3, 0xA4);	//³¤
		lcd_display_chinese(0x8A, 0xC5, 0xA3);	//Å£
		lcd_display_chinese(0x8B, 0xB1, 0xA4);	//±Æ
		
	}
}