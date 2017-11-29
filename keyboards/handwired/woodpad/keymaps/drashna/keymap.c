/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "woodpad.h"
#include "drashna.h"

 // Each layer gets a name for readability, which is then used in the keymap matrix below.
 // The underscores don't mean anything - you can have a layer called STUFF or any other name.
 // Layer names don't all need to be of the same length, obviously, and you can also skip them
 // entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#ifdef TAP_DANCE_ENABLE
#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
#endif


//define layer change stuff for underglow indicator
bool skip_leds = false;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NUMLOCK] = KEYMAP( /* Base */
    TG(_NAV), TG(_DIABLO), TG(_MACROS), KC_PSLS,\
    KC_P7,  KC_P8, KC_P9, KC_PAST,   \
    KC_P4,  KC_P5, KC_P6, KC_PMNS,   \
    KC_P1,  KC_P2, KC_P3, KC_PPLS,   \
    LT(_MEDIA,KC_P0), KC_PDOT, KC_COLN, KC_PENT   \
),
[_NAV] = KEYMAP( /* Base */
    _______, _______, _______, _______,\
    KC_HOME,  KC_UP, KC_PGUP, _______,   \
    KC_LEFT,  XXXXXXX, KC_RIGHT, _______,   \
    KC_END,  KC_DOWN, KC_PGDN, _______,   \
    KC_INS, KC_DEL, _______, _______   \
),
[_DIABLO] = KEYMAP( /* Base */
    KC_ESC, _______, XXXXXXX, _______,\
    KC_S, KC_I, KC_F, KC_M,   \
    KC_1, KC_2, KC_3, KC_4, \
    KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, \
    XXXXXXX, KC_DIABLO_CLEAR, KC_Q, SFT_T(KC_SPACE)  \
),

[_MACROS] = KEYMAP( /* Base */
    KC_OVERWATCH, XXXXXXX,      _______,      XXXXXXX,\
    KC_JUSTGAME,  XXXXXXX,      XXXXXXX,      KC_C9,   \
    XXXXXXX,      XXXXXXX,      KC_AIM,       KC_GGEZ,   \
    KC_SYMM,      KC_TORB,      XXXXXXX,      KC_GOODGAME,   \
    KC_SALT,      KC_MORESALT,  KC_SALTHARD,  KC_GLHF   \
),
[_MEDIA] = KEYMAP( /* Base */
    KC_RESET, KC_MUTE, KC_VOLD, KC_VOLU,\
    KC_MAKE, _______, RGB_HUI, RGB_HUD,   \
    KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT,   \
    RGB_TOG, RGB_SMOD, RGB_SAI, RGB_VAI,   \
    _______, KC_RGB_T, RGB_SAD, RGB_VAD   \
),

};


void numlock_led_on(void) {
  PORTF |= (1 << 7);
}

void numlock_led_off(void) {
  PORTF &= ~(1 << 7);
}



void matrix_init_keymap(void) {
  // set Numlock LED to output and low
  DDRF |= (1 << 7);
  PORTF &= ~(1 << 7);


  if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

void matrix_scan_keymap(void) {
  numlock_led_off();
  if ((is_overwatch && biton32(layer_state) == _MACROS) || (biton32(layer_state) == _NUMLOCK)) {
    numlock_led_on();
  }

  // Run Diablo 3 macro checking code.
}

