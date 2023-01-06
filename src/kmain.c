#include "kprint.h"

void kmain(void)
{
    kprint_put_text(10, 10, "Hello, world!", PLAIN_TEXT);

    kprint_put_text(20, 20, "I'm laplacedoge!", PLAIN_TEXT);

    while (1)
    {
    }
}
