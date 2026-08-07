#include <mcs51/8051.h>

#include <examples.h>

void delay(int ms) {
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < 120; j++);
    }
}

void blinky(void) {
    P2 = 0;
    char count = 0;

    while (1) {
        P2 = count;
        count++;
        delay(500);
    }
}