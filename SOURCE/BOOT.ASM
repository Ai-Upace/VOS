[org 0x7C00]  
[bits 16]  

start:  
    xor ax, ax  
    mov ds, ax  
    mov es, ax  
    mov ss, ax  
    mov sp, 0x7C00  

    ; 1. Read disk to 0x1000  
    mov ax, 0x1000  
    mov es, ax  
    mov bx, 0x00  
    mov ah, 0x02      ; Read disk
    mov al, 32        ; Read 32 sectors (16KB) 
    mov ch, 0         ; Cylinder 0 
    mov cl, 2         ; Sector 2 
    mov dh, 0         ; Head 0  
    int 0x13  
    jc disk_error  

    ; 2. Load GDT in parallel protection mode 
    cli  
    lgdt [gdt_descriptor]  

    ; Open the A20 line 
    in al, 0x92  
    or al, 2  
    out 0x92, al  

    ; Set CR0.PE  
    mov eax, cr0  
    or eax, 0x1  
    mov cr0, eax  

    ; far jump to 32-bit code 
    jmp CODE_SEG:pm_start  

disk_error:  
    mov si, msg_error  
    call print_string  
    jmp $  

print_string:  
    lodsb  
    or al, al  
    jz .done  
    mov ah, 0x0E  
    int 0x10  
    jmp print_string  
.done:  
    ret  

msg_error db "Disk Error!", 0  

align 8  
gdt_start:  
    dq 0  
gdt_code:  
    dw 0xFFFF, 0x0000  
    db 0x00, 0x9A, 0xCF, 0x00  
gdt_data:  
    dw 0xFFFF, 0x0000  
    db 0x00, 0x92, 0xCF, 0x00  
gdt_end:  

gdt_descriptor:  
    dw gdt_end - gdt_start - 1  
    dd gdt_start  

CODE_SEG equ gdt_code - gdt_start  
DATA_SEG equ gdt_data - gdt_start  

[bits 32]  
pm_start:  
    mov ax, DATA_SEG  
    mov ds, ax  
    mov ss, ax  
    mov es, ax  
    mov fs, ax  
    mov gs, ax  
    mov esp, 0x90000  

    jmp CODE_SEG:0x10000  ; jump to kernel  

; MBR END  
times 510 - ($-$$) db 0  
dw 0xAA55  ; BIOS Magic Number