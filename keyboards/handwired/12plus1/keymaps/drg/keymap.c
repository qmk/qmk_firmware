#include QMK_KEYBOARD_H

# define BASE 0
# define NAV 1
# define NUM 2
# define DRG 3

enum custom_keycodes {
    DRGREADY1 = SAFE_RANGE,
    DRGREADY2,
    DRGEGG,
    DRGPLAT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DRGREADY1:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ENTER)"Ready!"SS_TAP(X_ENTER));
        }
        break;

    case DRGREADY2:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ENTER)"Everyone Ready?"SS_TAP(X_ENTER));
        }
        break;

    case DRGPLAT:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ENTER)"Platform needed here"SS_TAP(X_ENTER));
        }
        break;

    case DRGEGG:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ENTER)"Next egg?"SS_TAP(X_ENTER));
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        RESET,   KC_COPY, KC_PASTE, KC_VOLU,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
        TO(NAV),   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE
    ),

    [NAV] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX,
        KC_PGUP, KC_UP,   XXXXXXX, KC_PGUP,
        TO(NUM),   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
    ),

    [NUM] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        TO(DRG),   KC_9,    KC_0,    XXXXXXX, RESET
    ),

    [DRG] = LAYOUT(
        DRGREADY1,    DRGREADY2,    KC_V,    KC_V,
        DRGPLAT,    DRGEGG,    KC_V,    KC_V,
        TO(BASE),   XXXXXXX,    XXXXXXX,    KC_V, KC_V
    ),


};
