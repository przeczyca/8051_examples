#include <mcs51/8051.h>

#include <examples.h>

const char digitMap[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11100110  // 9
};

void sevenSegmentTest(void) {
    P0 = 0xFF;
    P2_0 = 0;
    P2_1 = 1;
    
    // start timer for multiplexing
    TMOD = 0x11;    // Set both timers to mode 1
    TH0 = 0xEE;
    TL0 = 0x00;
    TR0 = 1;

    // start timer for counter
    TH1 = 0xEE;
    TL1 = 0x00;
    TR1 = 1;

    
    int leftDigit = 0;
    int rightDigit = 1;
    int overflowCount = 0;
    while (1) {
        if (TF0 != 0) {
            P0 = 0xFF;
            P2_0 = !P2_0;
            P2_1 = !P2_1;
            TF0 = 0;
            TH0 = 0xEE;
            TL0 = 0x00;
        }

        if (TF1 != 0) {
            if (overflowCount == 200) {
                rightDigit++;
                if (rightDigit > 9) {
                    rightDigit = 0;
                    leftDigit++;
                }
                if (leftDigit > 9) {
                    leftDigit = 0;
                }
                overflowCount = 0;
            }

            overflowCount++;
            TF1 = 0;
            TH1 = 0xEE;
            TL1 = 0x00;
        }

        if (P2_0) {
            P0 = ~digitMap[leftDigit];
        }
        else if (P2_1) {
            P0 = ~digitMap[rightDigit];
        }
    }
}