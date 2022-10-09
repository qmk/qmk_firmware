#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC, KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_ENT, LCTL_T(KC_LGUI), KC_Z, KC_X, KC_C, KC_D, KC_V, LGUI(KC_L), MEH_T(KC_MINS), KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_LGUI, LT(1, KC_QUOT), KC_SFTENT, KC_SPC, LT(2, KC_BSLS), LALT_T(KC_APP)),
                                                              [1] = LAYOUT(KC_MPLY, KC_NO, KC_DQUO, KC_NO, LALT(KC_F4), KC_NO, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_NO, QK_BOOT, KC_MPRV, KC_END, KC_UP, KC_HOME, KC_PGUP, KC_NO, KC_P4, KC_P5, KC_P6, KC_PPLS, RGB_SAI, RGB_SAD, KC_MNXT, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_P1, KC_P2, KC_P3, KC_PAST, RGB_HUI, RGB_HUD, KC_NO, KC_WBAK, KC_WFWD, KC_WSTP, KC_WREF, KC_NO, LCA(KC_DEL), KC_NLCK, KC_P0, KC_P0, KC_PDOT, KC_PENT, RGB_SPI, RGB_SPD, KC_PSCR, KC_NO, KC_LGUI, RGB_TOG, RGB_VAI, RGB_VAD),
                                                              [2] = LAYOUT(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_NO, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_K, KC_NO, KC_WH_D, KC_MS_U, KC_WH_U, KC_NO, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _LOWER:
                clockwise ? tap_code(KC_MS_WH_UP) : tap_code(KC_MS_WH_DOWN);
                break;
            case _RAISE:
                clockwise ? rgblight_increase_hue() : rgblight_decrease_hue();
                break;
            default:
                clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _LOWER:
                clockwise ? tap_code(KC_UP) : tap_code(KC_DOWN);
                break;
            case _RAISE:
                clockwise ? tap_code(KC_MEDIA_NEXT_TRACK) : tap_code(KC_MEDIA_PREV_TRACK);
                break;
            default:
                clockwise ? tap_code(KC_RIGHT) : tap_code(KC_LEFT);
                break;
        }
    }
    return true;
}
#endif  // ENCODER_ENABLE
