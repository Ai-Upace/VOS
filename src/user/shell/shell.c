/*
 * Copyright (C) 2025 ~ ? Ai-Upace
 * Powered by Visual Operating System (VOS)
 * 
 * BY GPLv3 LICENSE:
 * - This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *
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
#include "user/command.h"
#include <stddef.h>

#define MAX_ARGS 10

void execute_command(char* input) {
    char* argv[MAX_ARGS]; // 参数数组
    int argc = 0;

    // 1. 分割命令
    char* token = input;
    while (*token && argc < MAX_ARGS-1) {
        // 跳过空格
        while (*token == ' ') token++;
        if (!*token) break;

        // 记录参数起始
        argv[argc++] = token;

        // 找到参数结尾
        while (*token && *token != ' ') token++;
        if (*token) *token++ = '\0'; // 截断
    }
    argv[argc] = NULL; // UNIX风格结束

    // 2. 空命令处理
    if (argc == 0) return;

    // 3. 命令查找（时间复杂度O(n)）
    for (const CommandEntry* cmd = commands_table; cmd->command; cmd++) {
        if (strcmp(argv[0], cmd->command) == 0) {
            cmd->handler(argc, argv); // 执行！
            return;
        }
    }

    // 4. 未找到命令
    puts("Unknown command: %s\n", 0x07 ,argv[0]);
}

void shell() {
    char buf[128];
    while (1) {
        puts("[VOS] $ ", 0x07);
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
        execute_command(buf);
    }
}