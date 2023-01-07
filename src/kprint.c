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

static char dec2hex(uint8_t dec)
{
    dec &= 0x0F;
    if (dec < 10)
    {
        return '0' + dec;
    }
    else
    {
        return 'A' + (dec - 10);
    }
}

int khexdump(int row, int col, const void *buff, size_t size, uint8_t attr)
{
    size_t dec_size;
    uint16_t *addr;
    uint16_t ch;
    uint16_t shifted_attr;
    char digit;

    addr = DISP_VRAM_ADDR_START + DISP_COL_NUM * row + col;
    shifted_attr = (uint16_t)attr << 8;
    dec_size = size - 1;
    for (size_t i = 0; i < size; i++)
    {
        digit = dec2hex(((uint8_t *)buff)[i] >> 4);
        ch = shifted_attr | (uint16_t)digit;
        addr[3 * i] = ch;
        digit = dec2hex(((uint8_t *)buff)[i]);
        ch = shifted_attr | (uint16_t)digit;
        addr[3 * i + 1] = ch;
        if (i != dec_size)
        {
            ch = shifted_attr | (uint16_t)' ';
            addr[3 * i + 2] = ch;
        }
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
