section .multiboot_header
header_start:
    ; magic number
    dd 0xe85250d6

    ; architecture: 32-bit protected mode of i386
    dd 0x00000000

    ; header length
    dd header_end - header_start

    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; end tag
    dw 0x0000
    dw 0x0000
    dd 0x00000008
header_end:
