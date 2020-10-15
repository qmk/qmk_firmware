#include "hhkb_yang.h"

extern uint8_t power_save_level;

void hhkb_led_on(uint8_t led) {
    switch (led) {
        case 1:
            writePinHigh(F4);
            break;
        case 2:
            writePinHigh(F2);
            break;
        case 3:
            writePinHigh(F0);
            break;
    }
}

void hhkb_led_off(uint8_t led) {
    switch (led) {
        case 1:
            writePinLow(F4);
            break;
        case 2:
            writePinLow(F2);
            break;
        case 3:
            writePinLow(F0);
            break;
    }
}

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

    // LED pin configuration
    setPinOutput(F0);
    setPinOutput(F1);
    setPinOutput(F4);
    writePinLow(F0);
    writePinLow(F1);
    writePinLow(F4);

    // Turn on switch PCB
    setPinOutput(D6);
    writePinLow(D6);
}

void suspend_power_down_kb(void) {
    if (power_save_level > 2) {
        // Disable UART TX to avoid current leakage
        UCSR1B &= ~_BV(TXEN1);
        // Power down BLE module
        writePinHigh(D5);
    }
}

void suspend_wakeup_init_kb(void) {
    // Power up BLE module
    writePinLow(D5);
    // Enable UART TX
    UCSR1B |= _BV(TXEN1);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(F4, led_state.caps_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);

    writePin(F1, IS_LAYER_ON_STATE(state, 1));
    writePin(F0, IS_LAYER_ON_STATE(state, 2));

    return state;
}
