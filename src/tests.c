#include "operations.c"

void print_registers()
{
    for (enum REG r = 0; r < RCNT; r++)
        printf("%d: %d,   \t", r, registers[r]);
    printf("\n");
}

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

                if (op1 + op2 == res)
                    pass++;
                else
                    printf("%d + %d = %d\n", op1, op2, res);

                instruction &= (WORD_MAX << 6);
            }
            instruction &= (WORD_MAX << 9);
        }
        instruction &= (WORD_MAX << 12);
    }
    return pass;
}

int main()
{
    registers[0] = 0;
    registers[1] = 1;
    registers[2] = 2;
    registers[3] = 3;
    registers[4] = 4;
    registers[5] = 5;
    registers[6] = 6;
    registers[7] = 7;

    print_registers();
    printf("%d\n", add1());
    print_registers();

    return 0;
}