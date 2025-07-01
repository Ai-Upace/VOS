#include "IO.h"
#include "drivers/ps2.h"
#include <stdint.h>

static int shift_pressed = 0;  // false
static uint8_t kbd_state = 0;
#define SHIFT_DOWN   0x01
#define CAPS_LOCK    0x02
#define CTRL_DOWN    0x04
#define ALT_DOWN     0x08

// Scancode to ASCII
char scancode_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\\',
    0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    0, 0, 0, 32, 0, 0, 0, 0
};

// Scancode to ASCII with Shift
char scancode_shift[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '|',
    0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    0, 0, 0, 32, 0, 0, 0, 0
};

// simple getchar function
int getchar() {
    while (1) {
        while ((inb(0x64) & 0x01) == 0) asm("pause");
        unsigned char scancode = inb(0x60);

        // Shift 按下/释放
        if (scancode == 0x2A || scancode == 0x36) { kbd_state |= SHIFT_DOWN; continue; }
        if (scancode == 0xAA || scancode == 0xB6) { kbd_state &= ~SHIFT_DOWN; continue; }
        // Caps Lock 按下
        if (scancode == 0x3A) { kbd_state ^= CAPS_LOCK; continue; }
        // 跳过释放事件
        if (scancode & 0x80) continue;
        if (scancode >= sizeof(scancode_ascii) || !scancode_ascii[scancode]) continue;

        char c;
        // 判断是否为字母
        if (scancode_ascii[scancode] >= 'a' && scancode_ascii[scancode] <= 'z') {
            int upper = ((kbd_state & SHIFT_DOWN) ? 1 : 0) ^ ((kbd_state & CAPS_LOCK) ? 1 : 0);
            c = (char)(upper ? scancode_shift[scancode] : scancode_ascii[scancode]);
        } else {
            c = (char)(kbd_state & SHIFT_DOWN ? scancode_shift[scancode] : scancode_ascii[scancode]);
        }
        if (c) return c;
    }
}

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

void puts(const char* s, const int color, ...) {
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
                    // 十六进制
                case 'x':
                case 'X':
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
