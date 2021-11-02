#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <stdint.h>

int read(char *buffer, int length);

int write(char *buffer, int row, int col, int color);

void draw(int *matrix, int row, int col, int rows, int columns);

void clearScreen();

void memoryDump(char *dir, char *dump);

int getScreenHeight();

int getScreenWidth();

#endif
