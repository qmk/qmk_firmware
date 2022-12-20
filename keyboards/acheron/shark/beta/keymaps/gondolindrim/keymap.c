/*
Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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
#include "config_common.h"

#define MEDIA_KEY_DELAY 10
#define ALT_TAB_DELAY 1000

// Persistent encoder modes: the current encoder mode is written into EEPROM memory, and retrieved at the keyboard initialization. This means the current encoder mode is persistent even if the keyboard is reset or turned off
#define PERSISTENT_ENCODER_MODES

#define ENCODER_MODE_CHANGE_DELAY 500

// Defining special keycodes
enum keyboard_keycodes {
        ECLICK = SAFE_RANGE, // Encoder click
	ALTTABF , // ALT-TAB forward
	ALTTABB , // ALT-TAB backwards
	ALTTABC , // For alt-tab-click
	ENCMUP  , // Encoder mode up
	ENCMDN  , // Encoder mode down
	NEW_SAFE_RANGE
};

// Creates sample keyevents and keyrecords to be used in the processing of the custom keycodes. Their time should be resampled everytime they are used; their cols and rows are set to be "impossible", that is, outside the normal key matrix bounds.
const keyevent_t sample_pressed_keyevent = {
	.key = (keypos_t){.row = 5, .col = 13},
	.pressed = true,
	.time = 0
};

keyrecord_t sample_pressed_keyrecord = {
	.event = sample_pressed_keyevent
};

const keyevent_t sample_released_keyevent = {
	.key = (keypos_t){.row = 5, .col = 13},
	.pressed = false,
	.time = 0
};

keyrecord_t sample_released_keyrecord = {
	.event = sample_released_keyevent
};

// tap_process_record_user calls process_record_user with the pressed and released sample keyrecords with a delay of MEDIA_KEY_DELAY. The idea is to allow custom keycodes a simulation of a key press and release, allowing them to be treated in process_record_user. This, in turn, allows the custom keycodes to be used both in the encoder callback and the keyboard keymap.
uint16_t temp_timer = 0;
void tap_process_record_user(uint16_t keycode)
{
	temp_timer = timer_read();
	sample_pressed_keyrecord.event.time = timer_read();
	process_record_user( keycode, &sample_pressed_keyrecord );
	while (timer_elapsed(temp_timer) < MEDIA_KEY_DELAY);
	sample_released_keyrecord.event.time = timer_read();
	process_record_user( keycode, &sample_released_keyrecord );
}

// process_special_keycode is a function that distinguishes between the native keycodes and the ones custom-defined here. Normal keycodes are tapped, while keycodes in the SAFE_RANGE - NEW_SAFE_RANGE interval are treated with tap_process_record_user.
void process_special_keycode(uint16_t keycode) {
	if (SAFE_RANGE <= keycode && keycode < NEW_SAFE_RANGE) tap_process_record_user(keycode);
	else tap_code(keycode);
}

uint16_t encoder_click_delay = ENCODER_MODE_CHANGE_DELAY;

uint8_t startup_color[3] = {0xFF,0xFF,0xFF};

typedef struct _encoder_mode_t {
	uint8_t indicator_color[3];
	uint16_t clockwise_key[4];
	uint16_t counterclockwise_key[4];
	uint16_t clicked_key[4] ;
	uint16_t hold_key;
} encoder_mode_t;

encoder_mode_t encoder_modes[] = {
	{ .indicator_color = {0x22,0x00,0xFF} , .clockwise_key = {KC_VOLU, KC_VOLU, ENCMUP, KC_VOLU}, .counterclockwise_key = {KC_VOLD, KC_VOLD, ENCMDN, KC_VOLD}, .clicked_key = {KC_MUTE, KC_MPLY, KC_MUTE, KC_MUTE}, .hold_key = ENCMUP },
	{ .indicator_color = {0x00,0x33,0xFF} , .clockwise_key = {KC_WH_D, KC_WH_D, ENCMUP, KC_WH_D}, .counterclockwise_key = {KC_WH_U, KC_WH_U, ENCMDN, KC_WH_U}, .clicked_key = {KC_BTN1, KC_BTN1, KC_BTN1, KC_BTN1}, .hold_key = ENCMUP },
	{ .indicator_color = {0xFF,0x88,0x00} , .clockwise_key = {ALTTABF, ALTTABF, ENCMUP, ALTTABF}, .counterclockwise_key = {ALTTABB, ALTTABB, ENCMDN, ALTTABB}, .clicked_key = {ALTTABC, ALTTABC, ALTTABC, ALTTABC}, .hold_key = ENCMUP }
	// Insert your custom encoder mode here
};

#define NUM_ENCODER_MODES ARRAY_SIZE(encoder_modes)

// This counter is used to track what encoder mode is being used at a certain time
int encoder_mode_count = 0;


#ifdef PERSISTENT_ENCODER_MODES
typedef union {
	uint32_t raw;
	struct {
	int user_encoder_mode_count;
};
} user_config_t;

user_config_t user_config;
#endif

void set_indicator_colors(uint8_t color[3]){
    rgblight_setrgb(color[0], color[1], color[2]);
}

// Board init: RGB indicator is set to startup_color
void keyboard_pre_init_user(void){
	set_indicator_colors(startup_color);
};

void keyboard_post_init_user(void){
#ifdef PERSISTENT_ENCODER_MODES
	user_config.raw = eeconfig_read_user();
	encoder_mode_count = user_config.user_encoder_mode_count ;
#else
	encoder_mode_count = 0;
#endif
	set_indicator_colors(encoder_modes[ encoder_mode_count ].indicator_color);
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x12(
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ECLICK ,
		KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
		KC_LCTL, KC_LALT, KC_LGUI, _______, MO(1),   KC_SPC,  KC_SPC,  MO(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	),
	[1] = LAYOUT_ortho_4x12(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[2] = LAYOUT_ortho_4x12(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[3] = LAYOUT_ortho_4x12(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};

// ------------------------------------------------------------------------------------------------

bool is_alt_tab_active = false; // Flag to check if alt tab is active
uint32_t alt_tab_timer = 0;     // Time trigger for alt tab
uint16_t mapped_code = 0;
uint32_t held_keycode_timer = 0;

int current_layer = 0 ; // Updated in layer_state_set_user each time a layer change is made

void cycle_encoder_mode(bool forward){
	if (forward) encoder_mode_count++ ;  // Shifts encoder mode forward
	else encoder_mode_count-- ;
	if (encoder_mode_count == -1) encoder_mode_count = NUM_ENCODER_MODES - 1;
	// Shifts encoder mode backward
	encoder_mode_count = encoder_mode_count % NUM_ENCODER_MODES ; // This makes sure encoder_mode_count keeps cycling between 0,1,...,NUM_ENCODER_MODES and doesnt eventually overflow
#ifdef PERSISTENT_ENCODER_MODES
	user_config.user_encoder_mode_count = encoder_mode_count ;
	eeconfig_update_user(user_config.raw);
#endif
	set_indicator_colors( encoder_modes[ encoder_mode_count ].indicator_color ); // Set indicator color to the corresponding defined color
}

bool encoder_update_user(uint8_t index, bool clockwise) {
	process_special_keycode(clockwise ? encoder_modes[ encoder_mode_count ].clockwise_key[ current_layer ] : encoder_modes[ encoder_mode_count ].counterclockwise_key[ current_layer ]);
	return false;
}

uint32_t held_click_timer = 0;
bool is_click_held = false;
bool is_shift_held = false;
bool automatic_hold_cycle = false; // This flag registers if the encoder hold was automatically cycled 

// This bool records if LALT is pressed or not. Due to the automatic disabling of the ALT-TAB of the ALTTABS custom keystroke, the automatic disabling can un-register KC_LALT even when the LALT key is phisically pressed. Hence there needs to be two bools: one that keebs track of the ALT-TAB activity and one that keeps track of LALT so that the automatic disabling will not disable LALT if it is phisically pressed.
bool is_lalt_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case KC_LSFT:
	case KC_RSFT:
		if (record->event.pressed) is_shift_held = true;
		else is_shift_held = false;
		return true;
	case ECLICK:
		// Checks if the encoder has been pressed; if so, sets the corresponding flag and starts the corresponding timer
		if (record->event.pressed) {
			is_click_held = true;
			held_click_timer = timer_read32();
		// Checks if the encoder has been released: samples the duration of the encoder push; if this time was less than the encoder_click_delay, processes the clicked key. If it was bigger, processes the hold key. This behavior is adjusted using the ENCODER_MODE_CHANGE_DELAY macro. There is an exception made when automatic_hold_cycle is true; this means that the encoder push has been pressed enough to trigger a hold cycle. This case is taken care of in the housekeeping routine, where the held key is triggered and the timer reset. Hence the automatic_hold_cycle needs to be checked because without this check the function will trigger the clicked key after the hold cycle has been cycled more than once.
		} else {
			is_click_held = false;
			if (timer_elapsed32(held_click_timer) < encoder_click_delay && !automatic_hold_cycle ) process_special_keycode( encoder_modes[ encoder_mode_count ].clicked_key[ current_layer ] ) ;
			automatic_hold_cycle = false;
		}
		return true; // Skip all further processing of this key
	case KC_LALT: // If this is not defined, if the encoder is activated in the alt-tab mode while the LALT key is pressed, the menu goes away.
		if (record->event.pressed) is_lalt_pressed = true;
		else is_lalt_pressed = false;				
		return true;
	case ENCMUP:
	case ENCMDN:
		if (record->event.pressed) cycle_encoder_mode(keycode == ENCMUP); // If keycode == ENCMUP the expression returns true and the cycle function cycles the modes forward. If not, then cycles backwards.
		return false;
	case ALTTABF:
	case ALTTABB:
		if (record->event.pressed) {
			if (!is_alt_tab_active) {
				is_alt_tab_active = true;
				register_code(KC_LALT);
			
			}
			tap_code16(keycode == ALTTABF ? KC_TAB : S(KC_TAB)); // Due to S(KC_TAB), the 16-bit tap_code16 is needed.
			alt_tab_timer = timer_read32();
		}
		return true;
	case ALTTABC:
		if (record->event.pressed) {
			if (is_alt_tab_active) {
				if (!is_lalt_pressed) unregister_code(KC_LALT);
				is_alt_tab_active = false;
			}
		}
		return false;
	default:
		return true; // Process all other keycodes normally
	}
}

void housekeeping_task_user(void) {
	if (is_alt_tab_active) {
		if (is_lalt_pressed) alt_tab_timer = timer_read32();
		else if (timer_elapsed32(alt_tab_timer) > ALT_TAB_DELAY) {
			unregister_code(KC_LALT);
			is_alt_tab_active = false;
		}
	}
/*		This piece of the code checks for the encoder push timer. If the encoder push interval was less than encoder_click_delay then it is automatically processed by process_record_user by triggering the current mode's click key. However, if the encoder push is held for more time than the defined delay, then the encoder hold "cycles", that is, gets activated and the timer needs to be reset. This does three things: 
- (1) Sets the automatic_hold_cycle flag which prevents process_record_user from triggering the click key when the push is released
- (2) Processes the current mode's hold key in process_record_user
- (3) Resets the click timer
*/
	if (is_click_held && timer_elapsed32(held_click_timer) > encoder_click_delay ){
		automatic_hold_cycle = true;
		process_special_keycode( encoder_modes[ encoder_mode_count ].hold_key );
		held_click_timer = timer_read32();
	}
}
