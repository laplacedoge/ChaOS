#include "kmalloc.h"
#include "kprint.h"

extern uint8_t * const __heap_start;
extern uint8_t * const __heap_end;

typedef struct mem_chunk
{
    /* size of the data within this chunk */
    uint32_t size:31;

    /* 0: free-chunk, 1: used-chunk */
    uint32_t used:1;
} mem_chunk_t;

static mem_chunk_t * head_chunk = NULL;

/**
 * @brief initialize heap and head memory chunk.
*/
void __kmalloc_init_heap(void)
{
    head_chunk = (mem_chunk_t *)__heap_start;

    head_chunk->used = 0;
    head_chunk->size = (uint32_t)__heap_end - (uint32_t)__heap_start - sizeof(mem_chunk_t);

    return;
}

void *kmalloc(size_t size)
{
    size_t rest_size;
    mem_chunk_t *chunk;
    mem_chunk_t *next_chunk;
    void *ptr;

    if (size == 0)
    {
        return NULL;
    }

    /* size of allocated memory must be 4-byte aligned */
    size = (size & 0xFFFFFFFC) + ((size & 0x00000003) ? 4 : 0);

    chunk = head_chunk;
    while (1)
    {
        /* if this is a used-chunk, or a free-chunk but the size is smaller than our requirement */
        if (chunk->used || chunk->size < size)
        {
            next_chunk = (mem_chunk_t *)((uint8_t *)chunk + sizeof(mem_chunk_t) + chunk->size);

            /* if we have reached the end of the heap */
            if ((uint8_t *)next_chunk >= __heap_end)
            {
                return NULL;
            }
            else
            {
                chunk = next_chunk;
                continue;
            }
        }
        else
        {
            rest_size = chunk->size - size;
            ptr = (uint8_t *)chunk + sizeof(mem_chunk_t);

            chunk->used = 1;
            chunk->size = size;

            /* mark the rest of the memory as a free-chunk */
            if (rest_size >= sizeof(mem_chunk_t))
            {
                chunk = (mem_chunk_t *)((uint8_t *)chunk + sizeof(mem_chunk_t) + size);
                chunk->used = 0;
                chunk->size = rest_size - sizeof(mem_chunk_t);
            }

            return ptr;
        }
    }
}

void kfree(void *ptr)
{
    mem_chunk_t *chunk;
    mem_chunk_t *base_chunk;
    mem_chunk_t *next_chunk;

    /* invalid address */
    if ((uint8_t *)ptr < __heap_start + sizeof(mem_chunk_t) ||
        (uint8_t *)ptr >= __heap_end)
    {
        return;
    }

    /* set address of the base chunk */
    base_chunk = (mem_chunk_t *)((uint8_t *)ptr - sizeof(mem_chunk_t));
    base_chunk->used = 0;

    /* find the first used-chunk after the base chunk */
    chunk = base_chunk;
    while (!chunk->used)
    {
        next_chunk = (mem_chunk_t *)((uint8_t *)chunk + sizeof(mem_chunk_t) + chunk->size);
        chunk = next_chunk;

        /* if we have reached the end of the heap */
        if ((uint8_t *)next_chunk >= __heap_end)
        {
            break;
        }
    }
    base_chunk->size = (uint8_t *)chunk - (uint8_t *)base_chunk - sizeof(mem_chunk_t);

    return;
}
