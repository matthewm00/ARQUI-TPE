#ifndef COMMANDS_H
#define COMMANDS_H

#include <shell.h>

void help(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

void getCurrentDayTime(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

void getInfoReg(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

void divZero(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

void opCode(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

extern void opcodeExp(void);

void clear(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

void exit(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

void getMem(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE]);

#endif