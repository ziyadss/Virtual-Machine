#include "add.c"

void print_registers()
{
    printf("\n");
    for (enum REG r = 0; r < RCNT; r++)
        printf("%d: %d,   \t", r, registers[r]);
    printf("\n");
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
    printf("\n%d\n", add1());
    print_registers();
    printf("\n%d\n", add2());
    print_registers();

    return 0;
}