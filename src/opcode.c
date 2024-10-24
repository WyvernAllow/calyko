#include "opcode.h"

const char *ck_opcode_str(ck_opcode opcode) {
    switch (opcode) {
    case CK_OP_RETURN:
        return "RETURN";
    case CK_OP_CONSTANT:
        return "CONSTANT";
    case CK_OP_NEGATE:
        return "NEGATE";
    case CK_OP_ADD:
        return "ADD";
    case CK_OP_SUB:
        return "SUB";
    case CK_OP_MUL:
        return "MUL";
    case CK_OP_DIV:
        return "DIV";
    case CK_OP_PRINT:
        return "PRINT";
    default:
        return "UNKNOWN";
    }
}
