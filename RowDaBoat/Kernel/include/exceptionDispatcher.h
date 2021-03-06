#ifndef EXCEPTION_DISPATCHER_H
#define EXCEPTION_DISPATCHER_H

#include <stdint.h>
#include <lib.h>
#include <naiveConsole.h>
#include <registers.h>
#include <videoDriver.h>
#include <syscallDispatcher.h>
#include <prints.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6

static char *registerNames[] = {
    "R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ",
    "R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
    "RAX: ", "RIP: ", "RSP: "};

void printRegisters(uint64_t *registers);
void exceptionRegisters(uint64_t exception, uint64_t *registers);
void zero_division();
void invalid_OpCode();
void exceptionDispatcher(uint64_t exception, uint64_t *registers);
#endif