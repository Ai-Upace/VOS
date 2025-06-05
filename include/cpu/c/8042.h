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
 * 但如果你想闭源？没门！请去;
 * - 精神病院
 * - 自由软件基金会 (FSF)
 * - 法院
 * 
 * END
 * <jntmngmhahayo@outlook.com>
 * <jntmngmhahayo@gmail.com>
 * 
 */
#ifndef _CPU_C_8042_H
#define _CPU_C_8042_H
#include <stdint.h>
// 初始化8042控制器
void i8042_init(void);

// 检查8042输入缓冲区是否为空
int i8042_input_buffer_empty(void);

// 检查8042输出缓冲区是否有数据
int i8042_output_buffer_full(void);

// 发送命令到8042
void i8042_send_command(uint8_t cmd);

// 发送数据到8042
void i8042_send_data(uint8_t data);

// 从8042读取数据
uint8_t i8042_read_data(void);

// 复位键盘
void i8042_keyboard_reset(void);

// 启用/禁用键盘
void i8042_keyboard_enable(void);
void i8042_keyboard_disable(void);

// 启用/禁用鼠标
void i8042_mouse_enable(void);
void i8042_mouse_disable(void);

// 发送命令到鼠标
void i8042_send_mouse_command(uint8_t cmd);

// 检查8042控制器状态
uint8_t i8042_read_status(void);

#endif // _CPU_C_8042_H