/*
 * Copyright (C) 2025 ~ ? Ai-Upace
 * Powered by Visual Operating System (VOS)
 * 
 * BY GPLv3 LICENSE:
 * - This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 
 * - cn v :
 * 版权所有 (C) 2025 ~ ? Ai-Upace
 * 基于 VOS (Visual Operating System) 开发
 * 
 * 根据 GPLv3 许可证：
 * - 本程序是自由软件：您可以根据 GNU 通用公共许可证的条款重新分发和/或修改它
 * - 由自由软件基金会发布的 GNU 通用公共许可证
 * 
 * 
 * END
 * <jntmngmhahayo@outlook.com>
 * <jntmngmhahayo@gmail.com>
 * 
 */

#include "drivers/ps2.h"
#include "user/shell.h"

void main() {  
    puts("Hello World!", 0x7F);

    putchar(getchar(), 0x07); // Test getchar

    shell(); 

    while (1) {
        asm volatile("hlt");
    }
}