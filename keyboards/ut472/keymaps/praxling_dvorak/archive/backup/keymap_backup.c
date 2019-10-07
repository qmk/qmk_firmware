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

#define LT3_TAB LT(3, KC_TAB)
#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
    LED_CHG
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Base Layer
	* ,-------------------------------------------------------------------------.
	* | Esc |  ;  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |Bspace |
	* |-------------------------------------------------------------------------+
	* |Tab/L3|  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |   -  |
	* |-------------------------------------------------------------------------+
	* | Shift |  '  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  |Sh/En|
	* |-------------------------------------------------------------------------+
	* | Ctrl| Alt | App | Gui |  L2  |   Space   |  L1  | Left| Down|  Up |Right|
	* `-------------------------------------------------------------------------'
	*/

	[0] = LAYOUT(
		KC_ESC, KC_SCLN, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, 
		LT3_TAB, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, 
		KC_LSFT, KC_QUOT, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z,MT_RSFT_ENT, 
		KC_LCTL, KC_LALT, KC_APP, KC_LGUI, TT(2), KC_SPC, TT(1), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

	/* FN Layer 1
	* ,-------------------------------------------------------------------------.
	* | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
	* |-------------------------------------------------------------------------+
	* |      |     |     |     |     |     |     |     |     |     |  /  |  \   |
	* |-------------------------------------------------------------------------+
	* |       | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |     |
	* |-------------------------------------------------------------------------+
	* |     |     |     |Capsl|      |          |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/

	[1] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH, KC_BSLS, 
		KC_TRNS, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END),


	/* FN Layer 2
	* ,-------------------------------------------------------------------------.
	* |   $  |  &  |  [  |  {  |  }  |  (  |  =  |  *  |  )  |  +  |  ]  |Delete|
	* |-------------------------------------------------------------------------+
	* |   ~  |  %  |  #  |     |     |     |     |     |  ^  |  @  |  !  |   ?  |
	* |-------------------------------------------------------------------------+
	* |       | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |     |
	* |-------------------------------------------------------------------------+
	* |     |     |     |Capsl|      |          |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/

	[2] = LAYOUT(
		KC_DLR, KC_AMPR, KC_LBRC, KC_LCBR, KC_RCBR, KC_LPRN, KC_EQL, KC_PAST, KC_RPRN, KC_PPLS, KC_RBRC, KC_DEL, 
		KC_TILD, KC_PERC, KC_HASH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CIRC, KC_AT, KC_EXLM, KC_QUES, 
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END),

	/* FN Layer 3
	* ,-------------------------------------------------------------------------.
	* | Esc | Play | Prv | Next |Mute|Vol +|Vol -|  7  |  8  |   9  |  +  |  -  |
	* |-------------------------------------------------------------------------+
	* |      |     |     |     |     |     |  .  |  4  |  5  |  6  |   *  |  /  |
	* |-------------------------------------------------------------------------+
	* |       |LEDtg|LEDch|     |     |     |  0  |  1  |  2  |  3  |Mous1|Mous2|
	* |-------------------------------------------------------------------------+
	* |     |     |     |     |      |          |       |MousL|MousD|MousU|MousR|
	* `-------------------------------------------------------------------------'
	*/

	[3] = LAYOUT(
		KC_ESC, KC_MPLY, KC_MRWD, KC_MFFD, KC__MUTE, KC__VOLDOWN, KC__VOLUP, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PMNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PDOT, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PSLS, 
		KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_P1, KC_P2, KC_P3, KC_BTN1, KC_BTN2, 
		KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R)
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


