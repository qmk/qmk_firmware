/* Copyright 2021 n2
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
#include QMK_KEYBOARD_H
#include "keymap_jp.h"

#define RAISE FN_MO13
#define LOWER FN_MO23

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _DEFAULT = 0,
    _RAISE,
    _LOWER,
    _ADJUST
/*    _FN */
};

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
  if (!is_keyboard_master()) {
      render_logo();
  } else {
      // Host Keyboard Layer Status
      oled_write_P(PSTR("Layer: "), false);
      switch (get_highest_layer(layer_state)) {
          case _DEFAULT:
              oled_write_P(PSTR("DEFAULT\n"), false);
              break;
          case _RAISE:
              oled_write_P(PSTR("RAISE\n"), false);
              break;
          case _LOWER:
              oled_write_P(PSTR("LOWER\n"), false);
          break;
          case _ADJUST:
              oled_write_P(PSTR("ADJUST\n"), false);
          break;
          default:
              // Or use the write_ln shortcut over adding '\n' to the end of your string
          oled_write_ln_P(PSTR("Undefined"), false);
      };
      // Host Keyboard LED Status
      led_t led_state = host_keyboard_led_state();
      oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
      oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
      oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK\n") : PSTR("      \n"), false);
    }
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* DEFAULT
    * ,--------------------------------------------------------------------------------------------------------------------------------------.
    * |ZEN/HAN |   1    |   2    |   3    |   4    |   5    |        |   6    |   7    |   8    |   9    |   0    |   -    |   ^    |   \    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * | TAB    |   q    |   w    |   e    |   r    |   t    |        |   y    |   u    |   i    |   o    |   p    |   @    |   [    | BSPC   |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * | CAPS   |   a    |   s    |   d    |   f    |   g    |        |   h    |   j    |   k    |   l    |   ;    |   :    |   ]    | ENT    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * | LSHIFT |   z    |   x    |   c    |   v    |   b    |        |   n    |   m    |   ,    |   .    |   /    |   \    |  UP    | RSHIFT |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * | CTRL   | LGUI   | ALT    | MUHEN  | SPACE  | SPACE  | LOWER  | RAISE  | SPACE  | HENKAN | KANA   | APP    | LEFT   | DOWN   | RIGHT  |
    * `--------------------------------------------------------------------------------------------------------------------------------------'
    */
    [_DEFAULT] = LAYOUT(
      KC_ZKHK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   _______,    KC_6,       KC_7,   KC_8,    KC_9,    KC_0,    JP_MINS, JP_CIRC, JP_YEN,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   _______,    KC_Y,       KC_U,   KC_I,    KC_O,    KC_P,    JP_AT  , JP_LBRC, KC_BSPC,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   _______,    KC_H,       KC_J,   KC_K,    KC_L,    KC_SCLN, JP_COLN, JP_RBRC, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   _______,    KC_N,       KC_M,   KC_COMM, KC_DOT,  KC_SLSH, JP_BSLS, KC_UP,   KC_RSFT,
      KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN, KC_SPC,  KC_SPC, FN_MO23,    FN_MO13,    KC_SPC, KC_HENK, KC_KANA, KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT
    ),
   /* RAISE
    * ,--------------------------------------------------------------------------------------------------------------------------------------.
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |   1    |   2    |   3    |   4    |   5    |        |   6    |   7    |   8    |   9    |   0    |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * `--------------------------------------------------------------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
   /* LOWER
    * ,--------------------------------------------------------------------------------------------------------------------------------------.
    * |        |        |        |        |        |        |RGB_TOG |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |RGB_VAI |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |RGB_HUI |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |RGB_SAI |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * `--------------------------------------------------------------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT(
      _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
   /* ADJUST
    * ,--------------------------------------------------------------------------------------------------------------------------------------.
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    * `--------------------------------------------------------------------------------------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left side encoder */
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    } else if (index == 1) { /* Right side encoder */
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
    return true;
}
