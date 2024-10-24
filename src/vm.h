#ifndef CK_VM_H
#define CK_VM_H
#include <stddef.h>
#include <stdint.h>

#include "chunk.h"
#include "value.h"

#define CK_VM_STACK_SIZE 512

typedef struct ck_vm {
    const ck_chunk *chunk;
    uint8_t *ip;

    ck_value stack[CK_VM_STACK_SIZE];
    size_t stack_top;
} ck_vm;

typedef enum ck_result {
    CK_RESULT_OK,
    CK_RESULT_COMPILE_ERR,
    CK_RESULT_RUNTIME_ERR,
} ck_result;

void ck_vm_init(ck_vm *vm);
void ck_vm_free(ck_vm *vm);
ck_result ck_vm_interpret(ck_vm *vm, const ck_chunk *chunk);

#endif /* CK_VM_H */
