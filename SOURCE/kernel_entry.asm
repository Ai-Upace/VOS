; kernel_entry.asm - jump to kernel
[bits 32]  
global _start  
extern main  ; Declare the C main function

section .text  
_start:  
    ; 1. Initialize the kernel stack  
    mov esp, kernel_stack_top  

    ; 2. Call the kernel main function  
    call main  

    ; 3. Hangs if main returns  
    cli  
    hlt  

section .bss  
align 16  
kernel_stack_bottom:  
    resb 16 * 1024  ; 16KB kernel stack  
kernel_stack_top:  