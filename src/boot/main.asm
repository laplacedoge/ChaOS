global start
extern kmain
global __heap_start
global __heap_end
global __stack_bottom
global __stack_top

section .text
bits 32
start:
    cli
    mov esp, stack_top
    call kmain
    hlt

section .data
    __heap_start dd heap_start
    __heap_end dd heap_end
    __stack_bottom dd stack_bottom
    __stack_top dd stack_top

section .bss
align 1024
heap_start:
    resb 4096 * 8
heap_end:
stack_bottom:
    resb 4096 * 8
stack_top:
