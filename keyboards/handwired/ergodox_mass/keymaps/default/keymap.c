/* Copyright 2018 Andrew Mass
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

// Mousekey Settings
#define MOUSEKEY_DELAY             100
#define MOUSEKEY_INTERVAL          50
#define MOUSEKEY_MAX_SPEED         10
#define MOUSEKEY_TIME_TO_MAX       10
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

/**
 * Misc Info
 *
 * - KC_NO for noop
 * - KC_TRNS for transparent (go to lower layer)
 * - *LAYER*: Momentary
 * - ^LAYER^: Toggle
 */

// Layers
#define BASE 0
#define SYMB 1
#define NAVG 2

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
   NUMHOLD = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |^SYMB^|           |^NAVG^|   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * |--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------|
 * |        |      |      |*NAVG*|*SYMB*|                                       |*SYMB*|*NAVG*|      |      |        |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Del | Ins  |       |  GUI | Esc  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       |  Alt |      |      |
 *                                 | Space| Back |------|       |------| Cntl |Enter |
 *                                 |      |      | End  |       |  Tab |      |      |
 *                          ,------+------+-------------|       |--------------------+------.
 *                          |  Swap Side  |   Numhold   |       |   Numhold   |  Swap Side  |
 *                          `---------------------------'       `---------------------------'
 */
[BASE] = LAYOUT (
  KC_GRV,         KC_1,         KC_2,   KC_3,    KC_4,   KC_5,   KC_NO,
  KC_NO,          KC_Q,         KC_W,   KC_E,    KC_R,   KC_T,   TG(SYMB),
  KC_NO,          KC_A,         KC_S,   KC_D,    KC_F,   KC_G,
  KC_LSFT,        KC_Z,         KC_X,   KC_C,    KC_V,   KC_B,   KC_NO,
  KC_NO,          KC_NO,        KC_NO,  MO(NAVG),MO(SYMB),

                                                 KC_DELT,KC_INS,
                                                         KC_HOME,
                                        KC_SPC,  KC_BSPC,KC_END,
                                        SH_MON,          NUMHOLD,

 KC_NO,       KC_6,   KC_7,    KC_8,    KC_9,   KC_0,             KC_MINS,
 TG(NAVG),    KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,             KC_BSLS,
              KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN,          KC_QUOT,
 KC_NO,       KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT,
                      MO(SYMB),MO(NAVG),KC_NO,  KC_NO,            KC_NO,

 KC_LGUI,        KC_ESC,
 KC_LALT,
 KC_TAB,KC_RCTL, KC_ENT,
 NUMHOLD,        SH_MON
),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |   <  |   >  |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    +   |      |      |   {  |   }  |      |^SYMB^|           |^NAVG^|   7  |   8  |   9  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    =   |      |      |   (  |   )  |      |------|           |------|   4  |   5  |   6  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |      |      |   [  |   ]  |      |      |           |   0  |   1  |   2  |   3  |      |      | RShift |
 * |--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------|
 * |        |      |      |*NAVG*|*SYMB*|                                       |*SYMB*|*NAVG*|      |      |        |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Del | Ins  |       |  GUI | Esc  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       |  Alt |      |      |
 *                                 | Space| Back |------|       |------| Cntl |Enter |
 *                                 |      |      | End  |       |  Tab |      |      |
 *                          ,------+------+-------------|       |--------------------+------.
 *                          |  Swap Side  |   Numhold   |       |   Numhold   |  Swap Side  |
 *                          `---------------------------'       `---------------------------'
 */

[SYMB] = LAYOUT (
  KC_NO,   KC_NO,   KC_NO,   KC_LABK, KC_RABK, KC_NO,   KC_NO,
  KC_PLUS, KC_NO,   KC_NO,   KC_LCBR, KC_RCBR, KC_NO,   KC_TRNS,
  KC_EQL,  KC_NO,   KC_NO,   KC_LPRN, KC_RPRN, KC_NO,
  KC_TRNS, KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_NO,   KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,

                                      KC_TRNS, KC_TRNS,
                                               KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,
                             KC_TRNS,          KC_TRNS,

  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_TRNS, KC_7,    KC_8,    KC_9,    KC_NO,   KC_NO,   KC_NO,
           KC_4,    KC_5,    KC_6,    KC_NO,   KC_NO,   KC_NO,
  KC_0,    KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,   KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_NO,

  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,          KC_TRNS
),

/* Keymap 2: Navigation & Media Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Vol Up |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Vol Dn |      |MSE LC|MSE MC|MSE RC|      |^SYMB^|           |^NAVG^|      |MSE WD|MSE WU|      |      |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Vol Mute|      |MSE LF|MSE DN|MSE UP|MSE RT|------|           |------| LEFT | DOWN |  UP  | RGHT |MSE A0| MSE A1 |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |MSE BC|MSE FC|      |      |           |      |      | PgDn | PgUp |      |      | MSE A2 |
 * |--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------|
 * |  Play  | Prev | Next |*NAVG*|*SYMB*|                                       |*SYMB*|*NAVG*|      |      |        |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Del | Ins  |       |  GUI | Esc  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       |  Alt |      |      |
 *                                 | Space| Back |------|       |------| Cntl |Enter |
 *                                 |      |      | End  |       |  Tab |      |      |
 *                          ,------+------+-------------|       |--------------------+------.
 *                          |  Swap Side  |   Numhold   |       |   Numhold   |  Swap Side  |
 *                          `---------------------------'       `---------------------------'
 */

[NAVG] = LAYOUT (
  KC_VOLU, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,
  KC_VOLD, KC_NO,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NO,   KC_TRNS,
  KC_MUTE, KC_NO,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
  KC_NO,   KC_NO,   KC_NO,   KC_BTN4, KC_BTN5, KC_NO,   KC_NO,
  KC_MPLY ,KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,

                                      KC_TRNS, KC_TRNS,
                                               KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,
                             KC_TRNS,          KC_TRNS,

  KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_NO,   KC_WH_D, KC_WH_U, KC_NO,   KC_NO,   KC_F12,
           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ACL0, KC_ACL1,
  KC_NO,   KC_NO,   KC_PGDN, KC_PGUP, KC_NO,   KC_NO,   KC_ACL2,
                    KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_NO,

  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,          KC_TRNS
),

};

void matrix_init_user(void) {
  // Ensure NUMLOCK is OFF at startup
  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))
    tap_code(KC_NUMLOCK);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUMHOLD:
      // This function is called twice per keystroke, pressed & released. Turn
      // on NUMLOCK on press, then turn it off on release.
      tap_code(KC_NUMLOCK);
      return false; // Skip all further processing
  }
  return true;
}

/* Keymap x: Empty Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |^SYMB^|           |^NAVG^|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------|
 * |        |      |      |*NAVG*|*SYMB*|                                       |*SYMB*|*NAVG*|      |      |        |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Del | Ins  |       |  GUI | Esc  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       |  Alt |      |      |
 *                                 | Space| Back |------|       |------| Cntl |Enter |
 *                                 |      |      | End  |       |  Tab |      |      |
 *                          ,------+------+-------------|       |--------------------+------.
 *                          |  Swap Side  |   Numhold   |       |   Numhold   |  Swap Side  |
 *                          `---------------------------'       `---------------------------'
 */

/*
[    ] = LAYOUT (
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,

                                      KC_TRNS, KC_TRNS,
                                               KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,
                             KC_TRNS,          KC_TRNS,

  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                    KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_NO,

  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,          KC_TRNS
),
*/
