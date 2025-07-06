;
; Copyright (C) 2025 ~ ? Ai-Upace
; Powered by Visual Operating System (VOS)
;  
; BY GPLv3 LICENSE:
;  - This program is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;
; But if you want to shut down? No way! Please to
;  - Mental hospital
;  - FSF (Free Software Foundation)
;  - Court
; 
; - cn v :
; 版权所有 (C) 2025 ~ ? Ai-Upace
; 基于 VOS (Visual Operating System) 开发
;  
; 根据 GPLv3 许可证：
;  - 本程序是自由软件：您可以根据 GNU 通用公共许可证的条款重新分发和/或修改它
;  - 由自由软件基金会发布的 GNU 通用公共许可证
;
;
; END
; <jntmngmhahayo@outlook.com>
; <jntmngmhahayo@gmail.com>
;
; 文件：src/assembly/kernel_entry.asm  
[bits 32]  ; GRUB2默认进入32位保护模式  

global _start  
extern main  ; 声明C主函数  

section .multiboot_header  ; GRUB2魔数头  
align 4  
header_start:  
    ; Multiboot 1标准（兼容老GRUB）  
    dd 0x1BADB002              ; 魔数  
    dd 0x00000003              ; 标志位（内存信息+模块对齐）  
    dd -(0x1BADB002 + 0x03)    ; 校验和  

section .data
empty_idt:
    times 256 * 8 db 0         ; 初始化IDT为全0

section .text  
_start:  
    cli  ; 关中断  

    lidt [empty_idt]  ; 加载空的IDT


    ; 设置基础栈指针  
    mov esp, kernel_stack_top

    ; 按System V ABI传递参数
        mov edi, eax
        mov esi, ebx

    ; 调用C主函数  
    call main  

    ; 休眠
    cli
.halt:
    hlt
    jmp .halt  ; 停止执行

section .bss  
align 32
kernel_stack_bottom:  
    resb 16 * 1024  ; 16KB栈空间  
kernel_stack_top:  
