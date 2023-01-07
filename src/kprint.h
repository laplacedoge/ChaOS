#pragma once

#include "ktype.h"

#define DISP_VRAM_ADDR_START    ((uint16_t *)0x000b8000)

#define DISP_ROW_NUM            25

#define DISP_COL_NUM            80

/* dark colors */
#define BLACK       0x00
#define BLUE        0x01
#define GREEN       0x02
#define CYAN        0x03
#define RED         0x04
#define MAGENTA     0x05
#define BROWN       0x06
#define LIGHT_GRAY  0x07

/* light colors */
#define DARK_GRAY   0x08
#define LIGHT_BLUE  0x09
#define LIGHT_GREEN 0x0a
#define LIGHT_CYAN  0x0b
#define LIGHT_RED   0x0c
#define PINK        0x0d
#define YELLOW      0x0e
#define WHITE       0x0f

#define PLAIN_TEXT  ((BLACK << 4) | LIGHT_GRAY)

int kprint_put_text(int row, int col, const char *text, uint8_t attr);

int khexdump(int row, int col, const void *buff, size_t size, uint8_t attr);

int kprint_clear(void);
