#include <LCD12864.h>
#include <string.h>

// ����ʱ
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

// дָ��
void lcd_write_cmd(unsigned char cmd) {
    LCD_RS = 0;    // ָ��
    LCD_RW = 0;    // д
    LCD_DATA = cmd;
    LCD_E = 1;
    _nop_(); _nop_();
    LCD_E = 0;
    delay_ms(2);
}

// д����
void lcd_write_data(unsigned char dat) {
    LCD_RS = 1;    // ����
    LCD_RW = 0;    // д
    LCD_DATA = dat;
    LCD_E = 1;
    _nop_(); _nop_();
    LCD_E = 0;
    delay_ms(2);
}

// ��ʼ��
void lcd_init(void) {
    delay_ms(40);        // �ϵ���ʱ
    lcd_write_cmd(0x30); // �����趨: 8λ, ����ָ�
    delay_ms(1);
    lcd_write_cmd(0x30);
    delay_ms(1);
    lcd_write_cmd(0x0C); // ��ʾ��, ����
    delay_ms(1);
    lcd_write_cmd(0x01); // ����
    delay_ms(2);
    lcd_write_cmd(0x06); // д����ַ+1
}

// ����
void lcd_clear(void) {
    lcd_write_cmd(0x01);
    delay_ms(2);
}

// ����DDRAM��ַ
void lcd_set_ddram(unsigned char addr) {
    lcd_write_cmd(0x80 | addr);
}

// ��ʾASCII�ַ���
// addr = 0x80 ��һ����ʼ, 0x90 �ڶ���, 0x88 ������, 0x98 ������
void lcd_display_string(unsigned char addr, unsigned char* str) {
    lcd_set_ddram(addr);
    while (*str) {
        lcd_write_data(*str++);
    }
}

// ��ʾһ������
// high/low Ϊ GB2312 ����ĸߡ����ֽ�
void lcd_display_chinese(unsigned char addr, unsigned char high, unsigned char low) {
    lcd_set_ddram(addr);
    lcd_write_data(high);
    lcd_write_data(low);
}

// ��/�ر���
void lcd_backlight(unsigned char on) {
    if (on) {
        LCD_BL = 0; // �����
    } else {
        LCD_BL = 1; // ���⿪
    }
}



// �ж��Ƿ������� (GB2312 ��Χ: 0xA1-0xF7, 0xA1-0xFE)
bit is_chinese(unsigned char c) {
    return (c >= 0xA1 && c <= 0xF7);
}

// ��ʾGB2312�����ַ�����֧����Ӣ�Ļ�ϣ�
// str: GB2312������ַ���
// addr: ��ʼ��ʾλ�� (0x80 ��һ��, 0x90 �ڶ���, 0x88 ������, 0x98 ������)
void lcd_display_gb2312(unsigned char addr, unsigned char* str) {
    lcd_set_ddram(addr);
    while (*str) {
        if (is_chinese(*str)) {
            unsigned char high = *str++;
            unsigned char low = *str++;
            lcd_write_data(high);
            lcd_write_data(low);
        }
        else {
            lcd_write_data(*str++);
        }
    }
}
