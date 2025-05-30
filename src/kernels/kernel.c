#include "../include/IO.h"

// Write a byte to an I/O port
static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(val), "Nd"(port)
    );
}

// Read a byte from an I/O port
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile (
        "inb %1, %0"
        : "=a"(ret)
        : "Nd"(port)
    );
    return ret;
}

// Scancode to ASCII
char scancode_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x0
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   // 0x10
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',           // 0x1E
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,             // 0x2C
    '*', 0, ' ', 0,                                                           // 0x36
    // more but future ...
};

char getchar() {  
    static int shift_pressed = 0;  
    while (1) {  
        // wait for a key press 
        while ((inb(0x64) & 0x01) == 0) asm("pause");  
        
        unsigned char scancode = inb(0x60);  
        
        // Skip release events and control keys 
        if (scancode & 0x80) continue;  
        if (scancode == 0x2A || scancode == 0x36) {  
            shift_pressed = 1;  
            continue;  
        }  
        if (scancode >= sizeof(scancode_ascii) || !scancode_ascii[scancode]) {  
            continue;  
        }  
        
        // Handle shift key release
        char c = scancode_ascii[scancode];  
        return (shift_pressed && c >= 'a' && c <= 'z') ? c - 32 : c;  
    }  
}

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static int cursor_x = 0, cursor_y = 0;

void putchar(char c, int color) {
    volatile char *video = (volatile char*)VGA_ADDRESS;
    if (c == '\n') {
        cursor_x = 0; cursor_y++;
    } else {
        int pos = 2 * (cursor_y * VGA_WIDTH + cursor_x);
        video[pos] = c;
        video[pos+1] = color; // function color (in 'void putchar(char c, int color)' --> int color)
        cursor_x++;
    }
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0; cursor_y++;
    }
    if (cursor_y >= VGA_HEIGHT) {
        cursor_y = 0; // or scroll up, etc.
    }
}

void puts(const char* s, int color, ...) { 
    while (*s) putchar(*s++, color); 
}

void shell() {
    char buf[128];
    while (1) {
        puts("> ", 0x07);
        long unsigned int i = 0;
        char c;
        while ((c = getchar()) != '\n') {
            if (c == '\b' && i > 0) {
                i--;
                putchar('\b', 0x07);
                putchar(' ', 0x07);
                putchar('\b',0x07);
            } else if (i < sizeof(buf)-1 && c >= ' ') {
                buf[i++] = c;
                putchar(c, 0x07);
            }
        }
        buf[i] = 0;
        putchar('\n', 0x07);
        // More commands
    }
}

void main() {  
    puts("Hello World!", 0x7F);

    putchar(getchar(), 0x07); // Test getchar

    shell(); 

    while (1);  // halt
}  