#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
    		KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_0 )

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
}

void matrix_init_user(void)
{
}

void matrix_scan_user(void)
{
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    return true;
}
