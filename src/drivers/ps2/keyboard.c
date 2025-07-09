#include "IO.h"
#include "drivers/ps2.h"

static uint8_t kbd_state = 0;
#define L_SHIFT   0x01
#define CAPS_LOCK    0x02
#define CTRL_DOWN    0x03
#define ALT_DOWN     0x08

struct KeyboardState key;

// Scancode to ASCII
char scancode_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\\', 0,
    0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    0, 0, 0, 32, 0, 0, 0, 0
};

// Scancode to ASCII with Shift
char scancode_shift[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '|', 0,
    0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    0, 0, 0, 32, 0, 0, 0, 0
};

// simple getchar function
int getchar() {
    key.bits.lshift = 1; // 初始化左Shift键状态
    while (1) {
        while ((inb(0x64) & 0x01) == 0) asm("pause");
        unsigned char scancode = inb(0x60);

        // Shift 按下/释放
        if (scancode == 0x2A || scancode == 0x36) { kbd_state |= key.bits.lshift; continue; }
        if (scancode == 0xAA || scancode == 0xB6) { kbd_state &= !key.bits.lshift; continue; }

        if (scancode == 0xE0) {  // 扩展键
            if (scancode == 0x38) {kbd_state |= key.bits.ralt; continue; } // 右Alt键
            if (scancode == 0x1D) {kbd_state |= key.bits.rctrl; continue; } // 右Ctrl键
            if (scancode == 0xB8) {kbd_state &= !key.bits.rctrl; continue; }// 右Ctrl键释放
            if (scancode == 0x9D) {kbd_state &= !key.bits.ralt; continue; } // 右Alt键释放
        }
        // Caps Lock 按下
        if (scancode == 0x3A) { kbd_state ^= key.modes.caps_lock; continue; }
        // 跳过释放事件
        if (scancode & 0x80) continue;
        if (scancode >= sizeof(scancode_ascii) || !scancode_ascii[scancode]) continue;

        char c;
        // 判断是否为字母
        if (scancode_ascii[scancode] >= 'a' && scancode_ascii[scancode] <= 'z') {
            int upper = ((kbd_state & key.bits.lshift) ? 1 : 0) ^ ((kbd_state & key.modes.caps_lock) ? 1 : 0);
            // 设置大小写
            c = (char)(upper ? scancode_shift[scancode] : scancode_ascii[scancode]);
        } else {
            // shift 键映射（非字母与 Caps Lock 状态）
            c = (char)(kbd_state & L_SHIFT ? scancode_shift[scancode] : scancode_ascii[scancode]);
        }
        if (c) return c;
    }
}