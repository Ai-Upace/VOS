#include "IO.h"
#include <stdint.h>

static int cursor_x = 0, cursor_y = 0;

void update_cursor() {
    const int pos = cursor_y * VGA_WIDTH + cursor_x; // 计算光标位置
    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

void putchar(const char c, const int color) {
    volatile uint16_t *video = (volatile uint16_t*)VGA_ADDRESS; // 指向VGA显存的指针
    if (c == '\n') { // 如果是换行符
        cursor_x = 0;
        cursor_y++;   // 光标移到下一行开头
    } else {
        const int pos = (cursor_y * VGA_WIDTH + cursor_x); // 计算显存中的位置（每字符2字节）
        video[pos] = (color << 8) | c;
        cursor_x++;             // 光标右移
    }
    if (cursor_x >= VGA_WIDTH) { // 如果到达行末
        cursor_x = 0;
        cursor_y++;              // 换到下一行
    }
    if (cursor_y >= VGA_HEIGHT) { // 如果到达屏幕底部
        cursor_y = 0;
    }
    // 更新光标位置
    update_cursor();
}

void kprintf(const char* s, const int color, ...) {
    // 初始化可变参数
    va_list args;

    va_start(args, s);

    while (*s) {
        if (*s == '%') {
            s++;

            // 处理格式化字符与功能
            switch (*s) {
                case 'c':
                    const int ch = va_arg(args, int);
                    // 将数字转化为 char 类型
                    putchar((char)ch, color);
                    if (ch == '\0') {
                        putchar('^', color); putchar('@', color);
                    }
                    break;
                    // 字符串
                case 's':
                    const char* strs = va_arg(args, char*);
                    while (*strs) putchar(*strs++, color);
                    break;
                case 'd':
                    // TODO: 实现整数输出
                    putchar('1', color);
                    break;
                    // future
                case 'x':
                case 'X':
                    break;
                case '%':
                    putchar('%', color);
                    break;
                default: putchar('N', color);
            }
        } else {
            putchar(*s, color);  // 输出普通字符
        }
        s++;
    }

    va_end(args);
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && *s1 == *s2) {
        // 如果字符相同则继续
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
