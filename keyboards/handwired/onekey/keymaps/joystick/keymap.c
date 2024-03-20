#include QMK_KEYBOARD_H

#ifndef ADC_PIN
#    define ADC_PIN F6
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(JS_0)
};

void matrix_scan_user(void) {
    int16_t val = (((uint32_t)timer_read() % 5000 - 2500) * 255) / 5000;
    joystick_set_axis(1, val);
}

// Joystick config
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(ADC_PIN, 0, 512, 1023),
    [1] = JOYSTICK_AXIS_VIRTUAL
};
