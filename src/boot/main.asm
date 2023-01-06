global start
extern kmain

section .text
bits 32
start:
    cli
    mov esp, stack_top
    call kmain
    hlt

section .bss
align 4096
heap_start:
    resb 4096 * 8
heap_end:
stack_bottom:
    resb 4096 * 8
stack_top:
