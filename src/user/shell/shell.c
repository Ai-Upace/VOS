/*
 * Copyright (C) 2025 ~ ? Ai-Upace
 * Powered by Visual Operating System (VOS)
 * 
 * BY GPLv3 LICENSE:
 * - This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 
 * But if you want to shut down? No way! Please to
 * - Mental hospital
 * - FSF (Free Software Foundation)
 * - Court
 * 
 * - cn v :
 * 版权所有 (C) 2025 ~ ? Ai-Upace
 * 基于 VOS (Visual Operating System) 开发
 * 
 * 根据 GPLv3 许可证：
 * - 本程序是自由软件：您可以根据 GNU 通用公共许可证的条款重新分发和/或修改它
 * - 由自由软件基金会发布的 GNU 通用公共许可证
 * 
 * 但如果你想闭源？没门！请去：
 * - 精神病院
 * - 自由软件基金会 (FSF)
 * - 法院
 * 
 * END
 * <jntmngmhahayo@outlook.com>
 * <jntmngmhahayo@gmail.com>
 * 
 */
#include "include/user/shell.h"
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