#pragma once

#include "ktype.h"

void __kmalloc_init_heap(void);

void *kmalloc(size_t size);

void kfree(void *ptr);
