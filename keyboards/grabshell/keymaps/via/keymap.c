/* Copyright 2024 @ Grabshell (https://grabshell.site/)
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

enum layer_names {
    _BASE,
    _FnLay,
    NONE1,
    NONE2
};

report_mouse_t pointing_device_driver_get_report_user(report_mouse_t mouse_report);

/*
   _BASE / Default Key Map
   ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬───────┬┬───────┬─────┬─────┐─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
   │ ESC │  1  │  2  │  3  │  4  │  5  │      │     │ ALT │ -_  │       ││       │ =+  │ ALT │     │      │  6  │  7  │  8  │  9  │  0  │ `~  │
   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐├─────┴┐────┴┐────┴┐      ││      ┌┴────┌┴────┌┴─────┤┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   │ BS  │  Q  │  W  │  E  │  R  │  T  │     ││ TAB  │ GUI │ [{  │      ││      │ ]}  │ GUI │ ENT  ││     │  Y  │  U  │  I  │  O  │  P  │ -_  │
   └─────┼─────┼─────┼─────┼─────┼─────┤Shift│├──────┴┐────┴┐────┴┐     ││     ┌┴────┌┴────┌┴──────┤│Shift├─────┼─────┼─────┼─────┼─────┼─────┘
         │  A  │  S  │  D  │  F  │  G  │     ││ _FnLay│ CTL │ \|  │     ││     │ '"  │ -_  │ _FnLay││     │  H  │  J  │  K  │  L  │ ;:  │
         ├─────┼─────┼─────┼─────┼─────┼─────┘├───────┴─────┴─────┘     ││     ╰─────┴─────┴───────┤╰─────┼─────┼─────┼─────┼─────┼─────┤
         │  Z  │  X  │  C  │  V  │  B  │      ├──────╮╭─────────╮       ││                  ╭──────┤      │  N  │  M  │ ,<  │ .>  │ /?  │
         └─────┴─────┴─────┴─────┴─────┘      │ BTN1 ││         │Toggle ││     Track        │ BTN1 │      └─────┴─────┴─────┴─────┴─────┘
                    Back Left                 ├──────┤│ KC_BTN1 │Switch ││      Ball        │──────┤          Back Right
                                              │ BTN2 │╰─────────┘       ││                  │ BTN2 │
                                              ├──────┤╭─────────╮╭──────┤├──────┬─────┬─────│──────┤
                                              │ PGUP ││ enc sw  ││ PGDN ││ LEFT │ UP  │DOWN │RIGHT │
                                              ├──────┘╰─────────┘╰──────┤├──────┴─────┴─────┴──────┤
                                              ╰────── Frent Left ───────┴┴────── Frent Right ──────┘
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,	      	        KC_SPC,	    KC_LALT,    KC_MINS,            KC_EQL,	    KC_RALT,    KC_SPC,           	    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_GRV,
    KC_BSPC,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_LSFT,    KC_TAB,	    KC_LGUI,	KC_LBRC,	        KC_RBRC,	KC_RGUI,    KC_ENT,     KC_RSFT,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_MINS,
                KC_A,       KC_S,       KC_D,       KC_F,       KC_G,	      	        MO(_FnLay),	KC_LCTL,	KC_BSLS,	        KC_QUOT,    KC_RCTL,    MO(_FnLay),             KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,
                KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,	      	        KC_BTN1,	KC_BTN3,    XXXXXXX,               	                    KC_BTN2,                KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,
                 	                 	                 	                            KC_BTN2,	                 	                 	                KC_BTN1,
                	                 	                 	                            KC_PGUP,	KC_BTN3,	KC_PGDN,   KC_LEFT, KC_UP,      KC_DOWN,    KC_RIGHT
    ),
    [_FnLay] = LAYOUT(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    RGB_TOG,	      	    KC_TRNS,    KC_TRNS,    KC_TRNS,   	        KC_TRNS,	KC_TRNS,    KC_TRNS,	           	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_DEL,	    KC_TRNS,    KC_UP,      KC_TRNS,    KC_MUTE,    RGB_MOD,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_7,       KC_8,     KC_9,      KC_PEQL,   KC_PPLS,   KC_TRNS,
                KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_VOLD,    RGB_HUI,	            KC_TRNS,	KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,	            KC_4,       KC_5,     KC_6,      KC_0,	    KC_PAST,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_VOLU,    RGB_HUD,	      	    KC_TRNS,	KC_TRNS,    KC_TRNS,    	                 	        KC_TRNS,	            KC_1,       KC_2,     KC_3,      KC_TRNS,   KC_TRNS,
                 	                 	                 	                            KC_TRNS,	                 	                 	                KC_TRNS,
                	                 	                 	                            KC_HOME,	KC_TRNS,    KC_END,    KC_TRNS, KC_TRNS,	KC_TRNS,    KC_TRNS
    ),
    [NONE1] = LAYOUT(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,	KC_TRNS,   	        KC_TRNS,	KC_TRNS,    KC_TRNS,	           	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	            KC_TRNS,	KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,	KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,    KC_TRNS,    	                 	        KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                 	                 	                 	                            KC_TRNS,	                 	                 	                KC_TRNS,
                	                 	                 	                            KC_TRNS,	KC_TRNS,	KC_TRNS,   KC_TRNS, KC_TRNS,	KC_TRNS,    KC_TRNS
    ),
    [NONE2] = LAYOUT(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,	KC_TRNS,   	        KC_TRNS,	KC_TRNS,    KC_TRNS,	           	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	            KC_TRNS,	KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,	KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,    KC_TRNS,    	                 	        KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                 	                 	                 	                            KC_TRNS,	                 	                 	                KC_TRNS,
                	                 	                 	                            KC_TRNS,	KC_TRNS,	KC_TRNS,   KC_TRNS, KC_TRNS,	KC_TRNS,    KC_TRNS
    ),
};
