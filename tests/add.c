#include "../src/operations.c"

int add1()
{
    uint32_t pass = 0;
    word_t opcode = 0b0001;
    word_t instruction = 0b0001000000000000;
    for (int dr = 0; dr < 8; dr++)
    {
        instruction |= (dr << 9);
        for (int sr1 = 0; sr1 < 8; sr1++)
        {
            instruction |= (sr1 << 6);
            for (int sr2 = 0; sr2 < 8; sr2++)
            {
                instruction |= sr2;

                word_t op1 = registers[sr1], op2 = registers[sr2];
                operations[opcode](instruction);
                word_t res = registers[dr];
                word_t expected = op1 + op2;

                if (expected == res)
                    pass++;
                else
                    printf("\n%d + %d = %d\n", op1, op2, res);

                instruction &= (WORD_MAX << 6);
            }
            instruction &= (WORD_MAX << 9);
        }
        instruction &= (WORD_MAX << 12);
    }
    return pass;
}

int add2()
{
    uint32_t pass = 0;
    word_t opcode = 0b0001;
    word_t instruction = 0b0001000000100000;
    for (int dr = 0; dr < 8; dr++)
    {
        instruction |= (dr << 9);
        for (int sr1 = 0; sr1 < 8; sr1++)
        {
            instruction |= (sr1 << 6);
            for (int imm = 0; imm < 32; imm++)
            {
                instruction |= imm;

                word_t op1 = registers[sr1], op2 = sgnext(imm, 5);
                operations[opcode](instruction);
                word_t res = registers[dr];
                word_t expected = op1 + op2;

                if (expected == res)
                    pass++;
                else
                    printf("\n%d + %d = %d\n", op1, op2, res);

                instruction &= (WORD_MAX << 6) | (1 << 5);
            }
            instruction &= (WORD_MAX << 9) | (1 << 5);
        }
        instruction &= (WORD_MAX << 12) | (1 << 5);
    }
    return pass;
}
