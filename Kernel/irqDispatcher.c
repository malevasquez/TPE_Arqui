//FALTA
void irqDispatcher(unint64_t irq) {
    switch(irq) {
        case 0:
            int_20();
            break;
    }
    return;
}

void int_20() {
    timer_handler();
}
