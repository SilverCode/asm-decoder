#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "instructions.h"

int16_t decode_instruction(uint8_t byte[], instruction *ins) {
    // MOV instruction
    const uint8_t count = opcode_count();

    for (uint8_t i = 0; i  < count; ++i) {
        opcode oc = opcodes[i];

        if ((byte[0] & ~oc.mask) == oc.code) {
            ins->opcode = oc;
            ins->wide = (byte[0] >> 0) & 0b00000001;
            ins->dst = (byte[0] >> 1) & 0b00000001;

            ins->rm  = (byte[1] >> 0) & 0b00000111;
            ins->r = (byte[1] >> 3) & 0b00000111;
            ins->mod = (byte[1] >> 6) & 0x00000011;

            return ins->opcode.id;
        }
    }

    return -1;
}

void decode_file(const char *filename) {
    FILE *f = fopen(filename, "rb");

    instruction ins = {0};

    do {
        uint8_t byte[BPI] = {0};
        size_t bytes_read = fread(&byte, sizeof(uint8_t), BPI, f);

        if (bytes_read != 0 && decode_instruction(byte, &ins) > 0) {
            const char* src;
            const char* dst;

            if (ins.dst) {
                src = reg_name(ins.rm, ins.wide);
                dst = reg_name(ins.r, ins.wide);
            } else {
                dst = reg_name(ins.rm, ins.wide);
                src = reg_name(ins.r, ins.wide);
            }

            printf("%s %s, %s\n", ins.opcode.mnemonic, dst, src);
        }
    } while (!feof(f));

    fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a file name\n");
    }

    decode_file(argv[1]);

    return 0;
}
