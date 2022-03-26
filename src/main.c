#include "operations.c"

void loadFile(char *fileName, word_t offset)
{
    FILE *inFile = fopen(fileName, "rb");
    if (inFile == NULL)
    {
        fprintf(stderr, "Cannot open file %s.\n", fileName);
        exit(1);
    }

    word_t *p = memory + PC_START + offset;

    fread(p, sizeof(word_t), WORD_MAX - PC_START, inFile);

    fclose(inFile);
}

void start(word_t offset)
{
    registers[RPC] = PC_START + offset;
    running = true;

    while (running)
    {
        word_t instruction = mem_read(registers[RPC]++);

        operations[opcode(instruction)](instruction);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    loadFile(argv[1], 0);
    start(0);

    return 0;
}
