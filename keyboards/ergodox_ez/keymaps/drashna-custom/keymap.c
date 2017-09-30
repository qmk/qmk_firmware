/*
This is the keymap for the keyboard
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"

// Define layer names 
#define BASE 0
#define COLEMAK 1
#define DVORAK 2
#define SYMB 3
#define OVERWATCH 4
#define DIABLO 5
#define MOUS 6

//define modifiers
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

//define macro keycodes
#define M_VERSION M(0)
#define M_MAKE M(1)
 
//define layer change stuff for underglow indicator
bool skip_leds = false;

//This is both for underglow, and Diablo 3 macros
bool has_layer_changed = false;
static uint8_t current_layer;

//define diablo macro timer variables
static uint16_t diablo_timer[4];
static uint8_t diablo_times[] = {0, 1, 3, 5, 10, 30};
static uint8_t diablo_key_time[4];

bool check_dtimer(uint8_t dtimer) {
    // has the correct number of seconds elapsed (as defined by diablo_times)
    return (timer_elapsed(diablo_timer[dtimer]) < ( diablo_key_time[dtimer] * 1000 ) ) ? false : true;
};


enum custom_keycodes {
	PLACEHOLDER = SAFE_RANGE, // can always be here
	EPRM,
	VRSN,
	RGB_SLD,
	RGB_0000FF,
	RGB_008000,
	RGB_FF0000,
	RGB_800080,
	RGB_00FF90,
    KC_DIABLO_CLEAR
};

#ifdef TAP_DANCE_ENABLE
enum {
	TD_FLSH = 0,
	TD_DIABLO_1,
	TD_DIABLO_2,
	TD_DIABLO_3,
	TD_DIABLO_4
};




// on each tap, light up one led, from right to left
// on the forth tap, turn them off from right to leftmake ergodox-ez-drashna-custom-teensy

void dance_flsh_each(qk_tap_dance_state_t *state, void *user_data) {
	if (!skip_leds) {
		ergodox_board_led_off();
		ergodox_right_led_1_off();
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
		skip_leds = true;
	}
	switch (state->count) {
		case 1:
			ergodox_right_led_1_on();
            break;
        case 2:
			ergodox_right_led_2_on();
			break;
		case 3:
			ergodox_right_led_3_on();
			break;
		case 4:
			ergodox_right_led_1_off();
			_delay_ms(50);
			ergodox_right_led_2_off();
			_delay_ms(50);
			ergodox_right_led_3_off();

	}
}

// on the fourth tap, set the keyboard on flash state
// and set the underglow to red, because red == bad
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >= 4) {
        rgblight_enable();
        rgblight_mode(1);
        rgblight_setrgb(0xff,0x00,0x00);
		reset_keyboard();
		reset_tap_dance(state);
	}
}

// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master (qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
    if (state->count >= 7) {
        diablo_key_time[diablo_key] = diablo_times[0];
        reset_tap_dance(state);
    } else {
        diablo_key_time[diablo_key] = diablo_times[state->count - 1];
    }
}


// Would rather have one function for all of this, but no idea how to do that...
void diablo_tapdance1 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 0);
}

void diablo_tapdance2 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 1);
}

void diablo_tapdance3 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 2);
}

void diablo_tapdance4 (qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master (state, user_data, 3);
}


// if the flash state didnt happen, then turn off leds, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
	_delay_ms(200);
	ergodox_right_led_3_off();
	_delay_ms(200);
	ergodox_right_led_2_off();
	_delay_ms(200);
	ergodox_right_led_1_off();
	_delay_ms(500);
	skip_leds = false;
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	//Once for Blue, Twice for Green, Thrice for Red, and four to flash
	[TD_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset),
    // tap once to disable, and more to enable timed micros
    [TD_DIABLO_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
    [TD_DIABLO_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
    [TD_DIABLO_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
    [TD_DIABLO_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),

};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * 
 * 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   = +  |  1 ! | 2 @  | 3 #  | 4 $  | 5 %  | TG(4)|           | TG(4)| 6 ^  | 7 &  |  8 * | 9 (  |  0 ) |  - _   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   E  |   R  |   T  | TG(3)|           |TG(3) |   Y  |   U  |   I  |   O  |   P  |  \ |   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Bksp  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  ' "   |
 * |--------+------+------+------+------+------| TG(2)|           | TG(2)|------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  , < |  . > |  ? / | Shift  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `/SYM|  ' " | LGUI |  [ { | ] }  |                                       | LEFT | DOWN |  UP  |RIGHT | SYMB |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,--------------.
 *                                        |Alt/Ap|  Win  |       | Alt  |Ctl/Esc|
 *                                 ,------|------|-------|       |------+-------+------.
 *                                 |      |      | Home  |       | PgUp |       |      |
 *                                 | Space| Bksp |-------|       |------|  DEL  |Enter |
 *                                 |      |      | End   |       | PgDn |       |      |
 *                                 `---------------------'       `---------------------'
 */
  [BASE] = KEYMAP(
				KC_EQUAL,       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       TG(MOUS),
				KC_TAB,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       TG(DIABLO),
				KC_BSPACE,      KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
                KC_LSHIFT,      CTL_T(KC_Z),KC_X,       KC_C,       KC_V,       KC_B,       TG(OVERWATCH),
				LT(SYMB,KC_GRAVE),KC_QUOTE, KC_LGUI,    KC_LBRACKET,KC_RBRACKET,
                
									ALT_T(KC_APPLICATION),  KC_LGUI,
                                                            KC_HOME,
									KC_SPACE,   KC_BSPACE,  KC_END,
									
				TG(SYMB),       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,           KC_MINUS,
				TG(DVORAK),     KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,           KC_BSLASH,
                                KC_H,       KC_J,       KC_K,       KC_L,       KC_SCOLON,      GUI_T(KC_QUOTE),
				TG(COLEMAK),    KC_N,       KC_M,       KC_COMMA,   KC_DOT,     CTL_T(KC_SLASH),KC_RSHIFT,
                                            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,       KC_FN1,
				KC_LALT,    CTL_T(KC_ESCAPE),
				KC_PGUP,
				KC_PGDOWN,  KC_DELETE,  KC_ENTER
			),
/* Keymap 1: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   F  |   P  |   G  |  L1  |           |  L1  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |O / L2|   '    |
 * |--------+------+------+------+------+------| OVER |           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[COLEMAK] = KEYMAP(  
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   TG(MOUS),
        KC_DELT,        KC_Q,         KC_W,   KC_F,   KC_P,   KC_G,   TG(DIABLO),
        KC_BSPC,        KC_A,         KC_R,   KC_S,   KC_T,   KC_D,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   TG(OVERWATCH),
        LT(SYMB,KC_GRV),KC_QUOT,      KC_LGUI,    KC_LBRACKET,KC_RBRACKET,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_TRNS,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_NO,       KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,          KC_BSLS,
                          KC_H,   KC_N,   KC_E,   KC_I,   LT(MOUS, KC_O),   KC_QUOTE,
             KC_TRNS,KC_K,KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLASH),KC_RSHIFT,
						  KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,       KC_FN1,
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 2: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   '  |   ,  |   .  |   P  |   Y  |  L1  |           |  L1  |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |S / L2|   -    |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |:/Ctrl|   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |Z/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[DVORAK] = KEYMAP(  
        // left hand
        KC_EQL,         KC_1,           KC_2,    KC_3,   KC_4,   KC_5,   TG(MOUS),
        KC_DELT,        KC_QUOT,        KC_COMM, KC_DOT, KC_P,   KC_Y,   TG(DIABLO),
        KC_BSPC,        KC_A,           KC_O,    KC_E,   KC_U,   KC_I,
        KC_LSFT,        CTL_T(KC_SCLN), KC_Q,    KC_J,   KC_K,   KC_X,   TG(OVERWATCH),
        LT(SYMB,KC_GRV),KC_QUOT, KC_LGUI, KC_LBRACKET, KC_RBRACKET,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_TRNS,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_BSLS,
             KC_TRNS,       KC_F,   KC_G,   KC_C,   KC_R,   KC_L,             KC_SLSH,
                          KC_D,   KC_H,   KC_T,   KC_N,   LT(MOUS, KC_S),   KC_MINS,
             KC_NO,KC_B,   KC_M,   KC_W,   KC_V,   CTL_T(KC_Z),      KC_RSHIFT,
	                       KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_FN1,
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),

    /* Keymap 3: Symbol Layer
*
* ,--------------------------------------------------.           ,--------------------------------------------------.
* |   ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |   F11  |
* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
* | VERSION|   !  |   @  |  {   |   }  |  |   |      |           |      |  +   |   7  |   8  |   9  |  *   |   F12  |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |  MAKE  |   #  |   $  |  (   |   )  |  `   |------|           |------|  -   |   4  |   5  |   6  |  /   | PrtSc  |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |  RESET |   %  |   ^  |  [   |   ]  |  ~   |      |           |      | NUM  |   1  |   2  |   3  |  =   |  PAUSE |
* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
*   |  LT0 |   &  |   *  |  :   |   ;  |                                       |      |   0  | NUM. | ENT  |  ENT |
*   `----------------------------------'                                       `----------------------------------'
*                                        ,-------------.       ,-------------.
*                                        | RGBM | RED  |       | OFF  | SOLID|
*                                 ,------|------|------|       |------+------+------.
*                                 |      |      | GREEN|       |      |      |      |
*                                 | RGB  | RGB  |------|       |------| NUM0 | NUME |
*                                 | DARK |BRITE | BLUE |       |      |      |      |
*                                 `--------------------'       `--------------------'
*/
  [SYMB] = KEYMAP(
				KC_ESCAPE,KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_TRNS,
				M_VERSION,      KC_EXLM,    KC_AT,      KC_LCBR,    KC_RCBR,    KC_PIPE,    KC_TRNS,
				M_MAKE,         KC_HASH,    KC_DLR,     KC_LPRN,    KC_RPRN,    KC_GRAVE,
				TD(TD_FLSH),    KC_PERC,    KC_CIRC,    KC_LBRACKET,KC_RBRACKET,KC_TILD,    KC_TRNS,
				KC_NO,          KC_AMPR,    KC_ASTR,    KC_COLN,    KC_SCOLON,
	                                                              KC_TRNS, KC_TRNS,
	                                                              KC_TRNS,
	                                                              KC_TRNS, KC_TRNS, KC_TRNS,
				
				KC_TRNS, KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,         KC_F11,
				KC_TRNS, KC_KP_PLUS, KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_KP_ASTERISK, KC_F12,
				KC_KP_MINUS,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_KP_SLASH,KC_PSCREEN,
				KC_TRNS, KC_NUMLOCK, KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_EQUAL,       KC_PAUSE,
	                                 KC_KP_0,    KC_KP_0,    KC_KP_DOT,  KC_KP_ENTER,    KC_TRNS,
				RGB_TOG,    RGB_SLD,
				KC_NO,
				KC_KP_DOT, KC_KP_0, KC_KP_ENTER
			),

/* Keymap 4: Customized Overwatch Layout
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  | SALT | MORE |  GG  | SYMM | DOOM | HARD |           |      |  F9  | F10  | F11  |  F12 |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   F1   |  K   |  Q   |  W   |  E   |  R   |  T   |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   TAB  |  G   |  A   |  S   |  D   |  F   |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  LCTR  | LSHFT|  Z   |  X   |  C   |  M   |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   J  |  U   |  I   |  Y   |  T   |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  O   |  P   |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LGUI |       |      |      |      |
 *                                 |  V   | SPACE|------        |------|      | Enter|
 *                                 |      |      |  H   |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [OVERWATCH] = KEYMAP(
				KC_ESCAPE,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
				KC_F1,          KC_K,       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,
				KC_TAB,         KC_G,       KC_A,       KC_S,       KC_D,       KC_F,
				KC_LCTL,        KC_LSHIFT,  KC_Z,       KC_X,       KC_C,       KC_M,       KC_TRNS,
				KC_G,           KC_U,       KC_I,       KC_Y,       KC_T,
                                            KC_O,   KC_P,
                                                    KC_LGUI,
                                KC_V,   KC_SPACE,   KC_H,
									
				KC_NO,          KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_NO,      KC_NO,
				KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
				KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
				KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
				KC_NO,  KC_NO,
				KC_NO,
				KC_NO,  KC_NO,  KC_ENTER
			),

/* Keymap 3:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |  V   |  D   | ALT  |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |  S   |  I   |  F   |  M   |  T   |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    Q   |  1   |  2   |  3   |  4   |  G   |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | NUMLOCK| NUM1 | NUM2 | NUM3 | NUM4 |  Z   |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTL | MAC1 | MAC2 | MAC3 | MAC4 |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |   L  |  J   |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  G   |       |      |      |      |
 *                                 | SPACE|  Q   |------        |------|      |      |
 *                                 | SHIFT| ALT  | 0MAC |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [DIABLO] = KEYMAP(
				KC_ESCAPE,  KC_V,       KC_D,       KC_LALT,    KC_NO,      KC_NO,      KC_NO,
				KC_TAB,     KC_S,       KC_F,       KC_I,       KC_M,       KC_T,       KC_TRNS,
				KC_Q,       KC_1,       KC_2,       KC_3,       KC_4,       KC_G,
				KC_LCTL, TD(TD_DIABLO_1), TD(TD_DIABLO_2), TD(TD_DIABLO_3), TD(TD_DIABLO_4), KC_Z,       KC_NO,
				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_L,   KC_J,
                                                        KC_F,
                    SFT_T(KC_SPACE),    ALT_T(KC_Q),    KC_DIABLO_CLEAR,
									
									
				KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
				KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
				KC_NO,          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
				KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
				KC_NO,          KC_NO,  KC_NO,  KC_NO,  KC_NO,
				KC_NO,  KC_NO,
				KC_NO,
				KC_NO,  KC_NO,  KC_NO
			),

/* Keymap 4: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | MsUp |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |MsLeft|MsDown|MsRght|      |      |------|           |------|      |      | Acc0 | Acc1 | Acc2 |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Acc0 | Acc1 | Acc2 |      |      |      |           |      | Play | Stop | Mute |VolDn |VolUp |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | MWUp |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------| MBn4 | MBn4 |
 *                                 |      |      | MWDn |       | Mclk |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [MOUS] = KEYMAP(
				KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_TRNS,
				KC_NO,      KC_NO,      KC_MS_UP,   KC_NO,      KC_NO,      KC_NO,      KC_TRNS,
				KC_NO,      KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,KC_NO,      KC_NO,
				KC_NO,      KC_MS_ACCEL0,KC_MS_ACCEL1,KC_MS_ACCEL2,KC_NO,   KC_NO,      KC_TRNS,
                KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
									KC_NO,KC_NO,
									KC_MS_WH_UP,
									KC_MS_BTN1,KC_MS_BTN2,KC_MS_WH_DOWN,
				
				KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,KC_MS_ACCEL0,KC_MS_ACCEL1,KC_MS_ACCEL2,KC_NO,KC_NO,
				KC_TRNS,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_STOP,KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_NO,
				KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
				KC_NO,KC_NO,
				KC_NO,
				KC_MS_BTN3,KC_MS_BTN4,KC_MS_BTN5
			),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),
    // FN1 - Momentary Layer 1 (Symbols)
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
   
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case 0:
            if (record->event.pressed) {
                // Output Keyboard Firmware info
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
            }
        case 1:
            if (record->event.pressed) {
                // make ergodox-ez-drashna-custom-teensy
                return MACRO(I(5), T(M), T(A), T(K), T(E), T(SPACE), T(E), T(R), T(G), T(O), T(D), T(O), T(X), D(LSFT), T(MINUS), U(LSFT), T(E), T(Z), T(MINUS), T(D), T(R), T(A), T(S), T(H), T(N), T(A), T(MINUS), T(C), T(U), T(S), T(T), T(O), T(M), T(MINUS), T(T), T(E), T(E), T(N), T(S), T(Y), T(ENTER), END);
            }				
    }
    return MACRO_NONE;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// dynamically generate these.
		case EPRM:
			if (record->event.pressed) {
                eeconfig_init();
			}
			return false;
			break;
		case VRSN:
			if (record->event.pressed) {
				SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
			}
			return false;
			break;
		case RGB_SLD:
			if (record->event.pressed) {
				rgblight_mode(1);
			}
			return false;
			break;

		case RGB_0000FF:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x00,0x00,0xff);
				#endif
			}
			return false;
			break;

		case RGB_008000:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x00,0x80,0x00);
				#endif
			}
			return false;
			break;

		case RGB_FF0000:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0xff,0x00,0x00);
				#endif
			}
			return false;
			break;

		case RGB_800080:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x80,0x00,0x80);
				#endif
			}
			return false;
			break;

		case RGB_00FF90:
			if (record->event.pressed) {
				#ifdef RGBLIGHT_ENABLE
				rgblight_enable();
				rgblight_mode(1);
				rgblight_setrgb(0x00,0xff,0x90);
				#endif
			}
			return false;
			break;
        case KC_DIABLO_CLEAR:  // reset all Diable timers, disabling them
            if (record->event.pressed) {
                uint8_t dtime;
                
                for (dtime = 0; dtime < 4; dtime++) {
                    diablo_key_time[dtime] = diablo_times[0];
                }
            }
            return false;
            break;
            
	}
	return true;
}


// Sends the key press to system, but only if on the Diablo layer
void send_diablo_keystroke (uint8_t diablo_key) {
    if (current_layer == DIABLO) {
        switch (diablo_key) {
            case 0:
                SEND_STRING("1");
                break;
            case 1:
                SEND_STRING("2");
                break;
            case 2:
                SEND_STRING("3");
                break;
            case 3:
                SEND_STRING("4");
                break;
        }
    }
}

// Checks each of the 4 timers/keys to see if enough time has elapsed
// Runs the "send string" command if enough time has passed, and resets the timer.
void run_diablo_macro_check(void) {
    uint8_t dtime;
    
    for (dtime = 0; dtime < 4; dtime++) {
        if (check_dtimer(dtime) && diablo_key_time[dtime]) {
            diablo_timer[dtime] = timer_read();
            send_diablo_keystroke(dtime);
        } 
    }
    
}

void matrix_init_user(void) { // Runs boot tasks for keyboard
    has_layer_changed = true;
};



void matrix_scan_user(void) {  // runs frequently to update info
    uint8_t modifiders = get_mods();
    uint8_t layer = biton32(layer_state);
	
	if (!skip_leds) {
		ergodox_board_led_off();
		ergodox_right_led_1_off();
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
        
		// Since we're not using the LEDs here for layer indication anymore,
		// then lets use them for modifier indicators.  Shame we don't have 4...
		// Also, no "else", since we want to know each, independantly. 
        if ( modifiders & MODS_SHIFT_MASK) {
                ergodox_right_led_1_on();
        }
        if ( modifiders & MODS_CTRL_MASK) {
                ergodox_right_led_2_on();
        }
        if ( modifiders & MODS_ALT_MASK) {
                ergodox_right_led_3_on();
        }
        
    }
    // Check layer, and apply color if its changed since last check
    if (has_layer_changed) {
        switch (layer) {
            case SYMB:
                rgblight_sethsv (255,255,255);
                rgblight_mode(23);
                break;
            case OVERWATCH:
                rgblight_sethsv (30,255,255);
                rgblight_mode(17);
                break;
            case DIABLO:
                rgblight_sethsv (0,255,255);
                rgblight_mode(5);
                break;
            case MOUS:
                rgblight_sethsv (60,255,255);
                break;
            case COLEMAK:
                rgblight_sethsv (300,255,255);
                break;
            case DVORAK:
                rgblight_sethsv (120,255,255);
                break;
            case 7:
                rgblight_sethsv (255,255,255);
                break;
            default:
                rgblight_sethsv (195,255,255);
                rgblight_mode(1);
                break;
        }
    }

	// Update layer status at the end, so this sets the default color
	// rather than relying on the init, which was unreliably...
	// Probably due to a timing issue, but this requires no additional code
    if (current_layer == layer) {
        has_layer_changed = false;
    } else {
        has_layer_changed = true;
        current_layer = layer;
    }

	// Run Diablo 3 macro checking code.
    run_diablo_macro_check();
};

