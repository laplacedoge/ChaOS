#include "kprint.h"
#include "kstring.h"

int kprint_put_text(int row, int col, const char *text, uint8_t attr)
{
    size_t len;
    uint16_t *addr;
    uint16_t ch;

    len = kstrlen(text);
    addr = DISP_VRAM_ADDR_START + DISP_COL_NUM * row + col;
    for (uint32_t i = 0; i < len; i++)
    {
        ch = ((uint16_t)attr << 8) | text[i];
        addr[i] = ch;
    }

    return 0;
}

int kprint_clear(void)
{
    uint16_t *addr;
    uint16_t ch;

    addr = DISP_VRAM_ADDR_START;
    ch = ((BLACK << 12) | (BLACK << 8) | ' ');
    for (uint32_t i = 0; i < DISP_ROW_NUM * DISP_COL_NUM; i++)
    {
        addr[i] = ch;
    }

    return 0;
}
