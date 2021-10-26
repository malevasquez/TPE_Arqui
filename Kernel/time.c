static unsigned long ticks = 0;

void timer_handler() {
    ticks++;
}

/*
//PRETPE
int ticks_elapsed() {
    return ticks;
}

int seconds_elapsed() {
    return ticks / 18;
}
*/
