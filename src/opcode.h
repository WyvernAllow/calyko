#ifndef CK_OPCODE_H
#define CK_OPCODE_H

typedef enum ck_opcode {
    CK_OP_RETURN,
    CK_OP_CONSTANT,
    CK_OP_NEGATE,
    CK_OP_ADD,
    CK_OP_SUB,
    CK_OP_MUL,
    CK_OP_DIV,

    /* This instruction is temporary. In the future, some kind of FFI would
     * be better.
     */
    CK_OP_PRINT,

    CK_OPCODE_COUNT
} ck_opcode;

const char *ck_opcode_str(ck_opcode opcode);

#endif /* CK_OPCODE_H */
