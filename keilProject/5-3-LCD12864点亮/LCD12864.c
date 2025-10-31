#include <LCD12864.h>
#include <string.h>

// 简单延时
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

// 写指令
void lcd_write_cmd(unsigned char cmd) {
    LCD_RS = 0;    // 指令
    LCD_RW = 0;    // 写
    LCD_DATA = cmd;
    LCD_E = 1;
    _nop_(); _nop_();
    LCD_E = 0;
    delay_ms(2);
}

// 写数据
void lcd_write_data(unsigned char dat) {
    LCD_RS = 1;    // 数据
    LCD_RW = 0;    // 写
    LCD_DATA = dat;
    LCD_E = 1;
    _nop_(); _nop_();
    LCD_E = 0;
    delay_ms(2);
}

// 初始化
void lcd_init(void) {
    delay_ms(40);        // 上电延时
    lcd_write_cmd(0x30); // 功能设定: 8位, 基本指令集
    delay_ms(1);
    lcd_write_cmd(0x30);
    delay_ms(1);
    lcd_write_cmd(0x0C); // 显示开, 光标关
    delay_ms(1);
    lcd_write_cmd(0x01); // 清屏
    delay_ms(2);
    lcd_write_cmd(0x06); // 写入后地址+1
}

// 清屏
void lcd_clear(void) {
    lcd_write_cmd(0x01);
    delay_ms(2);
}

// 设置DDRAM地址
void lcd_set_ddram(unsigned char addr) {
    lcd_write_cmd(0x80 | addr);
}

// 显示ASCII字符串
// addr = 0x80 第一行起始, 0x90 第二行, 0x88 第三行, 0x98 第四行
void lcd_display_string(unsigned char addr, unsigned char* str) {
    lcd_set_ddram(addr);
    while (*str) {
        lcd_write_data(*str++);
    }
}

// 显示一个汉字
// high/low 为 GB2312 编码的高、低字节
void lcd_display_chinese(unsigned char addr, unsigned char high, unsigned char low) {
    lcd_set_ddram(addr);
    lcd_write_data(high);
    lcd_write_data(low);
}

// 开/关背光
void lcd_backlight(unsigned char on) {
    if (on) {
        LCD_BL = 0; // 背光关
    } else {
        LCD_BL = 1; // 背光开
    }
}



// 判断是否是中文 (GB2312 范围: 0xA1-0xF7, 0xA1-0xFE)
bit is_chinese(unsigned char c) {
    return (c >= 0xA1 && c <= 0xF7);
}

// 显示GB2312编码字符串（支持中英文混合）
// str: GB2312编码的字符串
// addr: 起始显示位置 (0x80 第一行, 0x90 第二行, 0x88 第三行, 0x98 第四行)
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
