#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x3(
        KC_LEFT_CTRL, 
        KC_ESCAPE, KC_LEFT_GUI, KC_BACKSPACE,
        KC_TAB, KC_NUM_LOCK, KC_RIGHT_ALT,
        KC_LEFT_CTRL, KC_A, KC_ENTER,
        KC_B, KC_C, KC_D
    )
};
#ifdef OLED_ENABLE

bool oled_task_user() {
    oled_clear();
    oled_write_P(PSTR("Testing OLED!"), false); // Replace THIS line with whatever you'd like the OLED to display.
    // There are more details in the OLED page!
    return false;
}

#endif

