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

section .text  
_start:  
    cli  ; 关中断  

    ; 传递GRUB信息给C内核（按Multiboot标准）  
    push ebx  ; 保存multiboot_info结构指针  
    push eax  ; 保存魔数0x2BADB002  

    ; 设置基础栈指针  
    mov esp, kernel_stack_top  

    ; 调用C主函数  
    call main  

    ; 如果内核返回（不该发生）  
    hlt  

section .bss  
align 16  
kernel_stack_bottom:  
    resb 16 * 1024  ; 16KB栈空间  
kernel_stack_top:  
