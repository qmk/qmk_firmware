#include <stdbool.h>
#include "gpio.h"
#include "ps2_io.h"

/* Check port settings for clock and data line */
#if !(defined(PS2_CLOCK_PIN))
#    error "PS/2 clock setting is required in config.h"
#endif

#if !(defined(PS2_DATA_PIN))
#    error "PS/2 data setting is required in config.h"
#endif

/*
 * Clock
 */
void clock_init(void) {}

void clock_lo(void) {
    setPinOutput(PS2_CLOCK_PIN);
    writePinLow(PS2_CLOCK_PIN);
}

void clock_hi(void) {
    setPinOutput(PS2_CLOCK_PIN);
    writePinHigh(PS2_CLOCK_PIN);
}

bool clock_in(void) {
    setPinInputHigh(PS2_CLOCK_PIN);
    return readPin(PS2_CLOCK_PIN);
}

/*
 * Data
 */
void data_init(void) {}

void data_lo(void) {
    setPinOutput(PS2_DATA_PIN);
    writePinLow(PS2_DATA_PIN);
}

void data_hi(void) {
    setPinOutput(PS2_DATA_PIN);
    writePinHigh(PS2_DATA_PIN);
}

bool data_in(void) {
    setPinInputHigh(PS2_DATA_PIN);
    return readPin(PS2_DATA_PIN);
}
