/*
Copyright 2019 Stephen Peery

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

#include "quantum.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BASE = 0,
	_GAME = 1,
	_FL,
	_CL
};

enum layer_keycodes {
  BASE = SAFE_RANGE,
  GAME
};
// readability
#define XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
       │ Esc │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Fn │ Del │
       │───────────────────────────────────────────────────────────────│
       │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Hom│
       │───────────────────────────────────────────────────────────────│
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │PgU│
       │───────────────────────────────────────────────────────────────│
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │  Enter │PgD│
       │───────────────────────────────────────────────────────────────│
       │ LShift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │RSft│ ↑  │ End│
       │───────────────────────────────────────────────────────────────│
       │LCrl│GUI │LAlt│         Space          │RAlt│RCl│ ←  │ ↓  │ →  │
       └────┴────┴────┴────────────────────────┴────┴───┴────┴────┴────┘

       ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
       │     │   │   │   │   │   │   │   │   │   │   │   │   │   │     │
       │───────────────────────────────────────────────────────────────│
       │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │   │
       │───────────────────────────────────────────────────────────────│
       │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │   │
       │───────────────────────────────────────────────────────────────│
       │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │   │
       │───────────────────────────────────────────────────────────────│
       │ LShift │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │RSft│    │    │
       │───────────────────────────────────────────────────────────────│
       │    │    │    │                        │    │   │    │    │    │
       └────┴────┴────┴────────────────────────┴────┴───┴────┴────┴────┘
*/
    /*  Row:      0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15        16       */
    [_BASE] = { { KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXX,     XXX,  	  XXX,  	XXX},
                { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, XXX,   	  KC_HOME,  KC_PGUP},
                { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,   KC_END,   KC_PGDN},
                { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXX,     KC_ENT,  XXX,      XXX,      XXX},
                { KC_LSFT, XXX,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXX,     KC_RSFT, XXX,      KC_UP,    XXX},
                { KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, MO(_FL), XXX,  	 XXX,     KC_RCTL, XXX,     XXX,     XXX,     XXX,     XXX,     KC_LEFT,  KC_DOWN,  KC_RIGHT}
              },

/*
       ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
       │ Esc │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Fn │ Del │
       │───────────────────────────────────────────────────────────────│
       │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Hom│
       │───────────────────────────────────────────────────────────────│
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │PgU│
       │───────────────────────────────────────────────────────────────│
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │  Enter │PgD│
       │───────────────────────────────────────────────────────────────│
       │ LShift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │RSft│ ↑  │ End│
       │───────────────────────────────────────────────────────────────│
       │LCrl│    │LAlt│         Space          │RAlt│RCl│ ←  │ ↓  │ →  │
       └────┴────┴────┴────────────────────────┴────┴───┴────┴────┴────┘
*/
    /*  Row:      0        1        2        3        4        5        6        7        8        9        10       11       12       13       14        15        16       */
    [_GAME] = { { KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXX,     XXX,  	  XXX,  	XXX},
                { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, XXX,   	  KC_HOME,  KC_PGUP},
                { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,   KC_END,   KC_PGDN},
                { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXX,     KC_ENT,  XXX,      XXX,      XXX},
                { KC_LSFT, XXX,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXX,     KC_RSFT, XXX,      KC_UP,    XXX},
                { KC_LCTL, XXX, 	KC_LALT, KC_SPC,  KC_RALT, MO(_CL), XXX,  	 XXX,     KC_RCTL, XXX,     XXX,     XXX,     XXX,     XXX,     KC_LEFT,  KC_DOWN,  KC_RIGHT}
              },

/*
       ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
       │RESET│Mut│MeP│Ply│VoD│VoU│Hom│Mai│Mod│Rod│Tog│Hui│Hud│Fn │ Ins │
       │───────────────────────────────────────────────────────────────│
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │Pau│
       │───────────────────────────────────────────────────────────────│
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
       │───────────────────────────────────────────────────────────────│
       │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
       │───────────────────────────────────────────────────────────────│
       │        │   │   │   │   │   │   │   │   │   │   │    │Vai │PrSc│
       │───────────────────────────────────────────────────────────────│
       │    │GAME│    │                        │    │   │Spd │Vad │Spi │
       └────┴────┴────┴────────────────────────┴────┴───┴────┴────┴────┘
*/
    /*  Row:      0        1        2        3        4        5        6        7        8        9         10       11       12       13       14        15        16      */
    [_FL] =   { { RESET,   KC_MUTE, KC_MSEL, KC_MPLY, KC_VOLD, KC_VOLU, KC_WHOM, KC_MAIL, RGB_MOD, RGB_RMOD, RGB_TOG, RGB_HUI, RGB_HUD, XXX,     XXX,  	   XXX, 	 XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     XXX,  	   KC_PAUSE, XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     KC_INS,   KC_PSCR,  XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     XXX,      XXX,      XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     XXX,      RGB_VAI,  XXX},
                { XXX,     GAME,    XXX,     XXX,     XXX,     MO(_FL), XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     RGB_SPD,  RGB_VAD,  RGB_SPI}
              },

/*
       ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
       │RESET│Mut│MeP│Ply│VoD│VoU│Hom│Mai│Mod│Rod│Tog│Hui│Hud│Fn │ Ins │
       │───────────────────────────────────────────────────────────────│
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │Pau│
       │───────────────────────────────────────────────────────────────│
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
       │───────────────────────────────────────────────────────────────│
       │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
       │───────────────────────────────────────────────────────────────│
       │        │   │   │   │   │   │   │   │   │   │   │    │Vai │PrSc│
       │───────────────────────────────────────────────────────────────│
       │    │BASE│    │                        │    │   │Spd │Vad │Spi │
       └────┴────┴────┴────────────────────────┴────┴───┴────┴────┴────┘
*/
    /*  Row:      0        1        2        3        4        5        6        7        8        9         10       11       12       13       14        15        16      */
    [_CL] =   { { RESET,   KC_MUTE, KC_MSEL, KC_MPLY, KC_VOLD, KC_VOLU, KC_WHOM, KC_MAIL, RGB_MOD, RGB_RMOD, RGB_TOG, RGB_HUI, RGB_HUD, XXX,     XXX,  	   XXX, 	 XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     XXX,  	   KC_PAUSE, XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     KC_INS,   KC_PSCR,  XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     XXX,      XXX,      XXX},
                { XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     XXX,      RGB_VAI,  XXX},
                { XXX,     BASE,    XXX,     XXX,     XXX,     MO(_CL), XXX,     XXX,     XXX,     XXX,      XXX,     XXX,     XXX,     XXX,     RGB_SPD,  RGB_VAD,  RGB_SPI}
              }
};

// Taken from 'g_led_config' in config_led.c
#define CAPS_LOCK_LED_ID 34

void rgb_matrix_indicators_user(void) {
    if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(CAPS_LOCK_LED_ID, 0xFF, 0x00, 0x00);
    } else {
        rgb_matrix_set_color(CAPS_LOCK_LED_ID, 0x00, 0x00, 0x00);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_BASE);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
		writePinLow(D6);
      }
      return false;
      break;
  }
  return true;
}