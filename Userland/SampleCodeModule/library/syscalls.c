// #include <types.h>
#include <syscalls.h>
#include <string.h>
#include <stdint.h>

#define READ_SYS 0
#define WRITE_SYS 1
#define DRAW_SYS 2
#define CLEAR_SYS 3
// #define INFO_REG 8
#define MEM_DUMP 9
#define HEIGHT 12           //que medidas?
#define WIDTH 13

int read(char *buffer, int length) {
    return _syscall(READ_SYS, length, buffer);
}

int write(char *buffer, int row, int col, int color) {
    int length = strlen(buffer);
    return _syscall(WRITE_SYS, length, buffer, row, col, color);
}

void draw(int *matrix, int row, int col, int rows, int columns) {
    _syscall(DRAW_SYS, matrix, row, col, rows, columns);
}

void clearScreen() {
    _syscall(CLEAR_SYS);
}


void memoryDump(char *dir, char *dump) {
    _syscall(MEM_DUMP, dir, dump);
}


int getScreenHeight() {
    return _syscall(HEIGHT);
}

int getScreenWidth() {
    return _syscall(WIDTH);
}
