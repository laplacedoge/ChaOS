#include "kmalloc.h"
#include "kprint.h"

static void setup(void)
{
    __kmalloc_init_heap();
}

static void loop(void)
{

}

void kmain(void)
{
    setup();

    while (1)
    {
        loop();
    }
}
