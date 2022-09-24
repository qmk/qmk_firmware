#include QMK_KEYBOARD_H

#ifndef ADC_PIN
#    define ADC_PIN F6
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(JS_BUTTON0)
};

void matrix_scan_user() {
    int16_t val = (((uint32_t)timer_read() % 5000 - 2500) * 255) / 5000;

    if (val != joystick_status.axes[1]) {
        joystick_status.axes[1] = val;
        joystick_status.status |= JS_UPDATED;
    }
}

// Joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(ADC_PIN, 0, 512, 1023),
    [1] = JOYSTICK_AXIS_VIRTUAL
};
