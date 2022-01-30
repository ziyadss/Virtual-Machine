#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint16_t word_t;

#define WORD_MAX ((word_t) ~(word_t)0)

#define MEMORY_SIZE WORD_MAX + 1
#define PC_START 0x3000

enum REG
{
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    RPC,
    RCND,
    RCNT
};

word_t registers[RCNT] = {0};