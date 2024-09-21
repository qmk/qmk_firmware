#include QMK_KEYBOARD_H


enum layers {
  NORMAL_LAYER = 0,
  SECOND_LAYER
};

enum custom_keycode {
    VS_COMMENT = SAFE_RANGE,
    VS_UNCOMMENT,
    TST_STRING
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VS_COMMENT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("kc"));
            }
            break;
        case VS_UNCOMMENT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ku"));
            }
            break;
        case TST_STRING:
            if (record->event.pressed) {
                SEND_STRING("12345\n");
            }
            break;

    }
    return true;
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL_LAYER] = LAYOUT_ortho_2x4(
        VS_COMMENT, VS_UNCOMMENT, TST_STRING, KC_4,
        KC_5,       KC_6,         KC_7,       TO(1)
    ),
    [SECOND_LAYER] = LAYOUT_ortho_2x4(
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, TO(0)
    )
};
