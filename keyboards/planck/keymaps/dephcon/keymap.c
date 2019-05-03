/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _SUPER
};

enum custom_keycodes {
SEL = SAFE_RANGE
,UPD
,WALK
,MARON
,ADS
,AGREE
,AINT
,POPCRN
,CTRL3
,LIMIT
};

enum {
  TD_CAPS = 0,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SUPER MO(_SUPER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
		TD(TD_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
		KC_LCTL, KC_LGUI, KC_LALT, SUPER, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_RGHT, KC_DOWN, KC_UP
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   [  |   ]  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
		KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
		KC_LSFT, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_HOME, KC_END, KC_TRNS,
		KC_RCTL, KC_RGUI, KC_RALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_END, KC_PGDN, KC_PGUP
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   {  |   }  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_DEL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,
		KC_LSFT, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_END, KC_PGUP, KC_PGDN
),

/* SUPER
 * ,-----------------------------------------------------------------------------------.
 * |RESET | SEL  |  UPD | ALT3 | ADS  |      |      |      | CLAP |MARON | WALK |BL_TOG|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |BL_DN |BL_INC|BLSTEP|      |      |      |      |      |      |AGREE |POPCRN|SADMJ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |MU_ON |MU_OFF|      |      |      |             |      | Prev | Next | Vol- | Vol+ |
 * `-----------------------------------------------------------------------------------'
 *
 */

[_SUPER] = LAYOUT_planck_grid(
  RESET, SEL, UPD, CTRL3, ADS, LIMIT, KC_TRNS, KC_TRNS, KC_TRNS, MARON, WALK, BL_TOGG,
		BL_DEC, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, AGREE, AINT, POPCRN, KC_TRNS,
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_MPLY, KC_TRNS, KC_TRNS,
		MU_ON, MU_OFF, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    if (record->event.pressed) {
        switch(keycode) {
            case SEL:
                SEND_STRING("SELECT TOP 1000 * FROM ");
                return false;
            case UPD:
                SEND_STRING("UPDATE "SS_TAP(X_ENTER)" SET "SS_TAP(X_ENTER)"WHERE "); // UPDATE STATEMENT
                return false;
            case WALK:
                SEND_STRING("https://i.imgur.com/mWQRAFU.gifv"SS_TAP(X_ENTER)); //walking into work
                return false;
            case MARON:
                SEND_STRING("https://i.imgur.com/7xweg.jpg"SS_TAP(X_ENTER)); //Maroney face
                return false;
            case ADS:
                 SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_C)SS_UP(X_LCTRL)SS_TAP(X_END)SS_TAP(X_ENTER)"SELECT TOP 1000 * FROM "SS_DOWN(X_LCTRL)SS_TAP(X_V)SS_UP(X_LCTRL)SS_TAP(X_END)SS_DOWN(X_LSHIFT)SS_TAP(X_HOME)SS_UP(X_LSHIFT)SS_TAP(X_F5)SS_TAP(X_BSPACE)SS_TAP(X_HOME)SS_TAP(X_BSPACE)); //SEL TOP 1K FOR ADS
                return false;
            case AGREE:
                SEND_STRING("https://i.imgur.com/EucIfYY.gifv"SS_TAP(X_ENTER)); // Agreement
                return false;
            case AINT:
                SEND_STRING("https://i.imgur.com/nTXnixm.jpg"SS_TAP(X_ENTER)); // Ain't nobody got time for that
                return false;
            case POPCRN:
                SEND_STRING("https://i.imgur.com/0hQyd5L.gifv"SS_TAP(X_ENTER)); // Popcorn
                return false;
            case CTRL3:
                SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_3)SS_UP(X_LCTRL)); // CTRL+3
                return false;
            case LIMIT:
                SEND_STRING("SELECT * FROM  LIMIT 100"); // CTRL+3
                return false;

        }
    }
    return true;
};
