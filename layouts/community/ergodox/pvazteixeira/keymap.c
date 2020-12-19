/* Copyright 2020 Pedro Vaz Teixeira (@pvazteixeira)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include QMK_KEYBOARD_H

// handle differences below:
/* #ifdef (KEYBOARD_ergodox_infinity) */
/* #elif defined(KEYBOARD_ergodox_ez) */
/* #endif */

enum layers{
  BASE,
  SYMB,
  MDIA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ergodox(
      // left hand
      KC_GRV,         KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_NO,   // 7
      KC_NO,          KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    KC_RBRC, // 7
      KC_NO,          KC_A,        KC_S,          KC_D,    KC_F,    KC_G,             // 6 20
      KC_NO,          KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,    KC_BSPC, // 7 27
      KC_NO,          KC_NO,       KC_NO,         KC_NO,   KC_NO,  // 5 32
      KC_VOLD, KC_VOLU, // 2 34
      KC_NO, // 1 35
      LCTL_T(KC_TAB), LGUI_T(KC_ESC),  MO(SYMB), // 3 38

      // right hand
      KC_NO,        KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_EQUAL, // 7
      KC_LBRC,      KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_BSLS,  // 7, 14
      KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT, // 6,20
      KC_MINS,      KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,  KC_LALT, // 7,27
      KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO, // 5,32
      KC_VOLD, KC_VOLU,
      KC_NO, //
      MO(SYMB), LALT_T(KC_ENT), LSFT_T(KC_SPC)
                          ),
  [SYMB] = LAYOUT_ergodox(
      // left hand
      KC_NO,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,
      KC_NO, KC_EXLM, KC_PGUP,   KC_UP, KC_PGDN, KC_PIPE, KC_TRNS,
      KC_NO, KC_HOME, KC_LEFT,  KC_DOWN, KC_RIGHT, KC_END,
      KC_NO, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_DEL,
      KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_DEL,
      KC_NO, KC_NO,
      KC_NO,
      KC_NO, KC_NO, KC_TRNS,
      // right hand
      KC_NO, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      KC_NO, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
      KC_LEFT, KC_DOWN,    KC_UP,    KC_LEFT,    KC_NO, KC_NO,
      KC_NO, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
      KC_NO, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
      KC_NO, KC_NO,
      KC_NO,
      KC_TRNS, KC_NO, KC_NO
                          ),

  [MDIA] = LAYOUT_ergodox(
      // left hand
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
      KC_TRNS, KC_TRNS,
      KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,
      // right hand
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
      KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,
      KC_TRNS,
      KC_TRNS, KC_TRNS, KC_WBAK
                          ),
};

/*
  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Log event
        uprintf("KL: col=%02d, row=%02d, pressed=%d, layer=%d\n", record->event.key.col, record->event.key.row, record->event.pressed, get_highest_layer(layer_state));

        switch (keycode) {
            case EPRM:
                eeconfig_init();
                return false;
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
#ifdef RGBLIGHT_ENABLE
            case RGB_SLD:
                rgblight_mode(1);
                return false;
#endif
        }
    }
    return true;
}
*/

/* Runs just one time when the keyboard initializes. */
void matrix_init_user(void) {
    /* Duplicate 'cfq_word_lut[0][...]' into 'cfq_word_lut[1][...]' */
    /* { */
    /*     char *d = cfq_word_lut_title_caps; */
    /*     for (uint16_t i = 0; i < 26; i++) { */
    /*         char *s            = cfq_word_lut[0][i]; */
    /*         cfq_word_lut[1][i] = d; */
    /*         while ((*d++ = *s++)) { */
    /*         } */
    /*     } */
    /* } */
    /* /\* Title caps. *\/ */
    /* for (uint16_t i = 0; i < 26; i++) { */
    /*     char *w             = cfq_word_lut[1][i]; */
    /*     bool  prev_is_alpha = false; */
    /*     if (*w) { */
    /*         while (*w) { */
    /*             bool is_lower = (*w >= 'a' && *w <= 'z'); */
    /*             bool is_upper = (*w >= 'A' && *w <= 'Z'); */
    /*             if (prev_is_alpha == false && is_lower) { */
    /*                 *w -= ('a' - 'A'); */
    /*             } */
    /*             prev_is_alpha = is_lower || is_upper; */
    /*             w++; */
    /*         } */
    /*     } */
    /* } */
};

/* Runs constantly in the background, in a loop. */
void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            /* none */
            break;
    }
};
