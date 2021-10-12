/* Copyright 2018 Carlos Filoteo
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
#ifdef LED_ENABLE
  #include "protocol/serial.h"

#endif

#include "keymap_norwegian.h"

#define LT3_TAB LT(3, KC_TAB)
#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)
#define CTRADEL LALT(LCTL(KC_DEL))
#define ALTTAB  LALT(KC_TAB)

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
    LED_CHG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer - L0
   * ,-------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * |Tab/L3|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  '  |Ent/RS|
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  Up |  L4 |
   * |-------------------------------------------------------------------------+
   * | Ctrl| Gui |  L4 | Alt |  L2  |   Space   |  L1  | Ctrl| Left| Down|Right|
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Base - L0 */
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  LT3_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NO_QUOT, MT_RSFT_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,  MO(4),
  KC_LCTL, KC_LGUI, MO(4), KC_LALT,  MO(2),      KC_SPC,        MO(1),  KC_RCTL, KC_LEFT, KC_DOWN,   KC_RGHT
),

  /* FN Layer 1
   * ,-------------------------------------------------------------------------.
   * |  |  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |     |  +  |  =  |  *  |  /   |
   * |-------------------------------------------------------------------------+
   * |       |     |     |     |     |     |     |     |  -  |  _  | PgUp|     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |Capsl|      |          |       |     | Home| PgDn| End |
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Right modifier - L1 */
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELETE,
  _______, _______, _______, _______, _______, _______, _______, _______, NO_PLUS,  NO_EQL, NO_ASTR, NO_SLSH,
  _______, _______, _______, _______, _______, _______, _______, _______,  NO_MINS,  NO_UNDS,  KC_PGUP, _______,
  _______, _______, _______, KC_CAPS, _______,     _______,      _______, _______, KC_HOME, KC_PGDN, KC_END
),

  /* FN Layer 2
   * ,-------------------------------------------------------------------------.
   * |  §  |  !  |  "  |  #  |  ¤  |  %  |  &  |  /  |  =  |  +  |  \  | Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |  ?  |  {  |  [  |  (  |  )  |  ]  |  }  | F10 | F11 |  F12 |
   * |-------------------------------------------------------------------------+
   * |       | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | PgUp|     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |Capsl|      |          |       |     | Home| PgDn| End |
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Left modifier - L2 */
  NO_SECT, KC_EXCLAIM,  NO_DQUO, KC_HASH,  NO_CURR,  KC_PERCENT, NO_AMPR, NO_SLSH, NO_EQL, NO_PLUS, NO_BSLS, KC_DELETE,
  _______, _______, NO_QUES, NO_LCBR, NO_LBRC, NO_LPRN, NO_RPRN, NO_RBRC, NO_RCBR, KC_F10, KC_F11, KC_F12,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_PGUP,  _______,
  _______, _______, _______, KC_CAPS, _______,     _______,      _______, _______, KC_HOME, KC_PGDN, KC_END
),

  /* FN Layer 3
   * ,-------------------------------------------------------------------------.
   * | Esc | Calc|Webhm| Comp|Webrf|     |     |     |     |     |PrtSc|CtrAlDl|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |VolDn|VolUp|     |     |      |
   * |-------------------------------------------------------------------------+
   * |       |LEDtg|LEDch|     |     |RESET|     | Mute|     |MouB1|MousU|MouB2|
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       |     |MousL|MousD|MousR|
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Hold Tab down - L3 */
  KC_ESC,  KC_CALC, KC_WHOM, KC_MYCM, KC_WREF, _______, _______, _______, _______, _______, KC_PSCR, CTRADEL,
  _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______, _______, _______,
  _______, LED_TOG, LED_CHG, _______, _______,   RESET, _______, KC_MUTE, _______, KC_MS_BTN1, KC_MS_U, KC_MS_BTN2,
  _______, _______, _______, _______, _______,     _______,      _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
),

  /* FN Layer 4
   * ,-------------------------------------------------------------------------.
   * |     |     |  @  |  £  |  $  |  ~  |     |  ¨  |  ´  |  `  |  Å  |       |
   * |-------------------------------------------------------------------------+
   * |      |     |     |  €  |     |     |     |     |  ^  |  Ø  |  Æ  |      |
   * |-------------------------------------------------------------------------+
   * |       |  <  |     |     |     |     |     |  µ  |     |     |     |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       | L5  |     |     |     |
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Norsk - L4 */
  _______, _______,   NO_AT,  NO_PND,  NO_DLR, NO_TILD, _______, NO_QUOT, NO_ACUT,  NO_GRV, NO_ARNG, _______,
  _______, _______, _______, NO_EURO, _______, _______, _______, _______, NO_CIRC, NO_OSTR,   NO_AE, _______,
  _______, NO_LABK, _______, _______, _______, _______, _______, NO_MICR, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,     _______,      _______,   TO(5), _______, _______, _______
),

  /* GAMING Layer (toggle on and off)
   * ,-------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  E  |  R  |  T  |  Y  |  F1 |  F2 |  F3 |  F4 |Alt+Tab|
   * |-------------------------------------------------------------------------+
   * | Tab  |  A  |  S  |  D  |  F  |  G  |  H  |  F5 |  F6 |  F7 |  F8 | Enter|
   * |-------------------------------------------------------------------------+
   * | Shift |  1  |  2  |  3  |  4  |  5  |  6  |  F9 | F10 | F11 | Up  |TOGGL|
   * |-------------------------------------------------------------------------+
   * | Ctrl|  Z  |  X  |  C  |   B  |   Space   |   M  |  V  |Left |Down |Right|
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* GAMING, toggled on and off - L5 */
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_F1,    KC_F2,    KC_F3,    KC_F4, ALTTAB,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_F5,    KC_F6,    KC_F7,    KC_F8,  KC_ENT,
  KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_F9,   KC_F10,   KC_F11,    KC_UP,   TO(0),
  KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_B,      KC_SPC,          KC_M,     KC_V,  KC_LEFT,  KC_DOWN, KC_RGHT
),
};

//LED keymap functions
 #ifdef LED_ENABLE
void led_chmode(void) {
  serial_send(101);
}

void led_toggle(void) {
  serial_send(100);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case LED_TOG:
        #ifdef LED_ENABLE
        led_toggle();
        #endif
        return false;
      case LED_CHG:
        #ifdef LED_ENABLE
        led_chmode();
        #endif
        return false;
    }
  }
  return true;
};
#endif
