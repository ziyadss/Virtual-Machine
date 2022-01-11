#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint16_t word_t;

const word_t WORD_MAX = ((word_t) ~(word_t)0);

const word_t MEMORY_SIZE = WORD_MAX;
const word_t PC_START = 0x3000;

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