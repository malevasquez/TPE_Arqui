#include <stdint.h>
#include <time.h>

#define TIMER_TICK 0
#define KEYBOARD 1

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq) {
    switch(irq) {
        case TIMER_TICK:
            int_20();
            break;
        case KEYBOARD:
            int_21();
            break;
        default:
            break;
    }
    return;
}


void int_20() {
    timerHandler();
}

void int_21() {
    keyboardHandler();
}
