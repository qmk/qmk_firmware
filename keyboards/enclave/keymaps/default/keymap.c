#include QMK_KEYBOARD_H

enum custom_keycodes {
    COPY = SAFE_RANGE,
    PASTE,
    WINCLIP,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case COPY:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("c"));
        }
        break;

    case PASTE:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("v"));
        }
        break;

    case WINCLIP:
        if (record->event.pressed) {
           SEND_STRING(SS_LGUI("v"));
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *    M = Macro
     * ┌────┬────┬────┐
     * │ M1 │ M2 │ M3 │
     * ├────┼────┼────┤
     * │ M4 │ M5 │ M6 │
     * ├────┼────┼────┤
     * │ M7 │ M8 │ M9 │
     * └────┴────┴────┘
     */
    [0] = LAYOUT_macro_3x3(
        KC_KB_VOLUME_UP,   KC_KB_VOLUME_DOWN,   KC_KB_MUTE,
        KC_MEDIA_PREV_TRACK,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK,
        COPY,   PASTE,   WINCLIP
    ),

    [1] = LAYOUT_macro_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    [2] = LAYOUT_macro_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    [3] = LAYOUT_macro_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    )
};
