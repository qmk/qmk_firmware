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

#define ENCODER_MODE_CHANGE_DELAY 500

// Defining encoder click keycode
enum keyboard_keycodes {
        ECLICK = 0x5F80, // Encoder click
	ALTTABS , // For alt-tab-switch
	ALTTABC , // For alt-tab-click
	ENCMUP  , // Encoder mode up
	ENCMDN    // Encoder mode down
};

uint16_t encoder_click_delay = ENCODER_MODE_CHANGE_DELAY;

uint8_t startup_color[3] = {0xFF,0xFF,0xFF};

typedef struct _encoder_mode_t {
	uint8_t indicator_color[3];
	uint16_t clockwise_key[4];
	uint16_t counterclockwise_key[4];
	uint16_t clicked_key[4] ;
} encoder_mode_t;

encoder_mode_t encoder_modes[] = {
	{ .indicator_color = {0x22,0x00,0xFF} , .clockwise_key = {KC_VOLD, KC_VOLD, ENCMDN, KC_VOLD}, .counterclockwise_key = {KC_VOLU, KC_VOLU, ENCMUP, KC_VOLU}, .clicked_key = {KC_MUTE, KC_MPLY, KC_MUTE, KC_MUTE} },
	{ .indicator_color = {0x00,0x33,0xFF} , .clockwise_key = {KC_WH_D, KC_WH_D, ENCMDN, KC_WH_D}, .counterclockwise_key = {KC_WH_U, KC_WH_U, ENCMUP, KC_WH_U}, .clicked_key = {KC_BTN1, KC_BTN1, KC_BTN1, KC_BTN1} },
	{ .indicator_color = {0xFF,0x88,0x00} , .clockwise_key = {ALTTABS, ALTTABS, ENCMDN, ALTTABS}, .counterclockwise_key = {ALTTABS, ALTTABS, ENCMUP, ALTTABS}, .clicked_key = {ALTTABC, ALTTABC, ALTTABC, ALTTABC} }
	// Insert your custom encoder mode here
};

#define NUM_ENCODER_MODES (sizeof(encoder_modes)/sizeof(encoder_modes[0]))

// This counter is used to track what encoder mode is being used at a certain time
int encoder_mode_count = 0;

void set_indicator_colors(uint8_t color[3]){
	rgblight_setrgb(color[0], color[1], color[2]);
}

// Board init: RGB indicator is set to startup_color
#define BOARD_INIT_KEYMAP
void board_init_keymap(void){
	set_indicator_colors(startup_color);
};

void keyboard_post_init_user(void){
	set_indicator_colors(encoder_modes[0].indicator_color);
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
	encoder_mode_count = encoder_mode_count%NUM_ENCODER_MODES ; // This makes sure encoder_mode_count keeps cycling between 0,1,...,NUM_ENCODER_MODES and doesnt eventually overflow
	set_indicator_colors( encoder_modes[ encoder_mode_count ].indicator_color ); // Set indicator color to the corresponding defined color
}

bool encoder_update_user(uint8_t index, bool clockwise) {
	if (clockwise)	mapped_code = encoder_modes[ encoder_mode_count ].clockwise_key[ current_layer ];
	else mapped_code = encoder_modes[ encoder_mode_count ].counterclockwise_key[ current_layer ];
	switch (mapped_code) {
		case ALTTABS:
			if(!is_alt_tab_active) {
				is_alt_tab_active = true;
				register_code(KC_LALT);
			}
			alt_tab_timer = timer_read32();
			tap_code16(!clockwise ? KC_TAB : S(KC_TAB));
			break;
		case ENCMUP:
			cycle_encoder_mode(true);
			break;
		case ENCMDN:
			cycle_encoder_mode(false);
			break;
		default:
		{
			register_code(mapped_code);
			held_keycode_timer = timer_read32();
			while (timer_elapsed32(held_keycode_timer) < MEDIA_KEY_DELAY)
			; /* no-op */
			unregister_code(mapped_code);
			break;
		}
	}
	return false;
}

uint32_t held_click_timer = 0;
bool is_click_held = false;
bool is_shift_held = false;
bool automatic_encoder_mode_cycle = false; // This flag registers if the encoder mode was automatically cycled 

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
		if (record->event.pressed) { // What to do when the encoder is pressed
			is_click_held = true;
				held_click_timer = timer_read32(); // If the encoder delayed mode change is on, triggers a timer
		} else { // What to do when encoder is released
			is_click_held = false;

			// Scans for the time the click was pressed and does what it has to do  -- sample the timer which was triggered on press and use the sampled time to either send out the click key or change mode in case the click is held for more than ENCODER_MODE_CHANGE_DELAY
				if (timer_elapsed32(held_click_timer) < encoder_click_delay && !automatic_encoder_mode_cycle ){ // Checking if the time the encoder click was held was smaller than the delay defined and if an automatic mode change was not already performed. If it was, just register whatever it is the click does.
					switch ( encoder_modes[ encoder_mode_count ].clicked_key[ current_layer ] ){
						case ALTTABC:
							if (is_alt_tab_active) {
								if (!is_lalt_pressed) unregister_code(KC_LALT);
								is_alt_tab_active = false;
							}
							break;
						case ENCMUP:
							cycle_encoder_mode(true);
							break;
						case ENCMDN:
							cycle_encoder_mode(false);
							break;
						default:
							register_code( encoder_modes[ encoder_mode_count ].clicked_key[ current_layer ]  );
							held_keycode_timer = timer_read32();
							while (timer_elapsed32(held_keycode_timer) < MEDIA_KEY_DELAY);
							unregister_code( encoder_modes[ encoder_mode_count ].clicked_key[ current_layer ] );
						break;
					}
				} else { // If the encoder click was held for more time than the delay:
					if (!automatic_encoder_mode_cycle) {
						if (is_shift_held) cycle_encoder_mode(false);
						else cycle_encoder_mode(true);
					}
				};
		//		held_click_timer = 0;
				automatic_encoder_mode_cycle = false;
		};
		return false; // Skip all further processing of this key
	case KC_LALT: // If this is not defined, if the encoder is activated in the alt-tab mode while the LALT key is pressed, the menu goes away.
		if (record->event.pressed) is_lalt_pressed = true;
		else is_lalt_pressed = false;				
		return true;
	case ENCMUP:
		cycle_encoder_mode(true);
		return false;
	case ENCMDN:
		cycle_encoder_mode(false);
		return false;
	default:
		return true; // Process all other keycodes normally
	}
}

void housekeeping_task_user(void) { // The very important timer.
	if (is_alt_tab_active){ 
		if (is_lalt_pressed) alt_tab_timer = timer_read32();
		else if (timer_elapsed32(alt_tab_timer) > ALT_TAB_DELAY) {
			unregister_code(KC_LALT);
			is_alt_tab_active = false;
		}
	}
	if (is_click_held && timer_elapsed32(held_click_timer) > encoder_click_delay ){
		automatic_encoder_mode_cycle = true;
		held_click_timer = timer_read32();
		if (is_shift_held) cycle_encoder_mode(false);
		else cycle_encoder_mode(true);
	}
}
