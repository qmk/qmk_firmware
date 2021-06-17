
#include "mock_split.h"

bool pins[32] = {0};
bool pinIsInputHigh[32] = {0};

uint8_t mockSetPinInputHigh(pin_t pin) {
    // dprintf("Setting pin %d input high.", pin);
    pins[pin] = true;
    pinIsInputHigh[pin] = true;
    return 0;
}

bool mockReadPin(pin_t pin) {
    return pins[pin];
}

bool setPin(pin_t pin, bool val) {
    pins[pin] = val;
    return val;
}

void last_encoder_activity_trigger(void) {}
