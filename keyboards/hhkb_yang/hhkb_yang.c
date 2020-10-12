#include "hhkb_yang.h"

void keyboard_pre_init_kb(void) {
    // BT power up
    setPinOutput(D5);
    writePinLow(D5);

    // Row selectors
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);

    // Col selectors
    setPinOutput(B3);
    setPinOutput(B4);
    setPinOutput(B5);

    // Key strobe
    setPinOutput(B6);
    writePinHigh(B6);

    // Key: input with pull-up
    setPinInputHigh(D7);

    // Unused pins on Pro2 ANSI
    // Input with pull up to save power
    setPinInputHigh(C6);
    setPinInputHigh(C7);

    // Turn on switch PCB
    setPinOutput(D6);
    writePinLow(D6);
}
