//
// Created by Ross Simpson on 2023/03/05.
//

#ifndef ASM_DECODER_INSTRUCTIONS_H
#define ASM_DECODER_INSTRUCTIONS_H

#include <stdint.h>

#define BPI 2 // Bytes per instruction

typedef struct opcode {
    uint8_t id;
    uint8_t code;
    uint8_t mask;
    const char *mnemonic;
} opcode;

enum {
    I_NOP,
    I_MOV,
    I_PSH
};

const opcode opcodes[] = {
        {.id = I_NOP, .code = 0b00000000, .mask = 0b00000000, .mnemonic = "nop"},
        {.id = I_MOV, .code = 0b10001000, .mask = 0b00000011, .mnemonic = "mov"},
        {.id = I_PSH, .code = 0b11111100, .mask = 0b00000011, .mnemonic = "push"}
};

typedef struct reg {
    char *name;
    char *name_wide;
} reg;

const reg registers[] = {
        { .name = "al", .name_wide = "ax" },
        { .name = "cl", .name_wide = "cx" },
        { .name = "dl", .name_wide = "dx" },
        { .name = "bl", .name_wide = "bx" },
        { .name = "ah", .name_wide = "sp" },
        { .name = "ch", .name_wide = "bp" },
        { .name = "dh", .name_wide = "si" },
        { .name = "bh", .name_wide = "di" },
};


uint8_t opcode_count() {
    return sizeof(opcodes)/sizeof(opcode);
}

uint8_t reg_count() {
    return sizeof(registers)/sizeof(reg);
}

const char *reg_name(uint8_t r, bool wide) {
    if (r > reg_count()) {
        return NULL;
    }

    return wide ? registers[r].name_wide : registers[r].name;
}

typedef struct instruction {
    opcode opcode;
    bool dst;
    bool wide;
    uint8_t rm;
    uint8_t r;
    uint8_t mod;
} instruction;

#endif //ASM_DECODER_INSTRUCTIONS_H
