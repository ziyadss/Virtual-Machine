#pragma once

#include "header.h"
#include "memory.c"
#include "traps.c"

#define OP_COUNT 16
typedef void (*operation_t)(word_t instruction);

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

static inline bool bit(word_t num, int bit) { return (num >> bit) & 1; }

static inline word_t opcode(word_t instruction) { return instruction >> 12; }
static inline word_t dr(word_t instruction) { return (instruction >> 9) & 0x7; }
static inline word_t sr1(word_t instruction) { return (instruction >> 6) & 0x7; }
static inline word_t sr2(word_t instruction) { return instruction & 0x7; }
static inline word_t off(word_t instruction, int bits) { return instruction & ((1 << bits) - 1); }

static inline word_t sgnext(word_t num, int bits) { return (num >> (bits - 1) & 1) ? (num | WORD_MAX << bits) : num; }
static inline word_t sgnextoff(word_t instruction, int bits) { return sgnext(off(instruction, bits), bits); }

static inline void br(word_t instruction)
{
    if (registers[RCND] & dr(instruction))
        registers[RPC] += sgnextoff(instruction, 9);
};

static inline void add(word_t instruction)
{
    word_t op1 = registers[sr1(instruction)];
    word_t op2 = bit(instruction, 5) ? sgnextoff(instruction, 5) : registers[sr2(instruction)];

    word_t dst = dr(instruction);
    registers[dst] = op1 + op2;
    uf(dst);
};

static inline void ld(word_t instruction)
{
    word_t dst = dr(instruction);
    registers[dst] = mem_read(registers[RPC] + sgnextoff(instruction, 9));
    uf(dst);
};

static inline void st(word_t instruction)
{
    mem_write(registers[RPC] + sgnextoff(instruction, 9), registers[dr(instruction)]);
};

static inline void jsr(word_t instruction)
{
    registers[R7] = registers[RPC];
    registers[RPC] = bit(instruction, 11) ? registers[RPC] + sgnextoff(instruction, 11) : registers[sr1(instruction)];
};

static inline void and (word_t instruction)
{
    word_t op1 = registers[sr1(instruction)];
    word_t op2 = bit(instruction, 5) ? sgnextoff(instruction, 5) : registers[sr2(instruction)];

    word_t dst = dr(instruction);
    registers[dst] = op1 & op2;
    uf(dst);
};

static inline void ldr(word_t instruction)
{
    word_t dst = dr(instruction);
    registers[dst] = mem_read(registers[sr1(instruction)] + sgnextoff(instruction, 9));
    uf(dst);
};

static inline void str(word_t instruction)
{
    mem_write(registers[sr1(instruction)] + sgnextoff(instruction, 9), registers[dr(instruction)]);
};

static inline void rti(word_t instruction){};

static inline void not(word_t instruction)
{
    word_t dst = dr(instruction);
    registers[dst] = ~registers[sr1(instruction)];
    uf(dst);
};

static inline void ldi(word_t instruction)
{
    word_t dst = dr(instruction);
    registers[dst] = mem_read(mem_read(registers[RPC] + sgnextoff(instruction, 9)));
    uf(dst);
};

static inline void sti(word_t instruction)
{
    mem_write(mem_read(registers[RPC] + sgnextoff(instruction, 9)), registers[dr(instruction)]);
};

static inline void jmp(word_t instruction)
{
    registers[RPC] = registers[sr1(instruction)];
};

static inline void res(word_t instruction){};

static inline void lea(word_t instruction)
{
    word_t dst = dr(instruction);
    registers[dst] = registers[RPC] + sgnextoff(instruction, 9);
    uf(dst);
};

static inline void trap(word_t instruction)
{
    traps[off(instruction, 8) - TRAP_OFFSET]();
};

operation_t operations[OP_COUNT] = {br, add, ld, st, jsr, and, ldr, str, rti, not, ldi, sti, jmp, res, lea, trap};