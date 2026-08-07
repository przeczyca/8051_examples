#include <mcs51/8051.h>

#include <examples.h>

void timerTest(void)
{
    // initialize timer (5ms)
    TMOD = 0x01;
    TH0 = 0xEE;
    TL0 = 0x00;
    TR0 = 1;

    P2=0x00;
    char overflowCount = 0;
    while(1) {
        if (TF0 != 0) {
            if (overflowCount >= 200) {
                P2 = ~P2;
                overflowCount = 0;
            }
            overflowCount++;
            TF0 = 0;
            TH0 = 0xEE;
            TL0 = 0x00;
        }
    }
}