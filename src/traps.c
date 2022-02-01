#pragma once

#include "header.h"
#include "memory.c"

#define T_COUNT 8
#define TRAP_OFFSET 0x20
typedef void (*trap_t)();

static inline void tgetc()
{
    registers[R0] = getchar();
};

static inline void tout()
{
    putchar(registers[R0]);
};

static inline void tputs()
{
    word_t *p = memory + registers[R0];
    while (*p)
        putchar(*p++);
};

static inline void tin()
{
    // registers[R0] = getchar();
    // putchar(registers[R0]);
    putchar(registers[R0] = getchar());
};

static inline void tputsp(){/* TODO: */};

static inline void thalt()
{
    running = false;
};

static inline void tinu16()
{
    scanf("%hu", &registers[R0]);
};
static inline void toutu16()
{
    printf("%hu\n", registers[R0]);
};

trap_t traps[8] = {tgetc, tout, tputs, tin, tputsp, thalt, tinu16, toutu16};