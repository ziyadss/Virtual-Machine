#include "tests.c"

static inline word_t test_and(word_t op1, word_t op2) { return op1 & op2; }

int and_sr2()
{
    return op_sr2(0b0101, test_and);
}

int and_imm()
{
    return op_imm(0b0101, test_and);
}
