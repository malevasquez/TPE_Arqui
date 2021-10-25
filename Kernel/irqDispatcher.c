#include <stdint.h>

void int_20() {
    timer_handler();
}

void irqDispatcher(uint64_t irq) {
    switch(irq) {
        case 0:
            int_20();
            break;
    }
    return;
}
