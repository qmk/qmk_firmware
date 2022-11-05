/* Copyright 2021 gipsy-king
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

// Raise layer or enter on tap
#define RAISE LT(1, KC_ENT)
// Xmonad layer with LGUI always on
#define MOD4 LM(2, MOD_LGUI)
// Oneshot
#define ONESHOT OSL(3)
// Mic-mute-tap or Fn layer (F20 is mic-mute on thinkpads)
#define FNLAY LT(3, KC_F20)

enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    EMAIL_W,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * .-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Backsp|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   -  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LCTR | LGUI | LALT | MOD4 |  ^(  | Space|Ent/Ra|  ^)  | RALT | MUTE | RGUI | RCTR |
 * '-----------------------------------------------------------------------------------'
 */
[0] = LAYOUT(
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
  KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
  KC_MINS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_EQL,
  KC_LCTL,KC_LALT,KC_LGUI,MOD4,   KC_LSPO,KC_SPC, RAISE,  KC_RSPC,KC_RALT,KC_RGUI,FNLAY,  KC_RCTL
),
/* Raise
 * .-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ~  |   {  | PgUp | PgDn |  End | Home |  <-  |  \/  |  /\  |  ->  |   }  |   |  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   [  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   ]  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * '-----------------------------------------------------------------------------------'
 */
[1] = LAYOUT(
  KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS,
  KC_TILD,KC_LCBR,KC_PGUP,KC_PGDN,KC_END, KC_HOME,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_RCBR,KC_PIPE,
  KC_LBRC,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_RBRC,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,ONESHOT,_______,_______
),
/* XMONAD 
 * Top row: Quit, Workspace shortcuts, Run
 * Middle row: Float, HJKL
 * Bottom row: Shift, Close, Border, Keyboard reset
 * Thumbs: Estra shifts, Space, Enter, Shifts
 */
[2] = LAYOUT(
  KC_Q,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_P,   KC_MUTE,
  KC_LSFT,_______,_______,_______,_______,KC_T,   KC_H,   KC_J,   KC_K,   KC_L,   _______,_______,
  KC_LSFT,_______,_______,KC_C,   _______,KC_B,   _______,_______,_______,_______,_______,_______,
  _______,_______,_______,KC_LSFT,KC_LSFT,KC_SPC, KC_ENT, KC_LSFT,_______,_______,KC_VOLD,KC_VOLU
),
/* Fn
 * Some macros, Keyboard-reset, mouse and audio.
 */
[3] = LAYOUT(
  _______,_______,EMAIL_W,EMAIL,  _______,_______,_______,_______,_______,_______,_______,QK_BOOT,
  _______,_______,_______,_______,_______,_______,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,_______,
  _______,_______,_______,_______,_______,_______,KC_BTN1,KC_MUTE,KC_VOLD,KC_VOLU,KC_BRID,KC_BRIU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case EMAIL:
                SEND_STRING("ste3ls@gmail.com");
                break;
            case EMAIL_W:
                SEND_STRING("benjamin@midokura.com");
                break;
        }
    }
    return true;
};
