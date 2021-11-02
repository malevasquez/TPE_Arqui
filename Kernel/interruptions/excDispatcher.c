#include <stdint.h>
#include <time.h>

#define DIV_ZERO 0
#define INV_OPCODE 1

static void zeroDivision();
static void invalidOpcode();

void exceptionDispatcher(int exception) {
    switch(exception) {
        case DIV_ZERO:
            zeroDivision();
            break;
        case INV_OPCODE:
            invalidOpcode();
            break;
        default:
            break;
    }
    return;
}

//ver si hay que hacer printf nuevos
void zeroDivision() {
    //printf("Exception 0: Cannot divide by 0");
}

void invalidOpcode() {
    //printf("Exception 6: Invalid operation code");
}
