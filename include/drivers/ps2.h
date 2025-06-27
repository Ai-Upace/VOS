#pragma once
#ifndef PS2_H
#define PS2_H
#include "../IO.h"

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

int  getchar();
void putchar(const char c, const int color);
void puts(const char* s, const int color, ...);
int  strcmp(const char* s1, const char* s2);

#endif