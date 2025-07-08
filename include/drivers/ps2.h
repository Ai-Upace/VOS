#pragma once
#ifndef PS2_H
#define PS2_H
#include <stdint.h>
#include <stdbool.h>

int getchar();

#define KEY_UP 0
#define KEY_DOWN 0
#define KEY_LEFT 0
#define KEY_RIGHT 0

struct KeyboardState {
    // 修饰键状态（1字节）
    union {
        uint8_t modifiers;
        struct {
            bool lshift : 1;
            bool rshift : 1;
            bool lctrl  : 1;
            bool rctrl  : 1;
            bool lalt   : 1;
            bool ralt   : 1;
            bool meta_l : 1;  // 预留Meta/Win键
            bool meta_r : 1;
        } bits;
    };

    // 锁定键状态
    union {
        uint8_t locks;
        struct {
            bool caps_lock : 1;
            bool num_lock  : 1;
            bool scr_lock  : 1;
            uint8_t reserved  : 5;
        } modes;
    };
} __attribute__((packed));  // 确保紧凑存储

struct TextMode {

};

struct Full_Color {

};

#endif