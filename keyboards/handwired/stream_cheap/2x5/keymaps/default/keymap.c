#include QMK_KEYBOARD_H


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

#define LOCK LGUI(KC_L)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define FIND LCTL(KC_F)

enum layers {
  NORMAL_LAYER = 0,
  SECOND_LAYER
  // ,
  // THIRD_LAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL_LAYER] = LAYOUT_ortho_2x5(
        VS_COMMENT, VS_UNCOMMENT, LOCK, TST_STRING, KC_F5,
        KC_F9, KC_F10, KC_F11, KC_F12, TO(1)
    ),
    [SECOND_LAYER] = LAYOUT_ortho_2x5(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MSTP,
        CUT,     COPY,    PASTE,   FIND,    TO(0)
    )
    // ,
    // [THIRD_LAYER] = LAYOUT_ortho_2x5(
    //      KC_Q, KC_W, KC_E, KC_R, KC_T,
    //      KC_Y, KC_U, KC_L, KC_P, TO(0)
    // )
};
