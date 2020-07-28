#include "msgeq7.h"

void msgeq7_init (void) {
    setPinOutput(MSGEQ7_RST_PIN);
    setPinOutput(MSGEQ7_STROBE_PIN);
    writePinHigh(MSGEQ7_STROBE_PIN);
    writePinHigh(MSGEQ7_RST_PIN);
}

void msgeq7_read (int *buf) {
    /* reset sequence */
    _delay_us(1);       /* tr ... 0.1us min */
    writePinLow(MSGEQ7_RST_PIN);
    _delay_us(100);     /* trs ... 72us min */

    /* read 7 bands */
    for (int i = 0; i < 7; i++) {
        writePinLow(MSGEQ7_STROBE_PIN);
        _delay_us(50);      /* to ... 36us min */
        buf[i] = analogReadPin(MSGEQ7_OUT_PIN) - NOISE_FLOOR;
        if (buf[i] < 0) buf[i] = 0;
        writePinHigh(MSGEQ7_STROBE_PIN);
        _delay_us(50);      /* tss - to ... 36us min */
    }

    writePinHigh(MSGEQ7_RST_PIN);
}
