/* Copyright 2019
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
#include <print.h>

enum layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NAV,
  _VIM,
  _MOUSE,
  _MEDIA,
};

signed int fwdCounter = 0;
signed int bwdCounter = 0;

//Layers
#define LOWER    MO(_LOWER)
#define RAISE    MO(_RAISE)
#define ADJUST   MO(_ADJUST)
#define QWERTY   TG(_QWERTY)
#define MOUSE    TG(_MOUSE)
#define MEDIA    TG(_MEDIA)
#define VIM      LT(_VIM, KC_TAB)
#define NAV      LT(_NAV, KC_SPC)

//Mods
#define CTL_ESC  LCTL_T(KC_ESC)
#define ALGR_DN  ALGR_T(KC_DOWN)
#define SHFT_ENT MT(KC_LSFT, KC_ENT)
#define PRV_PLY  MT(KC_MPRV, KC_MPLY)
#define NXT_PLY  MT(KC_MNXT, KC_MPLY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |VimTab|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CrEsc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |  C   |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Media| Alt  | GUI  |Lower | Space|Space | Space|Space |Raise | Down |  Up  |Mute  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  VIM,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHFT_ENT , \
  MEDIA,   KC_LGUI, KC_LALT, LOWER,   NAV,     NAV,     NAV,     NAV,     RAISE,   ALGR_DN, KC_UP,   KC_MUTE \
),

/* Vim
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CrEsc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |  C   |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |Lower | Space|Space | Space|Space |Raise |  F3  | CrP  |   *  |
 * `-----------------------------------------------------------------------------------'
 */
[_VIM] = LAYOUT_ortho_4x12( \
  KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,         KC_BSPC, \
  LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,      KC_QUOT, \
  KC_LSFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,      KC_ENT , \
  KC_LCTL,        KC_LGUI, KC_LALT, LOWER,   NAV,     NAV,     NAV,     NAV,     RAISE,   KC_F3,   LCTL_T(KC_P), KC_ASTR \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |     |    \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |     Del     |     Bksp    |      | LEFT | RIGHT| Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,  BL_TOGG, BL_INC , BL_DEC , _______, _______, \
  _______, _______, _______, _______, KC_DEL, KC_DEL,  KC_BSPC, KC_BSPC, _______, KC_LEFT, KC_RGHT, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | LEFT | RIGHT| Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______, KC_DEL,  KC_DEL,  KC_BSPC, KC_BSPC, _______, KC_LEFT, KC_RGHT, KC_MPLY \
),

/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  UP  |      |      |      |      |      | INS  |      |PRTSCR|  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | LEFT | DOWN | RIGHT|      |      |      |      |      |      | PGUP |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | HOME | END  | PGDN |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] =  LAYOUT_ortho_4x12( \
  _______, _______, KC_UP,   _______, _______, _______, _______, _______, KC_INS,  _______, KC_PSCR, KC_DEL, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,  KC_END, KC_PGDN, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LGUI(KC_TAB) \
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |WhLeft| MoUP |WhRgth|      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |MoLEFT|MoDOWN|MoRGHT|      |      |      |      |      |      | PGUP |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | HOME | END  | PGDN |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ACL0 | ACL1 | ACL2 |      | BTN1 | BTN1 | BTN2 | BTN2 |      |      |      | BTN3 |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] =  LAYOUT_ortho_4x12( \
  MOUSE,   KC_WH_L, KC_MS_U, KC_WH_R, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,  KC_END, KC_PGDN, _______,\
  KC_ACL0, KC_ACL1, KC_ACL2, _______, KC_BTN1, KC_BTN1, KC_BTN2, KC_BTN2, _______, _______, _______, KC_BTN3 \
),

/* Media
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  UP  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | LEFT | DOWN | RIGHT|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Mute | VolDn| VolUp| Prev | Next | Stop |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | PrPly| PrPly| NxPly| NxPly|      |      |      | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] =  LAYOUT_ortho_4x12( \
  _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,\
  _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, KC_MSTP, _______, _______, _______, _______, _______,\
  MEDIA, _______, _______, _______, PRV_PLY, PRV_PLY, NXT_PLY, NXT_PLY, _______, _______, _______, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |QWERTY|  VIM |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |RGBtog|RGBmod|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | BLtog| BLinc| BLdec|      |      |      |      |      |BrigDn|BrigUp|      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  EEP_RST, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
  _______, _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______,\
  _______, BL_TOGG, BL_INC,  BL_DEC , _______, _______, _______, _______, _______, KC_BRID, KC_BRIU, MOUSE \
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  fwdCounter = 0;
  bwdCounter = 0;

  #ifdef CONSOLE_ENABLE
    uprintf("layer_state: %u\n", biton32(layer_state));
  #endif 
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {

  switch (biton32(layer_state)) {
    case 6:
      if (clockwise) {
        tap_code(KC_WH_U);
      } else {
        tap_code(KC_WH_D);
      }
      break;
    case 5:
      if (clockwise) {
        tap_code(KC_0);
        tap_code(KC_5);
        tap_code(KC_J);
      } else {
        tap_code(KC_0);
        tap_code(KC_5);
        tap_code(KC_K);
      }
      break;
    case 4:
      if (clockwise) {
        tap_code(KC_WH_U);
      } else {
        tap_code(KC_WH_D);
      }
      break;
    case 3:
      if (clockwise) {
        if (bwdCounter > 0) {
          switch (bwdCounter) {
            case 1:
              tap_code(KC_1);
              break;
            case 2:
              tap_code(KC_2);
              break;
            case 3:
              tap_code(KC_3);
              break;
            case 4:
              tap_code(KC_4);
              break;
            case 5:
              tap_code(KC_5);
              break;
            case 6:
              tap_code(KC_6);
              break;
            case 7:
              tap_code(KC_7);
              break;
            case 8:
              tap_code(KC_8);
              break;
            case 9:
              tap_code(KC_9);
              break;
          }
          bwdCounter = 0;
        }
        fwdCounter++;
      } else {
        if (fwdCounter > 0) {
          switch (fwdCounter) {
            case 1:
              tap_code(KC_1);
              break;
            case 2:
              tap_code(KC_2);
              break;
            case 3:
              tap_code(KC_3);
              break;
            case 4:
              tap_code(KC_4);
              break;
            case 5:
              tap_code(KC_5);
              break;
            case 6:
              tap_code(KC_6);
              break;
            case 7:
              tap_code(KC_7);
              break;
            case 8:
              tap_code(KC_8);
              break;
            case 9:
              tap_code(KC_9);
              break;
          }
          fwdCounter = 0;
        }
        bwdCounter++;
      }
      break;
    case 2:
      if (clockwise) {
        register_code(KC_LCTL);
        tap_code(KC_EQL);
        unregister_code(KC_LCTL);
      } else {
        register_code(KC_LCTL);
        tap_code(KC_MINS);
        unregister_code(KC_LCTL);
      }
      break;
    case 1:
      if (clockwise) {
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_RGHT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
      } else {
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        tap_code(KC_LEFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
      }
      break;
    default:
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
      break;
  }
}
