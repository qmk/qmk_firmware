#include "hhkb_yang.h"

void keyboard_pre_init_kb(void) {
    // Disable BT power
    setPinOutput(D5);
    writePinHigh(D5);

    /* Row selectors */
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);

    /* Col selectors */
    setPinOutput(B3);
    setPinOutput(B4);
    setPinOutput(B5);

    /* Key strobe */
    setPinOutput(B6);
    writePinHigh(B6);

    /* Key: input with pull-up */
    setPinInputHigh(D7);
}
