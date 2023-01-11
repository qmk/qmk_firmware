/* Copyright 2018 Daniel Rose <droseger@protonmail.com>
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

/* Allow shortcuts for combos like RALT(KC_RBRC) that don't take up more than 7 characters: */
/* Original shortcuts (quantum_keycodes.h) take full-sized keycodes: too long! */
#undef C
#undef S
#undef A
#undef G
#define C(kc) LCTL(KC_##kc)
#define S(kc) LSFT(KC_##kc)
#define A(kc) LALT(KC_##kc)
#define G(kc) RALT(KC_##kc)
#define CTALDEL LCTL(LALT(KC_DEL))

enum layers {
  DEF,
  FUN,
  RES,
};

enum tap_dance {
  AF4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: default layer (ISO-DE)
 * .----.   .-------------------. .-------------------. .-------------------. .--------------.
 * |Esc |   |F1  |F2  |F3  |F4  | |F5  |F6  |F7  |F8  | |F9  |F10 |F11 |F12 | |PrSc|SLck|2Tp:|
 * |    |   |    |    |    |    | |    |    |    |    | |    |    |    |    | |SyRq|    |A+F4|
 * '----'   '-------------------' '-------------------' '-------------------' '--------------'
 * .------------------------------------------------------------------------. .--------------.
 * |°   |!   |"   |§   |$   |%   |&   |/   |(   |)   |=   |?   |`   |Backspa| |Ins |Home|PgUp|
 * |^   |1   |2  ²|3  ³|4   |5   |6   |7  {|8  [|9  ]|0  }|ß  \|´   |       | |    |    |    |
 * |------------------------------------------------------------------------| |--------------|
 * |Tab   |Q   |W   |E   |R   |T   |Z   |U   |I   |O   |P   |Ü   |*   |  E  | |Del |End |PgDn|
 * |      |    |    |   €|    |    |    |    |    |    |    |    |+  ~|  n  | |    |    |    |
 * |------------------------------------------------------------------\  t  | '--------------'
 * |Fn:    |A   |S   |D   |F   |G   |H   |J   |K   |L   |Ö   |Ä   |'   | e  |
 * |Layer 2|    |    |    |    |    |    |    |    |    |    |    |#   | r  |
 * |------------------------------------------------------------------------|      .----.
 * |Shift|>   |Y   |X   |C   |V   |B   |N   |M   |;   |:   |_   |Shift      |      |Up  |
 * |     |<  ¦|    |    |    |    |    |    |   µ|,   |.   |-   |           |      |    |
 * |------------------------------------------------------------------------| .--------------.
 * |Ctrl |Super|Alt  |                              |AltGr|Alt  |Fn:  |Ctrl | |Left|Down|Righ|
 * |     |     |     |                              |     |     |Lay 2|     | |    |    |    |
 * '------------------------------------------------------------------------' '--------------'
 *                                                                                                  NUHS = true position of KC_NUHS
 */
[DEF] = LAYOUT( \
  KC_ESC,         KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,   KC_PSCR,KC_SCRL,TD(AF4), \
  KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,  KC_INS, KC_HOME,KC_PGUP, \
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_NUHS,  KC_DEL, KC_END, KC_PGDN, \
  MO(FUN),KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,/*NUHS*/KC_ENT,                            \
  KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        KC_RSFT,          KC_UP,           \
  KC_LCTL,KC_LGUI,KC_LALT,                        KC_SPC,                         KC_RALT,KC_LALT,MO(FUN),KC_RCTL,  KC_LEFT,KC_DOWN,KC_RGHT),

    /* Layer 1: function layer
 * .----.   .-------------------. .-------------------. .-------------------. .--------------.
 * |Ctl+|   |My  |WWW:|Calc|Medi| |Mus:|Mus:|Mus:|Mus:| |Vol:|Vol:|Vol:|See:| |    |    |Paus|
 * |A+De|   |Comp|Home|    |Play| |Prev|Next|Paus|Stop| |Mute|Down|Up  |[3] | |    |    |Brea|
 * '----'   '-------------------' '-------------------' '-------------------' '--------------'
 * .------------------------------------------------------------------------. .--------------.
 * |    |    |    |    |    |    |    |    |    |    |    |    |    |       | |    |    |Mou:|
 * |    |    |    |    |    |    |    |{   |[   |]   |}   |\   |    |       | |    |    |WhUp|
 * |------------------------------------------------------------------------| |--------------|
 * |      |    |    |    |    |    |    |    |    |    |    |    |~   |     | |    |    |Mou:|
 * |      |    |    |    |    |    |    |    |    |    |    |    |    |     | |    |    |WhDn|
 * |------------------------------------------------------------------\     | '--------------'
 * |CapsLck|Mou:|Mou:|    |    |    |    |    |    |    |    |    |    |    |
 * |       |Fast|Slow|    |    |    |    |    |    |    |    |    |    |    |
 * |------------------------------------------------------------------------|      .----.
 * |     |    |    |    |    |    |    |    |µ   |    |    |    |           |      |Mou:|
 * |     |    |    |    |    |    |    |    |    |    |    |    |           |      |Up  |
 * |------------------------------------------------------------------------| .--------------.
 * |Mous:|Mous:|     |                              |     |Super|App  |     | |Mou:|Mou:|Mou:|
 * |Bttn2|Bttn1|     |                              |     |     |     |     | |Left|Down|Righ|
 * '------------------------------------------------------------------------' '--------------'
 *
 */
[FUN] = LAYOUT( \
  CTALDEL,        KC_MYCM,KC_WHOM,KC_CALC,KC_MSEL,KC_MPRV,KC_MNXT,KC_MPLY,KC_MSTP,KC_MUTE,KC_VOLD,KC_VOLU,MO(RES),  _______,KC_SCRL,KC_PAUS, \
  _______,_______,_______,_______,_______,_______,_______,G(7),   G(8),   G(9),   G(0),   G(MINS),_______,_______,  _______,_______,KC_WH_U, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,G(RBRC),_______,  _______,_______,KC_WH_D, \
  KC_CAPS,KC_ACL2,KC_ACL0,_______,_______,_______,_______,_______,_______,_______,_______,_______,/*NUHS*/_______,                           \
  _______,_______,_______,_______,_______,_______,_______,_______,G(M),   _______,_______,_______,        _______,          KC_MS_U,         \
  KC_BTN2,KC_BTN1,_______,                        _______,                        _______,KC_RGUI,KC_APP ,_______,   KC_MS_L,KC_MS_D,KC_MS_R),


/* Layer 3: Reset layer (prevents accidental resets) */
[RES] = LAYOUT( \
  _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,  _______,_______,_______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,  _______,_______,_______, \
  _______,_______,_______,_______,QK_BOOT,  _______,_______,_______,_______,_______,_______,_______,_______,_______,  _______,_______,_______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,/*NUHS*/_______,                           \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,          _______,         \
  _______,_______,_______,                        _______,                        _______,_______,_______,_______,  _______,_______,_______),
};

qk_tap_dance_action_t tap_dance_actions[] = {
  /* Tap once: nothing. Tap twice: Alt+F4 */
  [AF4]  = ACTION_TAP_DANCE_DOUBLE(XXXXXXX,A(F4)),
};

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    ph_caps_led_on();
  } else {
    ph_caps_led_off();
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    ph_sclk_led_on();
    } else {
    ph_sclk_led_off();
  }
}
