#include "vm.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "opcode.h"

static ck_value peek(const ck_vm *vm) {
    if (vm->stack_top == 0) {
        fprintf(stderr, "Stack underflow");
        exit(EXIT_FAILURE);
    }

    return vm->stack[vm->stack_top - 1];
}

static ck_value pop(ck_vm *vm) {
    if (vm->stack_top == 0) {
        fprintf(stderr, "Stack underflow");
        exit(EXIT_FAILURE);
    }

    vm->stack_top--;
    return vm->stack[vm->stack_top];
}

static void push(ck_vm *vm, ck_value value) {
    if (vm->stack_top >= CK_VM_STACK_SIZE) {
        fprintf(stderr, "Stack overflow");
        exit(EXIT_FAILURE);
    }

    vm->stack[vm->stack_top] = value;
    vm->stack_top++;
}

static uint8_t read_byte(ck_vm *vm) {
    return *vm->ip++;
}

void ck_vm_init(ck_vm *vm) {
    vm->chunk = NULL;
    vm->ip = NULL;
    vm->stack_top = 0;
}

void ck_vm_free(ck_vm *vm) {
    (void)vm;
}

ck_result ck_vm_interpret(ck_vm *vm, const ck_chunk *chunk) {
    vm->chunk = chunk;
    vm->ip = chunk->code;

    while (true) {
        uint8_t instruction = read_byte(vm);
        switch (instruction) {
        case CK_OP_RETURN:
            return CK_RESULT_OK;
        case CK_OP_CONSTANT: {
            uint8_t constant_idx = read_byte(vm);
            ck_value constant = chunk->constants[constant_idx];
            push(vm, constant);
            break;
        }
        case CK_OP_NEGATE: {
            push(vm, -pop(vm));
            break;
        }
        case CK_OP_ADD: {
            double b = pop(vm);
            double a = pop(vm);
            push(vm, a + b);
            break;
        }
        case CK_OP_SUB: {
            double b = pop(vm);
            double a = pop(vm);
            push(vm, a - b);
            break;
        }
        case CK_OP_MUL: {
            double b = pop(vm);
            double a = pop(vm);
            push(vm, a * b);
            break;
        }
        case CK_OP_DIV: {
            double b = pop(vm);
            double a = pop(vm);
            push(vm, a / b);
            break;
        }
        case CK_OP_PRINT: {
            printf("%f\n", peek(vm));
            break;
        }
        }
    }
}
