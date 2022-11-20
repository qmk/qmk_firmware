/* Copyright 2021 Flare576 <flare576@gmail.com>
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
#include "print.h"
#include "enums.h"
#include "graphics.h"

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PLAY] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
    [TD_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
};

#define KC_TPLY TD(TD_PLAY)
#define KC_THME TD(TD_HOME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Alt/Tb|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  PLAY |    | PAGE  |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |+/SHFT|
 * `-----------------------------------------/       /     \Enter \-----------------------------------------'
 *            | ESDF | LAlt | ESC/ | LGUI | /Space  /       \ or   \  | Bspc | Alt+ |Delete|FFXIV |
 *            |      |      |Symbol|      |/       /         \Mouse \ |      |Shift |      |      |
 *            `----------------------------------'           '------''---------------------------'
 *
 * Note: Apple's keyboard settings don't seem to discern right- and left-ALT, so swapping keys there breaks TAB & META
 */
[_BASE] = LAYOUT(
  KC_GRV,         KC_1, KC_2,      KC_3,    KC_4,             KC_5,                                KC_6,    KC_7,          KC_8,    KC_9,     KC_0,    KC_MINS,
  RALT_T(KC_TAB), KC_Q, KC_W,      KC_E,    KC_R,             KC_T,                                KC_Y,    KC_U,          KC_I,    KC_O,     KC_P,    KC_BSLS,
  KC_LSFT,        KC_A, KC_S,      KC_D,    KC_F,             KC_G,                                KC_H,    KC_J,          KC_K,    KC_L,     KC_SCLN, KC_QUOT,
  KC_LCTRL,       KC_Z, KC_X,      KC_C,    KC_V,             KC_B,    KC_TPLY, KC_THME,           KC_N,    KC_M,          KC_COMM, KC_DOT,   KC_SLSH, RSFT_T(KC_PLUS),
                        TG(_ESDF), KC_LALT, LT(_SYMS,KC_ESC), KC_LGUI, KC_SPC,  LT(_MOUS, KC_ENT), KC_BSPC, RSFT(KC_RALT), KC_DEL,  TG(_FF14)
),

/*
 * MOUS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CTRL+W|ALT+A |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |PRNTSC|      | M UP | HOME | PGUP |                    |M Wl U|M Wl D|M Wl L|M Wl R|      |COMP1 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |SC LCK|M LFT |M DWN |M RGHT|      |-------.    ,-------|  UP  | DOWN | LEFT |RIGHT |      |COMP2 |
 * |------+------+------+------+------+------| TRNS  |    | TRNS  |------+------+------+------+------+------|
 * | TRNS |PAUSE |      |      | END  | PGDN |-------|    |-------|MOUS1 |MOUS2 |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      | TRNS | TRNS |TRNS  | / TRNS  /       \ TRNS \  |MOUS3 |MOUS4 |MOUS5 |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_MOUS] = LAYOUT(
  LCTL(KC_W), LALT(KC_A), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
  _______,    KC_PSCR,    XXXXXXX, KC_MS_U, KC_HOME, KC_PGUP,                   KC_WH_U, KC_WH_D, KC_WH_L, KC_WH_R,  XXXXXXX, _COMP1,
  _______,    KC_SLCK,    KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, _COMP2,
  _______,    KC_PAUS,    XXXXXXX, XXXXXXX, KC_END,  KC_PGDN, _______, _______, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
                          XXXXXXX, _______, _______, _______, _______, _______, KC_BTN3, KC_BTN4, KC_BTN5, XXXXXXX
),

/* SYMS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  | F5   |                    |      |      |   {  |   }  |      | QK_BOOT|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |  F6  |  F7  |  F8  |  F9  | F10  |                    |      |      |   (  |   )  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS | F11  | F12  | F13  | F14  | F15  |-------.    ,-------|      |      |   [  |   ]  |      |      |
 * |------+------+------+------+------+------| TRNS  |    | TRNS  |------+------+------+------+------+------|
   | TRNS | UNDO | CUT  | COPY |PASTE | F20  |-------|    |-------|      |      |   <  |   >  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | TRNS | TRNS | TRNS | TRNS | / TRNS  /       \ TRNS \  | TRNS | TRNS | TRNS | TRNS |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYMS] = LAYOUT(
  XXXXXXX, KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                      XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, QK_BOOT,
  _______, KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,                     XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,
  _______, KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,                     XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX,
  _______, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), KC_F20,  _______,  _______, XXXXXXX, XXXXXXX, KC_LT,   KC_GT,   XXXXXXX, XXXXXXX,
                       XXXXXXX,    _______,    _______,    _______, _______,  _______, _______, _______, _______, XXXXXXX
),

/* FF14
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |                    | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  | TRNS | TRNS | TRNS | TRNS | TRNS |                    | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |-------.    ,-------| TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * |------+------+------+------+------+------| TRNS  |    | TRNS  |------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |-------|    |-------| TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | ESDF |      | ESC  | TRNS | / TRNS  /       \ TRNS \  | TRNS |PrntSc| TRNS | TRNS |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_FF14] = LAYOUT(
  _______, _______, _______,   _______, _______, _______,                   _______, _______, _______, _______, _______,  _______,
  KC_TAB,  _______, _______,   _______, _______, _______,                   _______, _______, _______, _______, _______,  _______,
  _______, _______, _______,   _______, _______, _______,                   _______, _______, _______, _______, _______,  _______,
  _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
                    TO(_ESDF), XXXXXXX, KC_ESC,  _______, _______, _______, _______, KC_PSCR, _______, _______
),

/* ESDF
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   T  |  Tab |   Q  |   W  |   E  |   R  |                    | Ctl-Y| Ctl-U| Ctl-I| Ctl-O| Ctl-P| PGUP |
 * |------|------+------+------+------+------+                    |------+------+------+------+------+------|
 * |   G  |LShift|   A  |   S  |   D  |   F  |-------.    ,-------| Ctl-H| Ctl-J| Ctl-K| Ctl-L| Ctl-;| PGDN |
 * |------|------+------+------+------+------+       |    |       |------+------+------+------+------+------|
 * | LCtrl|  Z   |   X  |   C  |   V  |   B  |-------|    |-------| Ctl-N| Ctl-M| Ctl-,| Ctl-.| Ctl-/|   M  |
 * `-----------------------------------------/       /     \Enter \-----------------------------------------'
 *            | TRNS |      | ESC  | LAlt | /Space  /       \      \  |PrnScr|      |      | FF14 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_ESDF] = LAYOUT(
  KC_GRV, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,       KC_7,       KC_8,          KC_9,         KC_0,          KC_EQL,
  KC_T,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,                      RCTL(KC_Y), RCTL(KC_U), RCTL(KC_I),    RCTL(KC_O),   RCTL(KC_P),    KC_PGUP,
  KC_G,   KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                      RCTL(KC_H), RCTL(KC_J), RCTL(KC_K),    RCTL(KC_L),   RCTL(KC_SCLN), KC_PGDN,
  KC_LCTRL, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, RCTL(KC_N), RCTL(KC_M), RCTL(KC_COMM), RCTL(KC_DOT), RCTL(KC_SLSH), KC_M,
                   _______, XXXXXXX, _______, _______, _______, _______, _______,    KC_PSCR,    _______,       TO(_FF14)
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case _COMP1:
            if (record->event.pressed) {
                // SEND_STRING(SS_TAP(X_RCTRL) SS_DELAY(100) SS_TAP(X_RCTRL) SS_DELAY(100) "1" SS_TAP(X_ENTER));
                keymap_config.swap_lalt_lgui = false;
            }
            return false;
        case _COMP2:
            if (record->event.pressed) {
                // SEND_STRING(SS_TAP(X_RCTRL) SS_DELAY(100) SS_TAP(X_RCTRL) SS_DELAY(100) "2" SS_TAP(X_ENTER));
                keymap_config.swap_lalt_lgui = true;
            }
            return false;
        case KC_SPC:
            luna_jump(record->event.pressed);
            break;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_THME:
        case KC_TPLY:
            return TAPPING_TERM + 250;
        default:
            return TAPPING_TERM;
    }
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDOWN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif
