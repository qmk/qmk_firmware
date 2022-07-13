#include QMK_KEYBOARD_H

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
        KC_AUDIO_VOL_UP, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN,
        _______, _______, _______
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
