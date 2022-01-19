#include "header.h"

static inline word_t OPCODE(word_t instruction) { return instruction >> 12; }

const word_t OP_COUNT = 16;
typedef void (*operation_t)(word_t instruction);

static inline void br(word_t instruction){};
static inline void add(word_t instruction){};
static inline void ld(word_t instruction){};
static inline void st(word_t instruction){};
static inline void jsr(word_t instruction){};
static inline void and (word_t instruction){};
static inline void ldr(word_t instruction){};
static inline void str(word_t instruction){};
static inline void rti(word_t instruction){};
static inline void not(word_t instruction){};
static inline void ldi(word_t instruction){};
static inline void sti(word_t instruction){};
static inline void jmp(word_t instruction){};
static inline void res(word_t instruction){};
static inline void lea(word_t instruction){};
static inline void trap(word_t instruction){};

const operation_t operations[OP_COUNT] = {br, add, ld, st, jsr, and, ldr, str, rti, not, ldi, sti, jmp, res, lea, trap};

enum flags
{
    FP = 1 << 0,
    FZ = 1 << 1,
    FN = 1 << 2
};

static inline void uf(enum REG r)
{
    if (registers[r] == 0)
        registers[RCND] = FZ;
    else if (registers[r] >> 15)
        registers[RCND] = FN;
    else
        registers[RCND] = FP;
}

#define SGNEXTIMM(i) sgn_ext(IMM(i), 5)
#define IMM(i) ((i) & 0x1F)
static inline word_t sgn_ext(word_t n, int b)
{
    return (n >> (b - 1) & 1) ? (n | WORD_MAX << b) : n;
}