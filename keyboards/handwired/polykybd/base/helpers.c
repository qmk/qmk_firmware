#include "helpers.h"

void peripherals_reset(void) {
    setPinOutput(HW_RST_PIN);
    writePinLow(HW_RST_PIN);
    wait_us(2);
    writePinHigh(HW_RST_PIN);
}