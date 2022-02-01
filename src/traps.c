#pragma once

#include "header.h"

#define T_COUNT 8
#define TRAP_OFFSET 0x20
typedef void (*trap_t)();

static inline void tgetc(){};
static inline void tout(){};
static inline void tputs(){};
static inline void tin(){};
static inline void tputsp(){};
static inline void thalt(){};
static inline void tinu16(){};
static inline void toutu16(){};

trap_t traps[8] = {tgetc, tout, tputs, tin, tputsp, thalt, tinu16, toutu16};