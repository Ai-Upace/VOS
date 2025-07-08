#pragma once
#ifndef IO_H
#define IO_H

#include <stdarg.h>

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

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void update_cursor();
void putchar(const char c, const int color);
void kprintf(const char* s, const int color, ...);
int  strcmp(const char* s1, const char* s2);

#endif