#include QMK_KEYBOARD_H

/* enum custom macros */
enum custom_keycodes {
    COPY = SAFE_RANGE,
    PASTE,
    WINCLIP,
};

/* custom macros */
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

/* what each layer does */
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
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
        COPY, PASTE, WINCLIP,
        KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, MO(1)
    ),

    [1] = LAYOUT_macro_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, MO(2), _______
    ),

    [2] = LAYOUT_macro_3x3(
        _______, _______, _______,
        _______, _______, _______,
        MO(3), _______, _______
    ),

    [3] = LAYOUT_macro_3x3(
        RGB_TOG, RGB_MODE_PLAIN, RGB_MODE_BREATHE,
        RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MODE_GRADIENT,
        _______, _______, _______
    )
};
