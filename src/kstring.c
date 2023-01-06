#include "kstring.h"

size_t kstrlen(const char *str)
{
    size_t len = 0;

    while (*str++ != '\0')
    {
        len++;
    }

    return len;
}
