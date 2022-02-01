#pragma once

#include "header.h"

word_t memory[MEMORY_SIZE] = {0};

static inline word_t mem_read(word_t address) { return memory[address]; }
static inline void mem_write(word_t address, word_t val) { memory[address] = val; }