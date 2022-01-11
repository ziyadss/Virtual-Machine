#include "header.h"

word_t mem[MEMORY_SIZE] = {0};

static inline word_t mem_read(word_t address) { return mem[address]; }
static inline void mem_write(word_t address, word_t val) { mem[address] = val; }

int main()
{
    return 0;
}