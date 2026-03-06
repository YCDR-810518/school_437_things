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

// 切换图形/基本模式
void lcd_graphic_mode(bit on) {
    if (on) {
        lcd_write_cmd(0x34); // 扩充指令集
        lcd_write_cmd(0x36); // 图形显示开
    }
    else {
        lcd_write_cmd(0x30); // 回到基本指令集
    }
}

// 绘制全屏图像
// 参数使用 code 关键字，因为动画数据必须存在 Flash 里
void lcd_draw_frame(unsigned char code* img) {
    unsigned char x, y;

    // 上半屏刷新 (32行)
    for (y = 0; y < 32; y++) {
        lcd_write_cmd(0x80 | y);    // 设定垂直地址 Y
        lcd_write_cmd(0x80);        // 设定水平地址 X=0
        for (x = 0; x < 16; x++) {  // 128位 / 8 = 16字节
            lcd_write_data(*img++);
        }
    }

    // 下半屏刷新 (32行)
    for (y = 0; y < 32; y++) {
        lcd_write_cmd(0x80 | y);    // 设定垂直地址 Y
        lcd_write_cmd(0x88);        // 设定水平地址 X=8 (下半屏起始)
        for (x = 0; x < 16; x++) {
            lcd_write_data(*img++);
        }
    }
}

// 清除图形缓存 (防止切回图形模式时显示上次的乱码)
void lcd_clear_gdram(void) {
    unsigned char x, y;
    for (y = 0; y < 32; y++) {
        lcd_write_cmd(0x80 | y);
        lcd_write_cmd(0x80);
        for (x = 0; x < 32; x++) { // 上下半屏一起连着清，一行写32字节
            lcd_write_data(0x00);
        }
    }
}