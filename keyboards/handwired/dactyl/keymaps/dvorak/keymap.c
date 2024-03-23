// Copyright 2017 Erin Call
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,
    SYMB,
    MDIA
};

#define ONE_GRV LT(SYMB, KC_GRAVE)
#define CTL_Z LCTL_T(KC_Z)
#define ALT_SHFT LALT(KC_LSFT)
#define ALT_MENU LALT_T(KC_MENU)
#define LG_SLSH LGUI_T(KC_SLSH)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_SCLN LCTL_T(KC_SCLN)
#define LT2_S LT(MDIA, KC_S)

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
    VRSN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Del  |  '"  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BkSp |   A  |   O  |   E  |   U  |   I  |                    |   D  |   H  |   T  |   N  | S/L2 |//Cmd |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|;/Ctrl|   Q  |   J  |   K  |   X  |                    |   B  |   M  |   W  |   V  |Z/Ctrl|RShift|
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |Grv/L1|   =  |AltShf| Left | Right|                                  |  Up  | Down |   [  |   ]  | ~L1  |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      | App  | LGui |  | Alt  | ^/Esc|
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      | Home |  | PgUp |      |      |
 *                               | Space|Backsp|------|  |------|  Tab |Enter |
 *                               |      |ace   | End  |  | PgDn |      |      |
 *                               `--------------------'  `--------------------'
 */
    [BASE] = LAYOUT(
		KC_EQL,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,                                             KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS,
		KC_DEL,  KC_QUOT,  KC_COMM,  KC_DOT,  KC_P,    KC_Y,                                             KC_F,   KC_G,  KC_C,    KC_R,    KC_L,    KC_BSLS,
		KC_BSPC, KC_A,     KC_O,     KC_E,    KC_U,    KC_I,                                             KC_D,   KC_H,  KC_T,    KC_N,    LT2_S,   LG_SLSH,
		KC_LSFT, CTL_SCLN, KC_Q,     KC_J,    KC_K,    KC_X,                                             KC_B,   KC_M,  KC_W,    KC_V,    CTL_Z,   KC_RSFT,
		ONE_GRV, KC_EQL,   ALT_SHFT, KC_LEFT, KC_RGHT,                                                           KC_UP, KC_DOWN, KC_LBRC, KC_RBRC, TT(SYMB),
															   ALT_MENU, KC_LGUI,      KC_RALT, CTL_ESC,
													   KC_SPC, KC_BSPC,  KC_HOME,      KC_PGUP, KC_TAB,  KC_ENT,
																         KC_END,       KC_PGDN
    ),
/* Keymap 1: Symbol Layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |Versn |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |                    |  Up  |   7  |   8  |   9  |   *  |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |   )  |   `  |                    | Down |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   ~  |                    |   &  |   1  |   2  |   3  |   \  |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |QK_BOOT |      |      |      |      |                                  |      |   .  |   0  |   =  |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 */
	[SYMB] = LAYOUT(
		VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                            KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,
		KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                          KC_UP,   KC_P7,   KC_8,    KC_9,  KC_PAST, KC_F12,
		KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                           KC_DOWN, KC_P4,   KC_5,    KC_6,  KC_PPLS, KC_TRNS,
		KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                                          KC_AMPR, KC_P1,   KC_2,    KC_3,  KC_PSLS, KC_TRNS,
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                            KC_TRNS, KC_PDOT, KC_P0, KC_PEQL, KC_TRNS,
															  KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
													 KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
												                       KC_TRNS,      KC_TRNS			
	),
/* Keymap 2: Media and mouse keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | MsUp |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MsLeft|MsDown|MsRght|      |                    |      |      |      |      |      | Play |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      | Prev | Next |      |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |      |      |      | Lclk | Rclk |                                  | VolUp| VolDn| Mute |      |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |Brwser|
 *                               |      |      |------|  |------|      |Back  |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 *
 */
	[MDIA] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS,                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
		KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                                          KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN2,                                                             KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
															       KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
													      KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_WBAK,
														                    KC_TRNS,      KC_TRNS
	)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
  }
  return true;
}
