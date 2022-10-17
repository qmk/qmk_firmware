// qmk flash -kb bm40hsrgb -km signynt

/* Copyright 2021 Vincenzo Mitchell Barroso
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

// non-KC_ keycodes
#define KC_RST QK_BOOT
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI

//define layers
enum layers {BASE, MEDR, NAVR, NSSL, NSL, FUNL, GAME, SECGAME};

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
};

//cmd tab

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LCTL);
        }
        cmd_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 500) {
      unregister_code(KC_LCTL);
      is_cmd_tab_active = false;
    }
  }
}

//layer led colors

bool rgb_matrix_indicators_user(void) {

//game indicators

if(IS_LAYER_ON(GAME)) {
  rgb_matrix_set_color(11, 0, 40, 50);
}

if(IS_LAYER_ON(SECGAME)) {
  rgb_matrix_set_color(11, 50, 0, 0);
}

//layer indicators

if(IS_LAYER_ON(NAVR)) {
  rgb_matrix_set_color(40, 0, 40, 50);

  rgb_matrix_set_color(19, 0, 40, 50);
  rgb_matrix_set_color(20, 0, 40, 50);
  rgb_matrix_set_color(21, 0, 40, 50);
  rgb_matrix_set_color(22, 0, 40, 50);
}

if(IS_LAYER_ON(MEDR)) {
  rgb_matrix_set_color(39, 50, 10, 20);

  rgb_matrix_set_color(19, 50, 10, 20);

  rgb_matrix_set_color(22, 50, 10, 20);

  rgb_matrix_set_color(42, 50, 10, 20);
}

if(IS_LAYER_ON(FUNL)) {
  rgb_matrix_set_color(43, 50, 0, 0);

  rgb_matrix_set_color(1, 50, 0, 0);
  rgb_matrix_set_color(2, 50, 0, 0);
  rgb_matrix_set_color(3, 50, 0, 0);
  rgb_matrix_set_color(4, 50, 0, 0);

  rgb_matrix_set_color(13, 50, 0, 0);
  rgb_matrix_set_color(14, 50, 0, 0);
  rgb_matrix_set_color(15, 50, 0, 0);
  rgb_matrix_set_color(16, 50, 0, 0);

  rgb_matrix_set_color(25, 50, 0, 0);
  rgb_matrix_set_color(26, 50, 0, 0);
  rgb_matrix_set_color(27, 50, 0, 0);
  rgb_matrix_set_color(28, 50, 0, 0);
}

if(IS_LAYER_ON(NSL)) {
  rgb_matrix_set_color(42, 10, 0, 50);

  rgb_matrix_set_color(2, 10, 0, 50);
  rgb_matrix_set_color(3, 10, 0, 50);
  rgb_matrix_set_color(4, 10, 0, 50);

  rgb_matrix_set_color(14, 10, 0, 50);
  rgb_matrix_set_color(15, 10, 0, 50);
  rgb_matrix_set_color(16, 10, 0, 50);

  rgb_matrix_set_color(26, 10, 0, 50);
  rgb_matrix_set_color(27, 10, 0, 50);
  rgb_matrix_set_color(28, 10, 0, 50);

  rgb_matrix_set_color(38, 10, 0, 50);
  rgb_matrix_set_color(39, 10, 0, 50);
  rgb_matrix_set_color(40, 10, 0, 50);
}

if(IS_LAYER_ON(NSSL)) {
  rgb_matrix_set_color(41, 0, 50, 1.9);

  rgb_matrix_set_color(1, 0, 50, 1.9);
  rgb_matrix_set_color(2, 0, 50, 1.9);
  rgb_matrix_set_color(3, 0, 50, 1.9);
  rgb_matrix_set_color(4, 0, 50, 1.9);
  rgb_matrix_set_color(5, 0, 50, 1.9);

  rgb_matrix_set_color(13, 0, 50, 1.9);
  rgb_matrix_set_color(14, 0, 50, 1.9);
  rgb_matrix_set_color(15, 0, 50, 1.9);
  rgb_matrix_set_color(16, 0, 50, 1.9);
  rgb_matrix_set_color(17, 0, 50, 1.9);

  rgb_matrix_set_color(25, 0, 50, 1.9);
  rgb_matrix_set_color(26, 0, 50, 1.9);
  rgb_matrix_set_color(27, 0, 50, 1.9);
  rgb_matrix_set_color(28, 0, 50, 1.9);
  rgb_matrix_set_color(29, 0, 50, 1.9);

    return false;
}

//capslock leds

if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    rgb_matrix_set_color_all(50, 15.6, 0);
  }

}

//tap dance declarations
enum {
    TD_MEDIA, TD_SCREEN,
};

//tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MEDIA] = ACTION_TAP_DANCE_DOUBLE( KC_MPLY , KC_MNXT ),
    [TD_SCREEN] = ACTION_TAP_DANCE_DOUBLE( (G(S(KC_S))) , S(C(KC_4)) ),
};

#define KC_TD(TD_VARIABLE) TD(TD_VARIABLE)

//--------------------------------------------------------------------------------------------------------

//base

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_planck_mit(
    KC_LALT,              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_LALT,
    KC_LSFT,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_LSFT,
    KC_LCTL,              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    G(KC_TAB),            KC_TD(TD_SCREEN),  KC_ESC,            LT(MEDR, KC_TAB),  LT(NAVR, KC_SPC),      LT(NSSL, KC_ENT),                 LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_LGUI,           KC_TD(TD_MEDIA),     CMD_TAB
  ),

//layers
  [NAVR] = LAYOUT_planck_mit(
    KC_LALT,              KC_RST,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             C(S(KC_Z)),        C(A(KC_LEFT)),     C(KC_X),           C(KC_C),           C(A(KC_RGHT)),     KC_LALT,
    KC_LSFT,              G(S(C(KC_F1))),    G(S(C(KC_F3))),    G(S(C(KC_F4))),     G(S(C(KC_F2))),   KC_NO,             KC_CAPS,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_LSFT,
    KC_LCTL,              KC_NO,             KC_ALGR,           KC_NO,              G(S(C(KC_F5))),   KC_NO,             KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_LCTL,
    TG(GAME),             KC_NO,             KC_NO,             KC_NO,              KC_NO,                     KC_ENT,                      KC_BSPC,           KC_DEL,            KC_NO,             C(G(KC_LEFT)),     C(G(KC_RIGHT))
  ),
  [MEDR] = LAYOUT_planck_mit(
    KC_LALT,              KC_RST,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_TOG,            KC_MOD,            KC_HUI,            KC_SAI,            KC_VAI,            KC_LALT,
    KC_LSFT,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_LSFT,
    KC_LCTL,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_F13,            KC_F14,            KC_F15,            RGB_VAI,           KC_LCTL,
    KC_NO,                KC_NO,             KC_NO,             KC_NO,              KC_NO,                     KC_MSTP,                     KC_MPLY,           KC_MUTE,           KC_NO,             KC_NO,             KC_NO
  ),
  [FUNL] = LAYOUT_planck_mit(
    KC_LALT,              KC_F12,            KC_F7,             KC_F8,              KC_F9,            KC_PSCR,           KC_F15,            KC_NO,             KC_NO,             KC_NO,             KC_RST,            KC_LALT,
    KC_LSFT,              KC_F11,            KC_F4,             KC_F5,              KC_F6,            KC_SCRL,           KC_F14,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LSFT,
    KC_LCTL,              KC_F10,            KC_F1,             KC_F2,              KC_F3,            KC_PAUS,           KC_F13,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LCTL,
    KC_NO,                KC_NO,             KC_TAB,            KC_APP,             KC_SPC,                    KC_UNDS,                     KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [NSL] = LAYOUT_planck_mit(
    KC_LALT,              KC_LPRN,           KC_7,              KC_8,               KC_9,             KC_RPRN,           KC_LBRC,           KC_AMPR,           KC_ASTR,           KC_LCBR,           KC_RBRC,           KC_BSPC,
    KC_LSFT,              KC_COLN,           KC_4,              KC_5,               KC_6,             KC_EQL,            KC_LCBR,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_RCBR,           KC_LSFT,
    KC_LCTL,              KC_GRV,            KC_1,              KC_2,               KC_3,             KC_PLUS,           KC_TILD,           KC_EXLM,           KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    A(S(C(KC_N))),        S(C(KC_5)),        KC_NO,             KC_UNDS,            KC_0,                      KC_MINS,                     KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [NSSL] = LAYOUT_planck_mit(
    KC_LALT,              KC_LCBR,           KC_AMPR,           KC_ASTR,            KC_LPRN,          KC_RCBR,           KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_RST,            KC_BSPC,
    KC_LSFT,              KC_SCLN,           KC_DLR,            KC_PERC,            KC_CIRC,          KC_PLUS,           KC_NO,             KC_MS_L,            KC_MS_D,          KC_MS_U,           KC_MS_R,           KC_LSFT,
    KC_LCTL,              KC_TILD,           KC_EXLM,           KC_AT,              KC_HASH,          KC_PIPE,           KC_NO,             KC_WH_L,            KC_WH_D,          KC_WH_U,           KC_WH_R,           KC_LCTL,
    KC_NO,                KC_NO,             KC_UNDS,           KC_GT,              KC_RPRN,                   KC_NO,                       KC_BTN1,            KC_BTN3,          KC_BTN2,           KC_NO,             KC_NO
  ),
  [GAME] = LAYOUT_planck_mit(
    KC_ESC,               KC_Q,              KC_W,              KC_E,               KC_R,             KC_T,              KC_Y,              KC_U,               KC_I,             KC_O,              KC_P,              TG(GAME),
    KC_LALT,              KC_A,              KC_S,              KC_D,               KC_F,             KC_G,              KC_H,              KC_J,               KC_K,             KC_L,              KC_QUOT,           KC_LSFT,
    KC_LSFT,              KC_Z,              KC_X,              KC_C,               KC_V,             KC_B,              KC_N,              KC_M,               KC_COMM,          KC_DOT,            KC_SLSH,           KC_LCTL,
    KC_LCTL,              A(KC_TAB),         MO(SECGAME),       KC_TAB,             KC_SPC,             LT(SECGAME, KC_ENT),                KC_BSPC,            KC_DEL,           KC_MPRV,           KC_MPLY,           KC_MNXT
  ),
  [SECGAME] = LAYOUT_planck_mit(
    KC_1,                 KC_2,              KC_3,              KC_4,               KC_5,             KC_6,              KC_7,              KC_8,               KC_9,             KC_0,              KC_MINS,           KC_EQL,
    KC_F1,                KC_F2,             KC_F3,             KC_F4,              KC_F5,            KC_F6,             KC_F7,             KC_F8,              KC_F9,            KC_F10,            KC_F11,            KC_F12,
    KC_LEFT,              KC_DOWN,           KC_UP,             KC_RGHT,            KC_NO,            KC_NO,             KC_NO,             KC_P1,              KC_P2,            KC_P3,             KC_P4,             KC_P5,
    KC_LEFT,              KC_DOWN,           KC_UP,             KC_RGHT,            KC_NO,                     KC_NO,                       KC_P6,              KC_P7,            KC_P8,             KC_P9,             KC_P0
  )
};
