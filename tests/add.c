#include "tests.c"

static inline word_t test_add(word_t op1, word_t op2) { return op1 + op2; }

int add_sr2()
{
    return op_sr2(0b0001, test_add);
}

int add_imm()
{
    return op_imm(0b0001, test_add);
}
