/*
Copyright 2021 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

/* ---------------------------------------------- EVOLV75 GONDOLINDRIM LAYOUT
This is the firmware for the Evolv75 CE (pre-Alpha) PCBs as designed by Gondolindrim.

The final objective is to achieve a joystic encoder feature where the encoder can exhibit multiple behaviours, hereby called "encoder modes", which can be switched seamlessly by the user. In order to make the user know what encoder mode is active at a given instant, the keyboard has RGB underglow LEDs that shine a particular color; each mode has its own color.

Modes, their behaviours and their colors are user-customizable.
*/

/* ---------------------------------------------- BASIC DEFINITIONS
DON"T CHANGE ANY OF THESE.
*/

#include QMK_KEYBOARD_H
typedef uint8_t color[3];
#define COLOR(h,s,v) ((color){h,s,v})

// Defining custom keycodes
enum keyboard_keycodes {
        ENCCLK = 0x5F80,	// For "encoder click"
	ENCNTH,			// "Encoder north"
	ENCSTH,			// "Encoder south"
	ENCEST,			// "Encoder east"
	ENCWST,			// "Encoder west"
	ALTTABN,		// For alt-tab-switch, next
	ALTTABP,		// For alt-tab-switch, previous
	ALTTABC, 		// For alt-tab-click
	ENCMUP,			// Encoder mode up
	ENCMDN			// Encoder mode down
};

// Defining the encoder mode data structure
typedef struct _encoder_mode_t {
	color indicator_color;
	uint16_t clockwise_key[4];
	uint16_t counterclockwise_key[4];
	uint16_t clicked_key[4];
	uint16_t north_key[4];
	uint16_t south_key[4];
	uint16_t east_key[4];
	uint16_t west_key[4];
} encoder_mode_t;

/* ---------------------------------------------- COLORS
Colors are defined as HSV values where the values range from 0 to 255. Template:

#define <COLOR NAME> COLOR( <HSV CODE> )

Use these to define the colors for encoder modes.
*/

#define CYAN COLOR(128,255,255)
#define PINK COLOR(191,255,255)
#define YELLOW COLOR(36,255,255)
#define WHITE COLOR(0,0,255)
#define STARTUP_COLOR WHITE

/* ---------------------------------------------- DELAYS
These delays define some important behaviours on the firmware.

MEDIA_KEY_DELAY is used throughout the code to hold certain keycodes for a time before holding them; this allows the use of media keys like volume up and down everywhere.

ALT_TAB_DELAY is the time delay the firmware holds the LALT key before letting it go; in practical use this means once you rotate the encoder in alt-tabbing mode, it will keep the alt-tab window held for this amount of time.

ENCODER_CLICK_DELAY defines a delayed behavior for the encoder click. Once you click it, a timer is triggered and monitored. If the click is held for more than this macro (defaults to 1000 or 1 second), encoder modes start cycling, each per second, and stops when you release. If you hold the click for shorter than the time defined in this macro, then the firmware registers the key contained in the .clicked_key list of that mode.
*/

#define MEDIA_KEY_DELAY 20
#define ALT_TAB_DELAY 2000
#define ENCODER_CLICK_DELAY 1000

// -------------------------------------------- ENCODER MODES
/* Encoder mode list
WARNING: DO NOT, ABSOLUTELY DO NOT use ENCNTH, ENCSTH, ENCWST or ENCEST in any of the encoder mode keys. The reason is because these keycodes are used in process_record_user and they point to these very same encoder mode keys; this could generate a loop in process_record_user and freeze the keyboard.

You can add and remove modes at will as long as you have at least one.
*/
const encoder_mode_t encoder_modes[] = {
	// PINK MODE: "media mode". Encoder controls volume (and mode change on layer 1); click does media pause (mute on layer 1), directionals do arrows.
	{ .indicator_color = PINK,
	  .clockwise_key = {KC_VOLU, ENCMUP, KC_VOLU, KC_VOLU},
	  .counterclockwise_key = {KC_VOLD, ENCMDN, KC_VOLD, KC_VOLD},
	  .clicked_key = {KC_MUTE, KC_MUTE, KC_MPLY, KC_MUTE},
	  .north_key = {KC_UP, KC_UP, KC_UP, KC_UP},
	  .south_key = {KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN},
	  .east_key = {KC_RGHT, KC_RGHT, KC_RGHT, KC_RGHT},
	  .west_key = {KC_LEFT, KC_LEFT, KC_LEFT, KC_LEFT}
	},
	/* CYAN MODE: "application mode". Switches back and forth between applications ("alt-tabbing"); click stops the alt-tabbing at the selected application. When on layer 1, encoder changes modes. East-west switches tabs ("ctrl-tabbing") and north-sourh maximizes/minimizes windows (GUI plus up and down). Note: these are modifier keys defined natively in QMK
	- C(kc) means hold left control and press kc
	- MEH(kc) means hold left control, left shift and press kc
	- G(kc) means hold LGUI and press kc
*/
	{ .indicator_color = CYAN,
	  .clockwise_key = {ALTTABN, ENCMUP, ALTTABN, ALTTABN},
	  .counterclockwise_key = {ALTTABP, ENCMDN, ALTTABP, ALTTABP},
	  .clicked_key = {ALTTABC, ALTTABC, ALTTABC, ALTTABC},
	  .north_key = {G(KC_UP),G(KC_UP), G(KC_UP), G(KC_UP)},
	  .south_key = {G(KC_DOWN), G(KC_DOWN), G(KC_DOWN), G(KC_DOWN)},
	  .east_key = {C(KC_TAB), C(KC_TAB), C(KC_TAB), C(KC_TAB)},
	  .west_key = {S(C(KC_TAB)), S(C(KC_TAB)), S(C(KC_TAB)), S(C(KC_TAB))}
	},
	// YELLOW MODE: "navigation mode". Encoder mimicks mousehwheel, click does mouseclick. North-wouth does page up/down, east-west do home and end.
	{ .indicator_color = YELLOW,
	  .clockwise_key = {KC_WH_U, ENCMUP, KC_WH_U, KC_WH_U},
	  .counterclockwise_key = {KC_WH_D, ENCMDN, KC_WH_D, KC_WH_D},
	  .clicked_key = {KC_BTN1, KC_BTN2, KC_BTN1, KC_BTN1},
	  .north_key = {KC_PGUP, KC_PGUP, KC_PGUP, KC_PGUP},
	  .south_key = {KC_PGDN, KC_PGDN, KC_PGDN, KC_PGDN},
	  .east_key = {KC_END, KC_END, KC_END, KC_END},
	  .west_key = {KC_HOME, KC_HOME, KC_HOME, KC_HOME}
	}
	// Insert your custom encoder mode here
};

#define NUM_ENCODER_MODES ARRAY_SIZE(encoder_modes) // DO NOT CHANGE THIS. NUM_ENCODER_MODES calculates how many modes there are.

// This counter is used to track what encoder mode is being used at a certain time
int encoder_mode_count = 0;

/* ---------------------------------------------- RGB STARTING COLOR
Due to the way rgblight.c stores to and re-stores RGB configurations from EEPROM, the first time the MCU boots up, the EEPROM will not have stored the default value for the RGB animation which in QMK is the static red light; however, during the first bootup, this EEPROM will be set so that, in all subsequent bootups, the RGBs will glow red instead of whatever color the first encoder mode is. What these lines do is re-define the default RGB color so that the default RGB color is defined the same as encoder mode [0] so that the RGB will glow this color once the keyboard boots. DONT CHANGE THIS.
*/
#define RGBLIGHT_DEFAULT_HUE encoder_modes[0].indicator_color[0]
#define RGBLIGHT_DEFAULT_SAT encoder_modes[0].indicator_color[1]
#define RGBLIGHT_DEFAULT_VAL encoder_modes[0].indicator_color[2]

/* ---------------------------------------------- DEFINING DEFAULT KEYMAP
Adapt this at will with the caveat that you should not have more nor less than four layers. And let's be honest, if you find yourself needing more than four layers on a 75% keyboard you are probably doing something wrong.
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_evolv_iso( 
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_INS ,           
	KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_BSPC, KC_DEL ,          ENCNTH,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_ENT ,          KC_PGUP, ENCWST , ENCCLK, ENCEST,
        KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_NUHS,                   KC_PGDN,          ENCSTH,
        KC_LSFT, KC_BSLS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  , MO(1)  ,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                            KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),
   [1] = LAYOUT_evolv_iso(                                                                                                                                                  
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           ENCNTH,        
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,  ENCWST , ENCCLK, ENCEST,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,           ENCSTH,        
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_TRNS,  
        _______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______),
   [2] = LAYOUT_evolv_iso(                                                                                                                                                  
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           ENCNTH,        
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,  ENCWST , ENCCLK, ENCEST,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,           ENCSTH,        
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,  
        _______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______),
   [3] = LAYOUT_evolv_iso(                                                                                                                                                  
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            ENCNTH,        
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   ENCWST , ENCCLK, ENCEST,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,            ENCSTH,        
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,  
        _______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______)
};

/* ---------------------------------------------- END OF USER CUSTOMIZABLE CODE
Everything past here are functions that operate the firmware. There is nothing to be customized by the user for encoder modes or keyboard keymap.
*/

/* ---------------------------------------------- SET INDICATOR COLOR FUNCTION
This is the function used when the RGB colors need to change.
*/
void set_indicator_colors(const color target_color){
	rgblight_sethsv(target_color[0],target_color[1],target_color[2]);
};

// Board init: RGB indicator is set to the first encoder mode color, also encoder mode is set to first mode.
void keyboard_pre_init_user(void){
        set_indicator_colors(STARTUP_COLOR);
        encoder_mode_count = 0;
};

void keyboard_post_init_user(void){
	set_indicator_colors(encoder_modes[0].indicator_color);
};

/* ---------------------------------------------- SPECIAL KEYCODE PROCESSING
	The heart of this firmware is the process_custom_keycode function; this allows all the customized keycodes ENCMUP, ENCMDN, ALTTABN, ALLTABP and so on to be used in any place including the encoder callback. Its main mechanic is calling the process_record_user function, where there is a function for each one of the customized keycodes.
	What process_custom_keycode does is, if a "normal" keycode is passed on, then it is registered and held for a small period of time (MEDIA_KEY_DELAY to be more specific). This "holding" allows it to correctly register media keys. However, if a custom keycode is used, then the function executes process_record_user again, but now with a new argument keycode that will be whatever is mapped inside the special key requested.
	Admittedly, this implementation looks redundant: process_record_user calls process_custom_keycode which calls process_record_user again. However, the ingenuity of this recursion is this allows any of the custom keycodes to be mappable both to encoder action as well as keys by having their behavior mapped to a single function in a switch-case structure. For instance, by having the encoder update function encoder_update_user use process_custom_keycode, the code for each custom keycode can be present in a single place in the code, that is, in process_record_user. On another hand, if the user wants to map a certain special keycode to a particular key, they can do so; for instance, if the user wants to map the encoder mode switch keys ENCMUP/ENCMDN to, say, left and right keys of layer 1, they can also do so.
	The glaring problem with this approach is the same as with all recursions: a recursion mapped to itself is a loop, meaning that it is very easy to put the program in a loop within process_record_user by nesting the custom keycodes, for instance, using the keycode ENCNTH in a north key in any of the modes. This then requires a certain care from whoever is adapting or customizing their encoder modes to not use ENCNTH, ENCSTH, ENCWST, ENCEST in the keymap or the encoder modes. The way the firmware deals with this is by only processing keycodes inside the 0x5F85 and 0x5F89 range which exclude these keys; if the given keycode is in the 0x5F80 to 0x5F84 range, which pertains to these forbidden keycodes, nothing is done; to the user it will seem like nothing happens.
	In the case of the encoder rotating action, in order to call process_record_user a placeholder record is used, the idea being to use values not obtainable phisically on the keyboard like col 20, row 20, with a timer right at the begginig of the code initialization.
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}

Despite this long description, process_custom_kc is fairly simple. It tests the passed keycode and, if it is one of the custom-defined keys in the forbidden range, nothing is done; if it's one of the good ones, process_record_user is called and the function for that particular keycode will be executed. In other cases, if the event was a press the keycode is registered and held for MEDIA_KEY_DELAY ms. In the case the event was a release, the keycode is unregistered.
*/

keyrecord_t placeholder_record ;
//placeholder_record->event.key.col = 20;
//placeholder_record.event.key.row = 20;
//placeholder_record.event.time = timer_read32();

uint16_t mapped_code = 0;
uint32_t held_keycode_timer = 0;
void process_custom_keycode(uint16_t keycode, keyrecord_t *record){
	if (keycode >= 0x05F80 && keycode < 0x5F85) ;
	else if (keycode >= 0x5F85 && keycode <= 0x5F89) process_record_user(keycode, record);
	else {
		// Note: (un)register_keycode16 need to be the 16 bit versions in case modifier keys like C(), G() and so on are used. This is specially true for the "application control" encoder mode.
		if (record->event.pressed){
			register_code16(keycode);
			held_keycode_timer = timer_read32();
			while (timer_elapsed32(held_keycode_timer) < MEDIA_KEY_DELAY);
		} else unregister_code16(keycode);
	}
}

// Basically calls process_custom_keycode in a press event and then in a release event. This is basically done to tap custom keycodes.
void tap_custom_keycode(uint16_t keycode){
	placeholder_record.event.pressed = true;
	process_custom_keycode(keycode, &placeholder_record);
	placeholder_record.event.pressed = false;
	process_custom_keycode(keycode, &placeholder_record);
}

/* ---------------------------------------------- LAYER UPDATING
Keeps track of the highest active layer.
*/
int current_layer = 0 ; // Updated in layer_state_set_user each time a layer change is made
layer_state_t layer_state_set_user(layer_state_t state) {
	current_layer = get_highest_layer(state);
	return state;
}

/* ---------------------------------------------- ENCODER MDOE CYCLING
Pretty straightforward: cycles encoder mode forwards if passed a true value and backwards otherwise.

Some care is taken for two edge cases:
	- The user is at mode 0 and the encoder mode is changed backwards
	- The user is at the last mode and changes it forward.

The program deals with this last case by taking the division remainder, which will take encoder_mode_count to 0. For the first case, encoder_mode_count is just made equal to the last (highest) mode.
*/
void cycle_encoder_mode(bool forward){
	forward ? encoder_mode_count++ : encoder_mode_count-- ;
	if (encoder_mode_count == -1) encoder_mode_count = NUM_ENCODER_MODES - 1;
	encoder_mode_count = encoder_mode_count%NUM_ENCODER_MODES ; // This makes sure encoder_mode_count keeps cycling between 0,1,...,NUM_ENCODER_MODES and doesnt eventually overflow
	set_indicator_colors( encoder_modes[ encoder_mode_count ].indicator_color ); // Set indicator color to the corresponding defined color
}

/* ---------------------------------------------- PROCESSING ALT-TABBING
This function process the alt-tabbing keycode ALTTABS. The process works in a few steps:
- At first, the flag is_alt_tab_active is false. When the user first uses this keycode (rotating the encoder, for instance) then the function turns the flag and "presses" left alt (KC_LALT), also triggering a timer alt_tab_timer.
- The alt_tab_timer is supposed to keep track of how many miliseconds the alt-tab window should be kept, that is, how much time the LALT keycode should be held. The objective being, once the user cycles through the applications to the desired one, they select it either by not rotating the applications anymore or clicking the encoder.
- Finally, the function shoots out the KC_TAB keycode if the encoder was rotated clockwise or the S(KC_TAB) (shift + tab) if the encoder was rotated counterclockwise.
- If the user cycles the encoder still while alt-tab is active, then the function refreshes the timer and shoots out tab or shift+tab.
- The function that keeps track of the timer expiration is housekeeping_task_user, where if the alt_tab_timer surpasses the defined ALT_TAB_DELAY macro (defaults to 2 seconds or 2000 ms) then the release_alt_tab function is called: the LALT keycode is released and the is_alt_tab_active flag is set to false again
- The release_alt_tab function is also called when the ALTTABC keycode is hit, thus selecting the desired application.
*/

// This bool records if LALT is pressed or not. Due to the automatic disabling of the ALT-TAB of the ALTTABS custom keystroke, the automatic disabling can un-register KC_LALT even when the LALT key is phisically pressed. Hence there needs to be two bools: one that keebs track of the ALT-TAB activity and one that keeps track of LALT so that the automatic disabling will not disable LALT if it is phisically pressed.
bool is_lalt_pressed = false;
bool is_alt_tab_active = false; // Flag to check if alt tab is active
uint32_t alt_tab_timer = 0;     // Time trigger for alt tab
void process_alt_tabbing(bool next){
	if(!is_alt_tab_active) {
		is_alt_tab_active = true;
		register_code(KC_LALT);
		}
	alt_tab_timer = timer_read32();
	tap_code16(next ? KC_TAB : S(KC_TAB));
}

void release_alt_tab(void){
	is_alt_tab_active = false;
	unregister_code(KC_LALT);
}

/* ---------------------------------------------- ENCODER UPDATE CALLBACK
This taps the keycode stored in the encoder mode struct, at the current encoder mode, at the current layer. Because the user can use non-QMK-native keycodes in the encoder, like the alt-tabbing keycodes like ALTTABP and ATLTTABN, the tap function is the custom tap one.
*/

bool encoder_update_user(uint8_t index, bool clockwise) {
	mapped_code = clockwise ? encoder_modes[ encoder_mode_count ].clockwise_key[ current_layer ] : encoder_modes[ encoder_mode_count ].counterclockwise_key[ current_layer ] ; // mapped code is the clockwise key if a clockwise motion is sensed, otherwise it registers the counterclockwise key
	tap_custom_keycode(mapped_code);
	return false; 	// This function needs to return false in order to inhibit the action of encoder_update_user as defined in evolv.c
}

/* ---------------------------------------------- DEALING WITH THE ENCODER CLICK
The encoder used in the Evolv has a construction particularity in that not only it has rotation and clicking but also directional joystic capabilities in the four cardinal directions, as in, it can also register four directions. The way that this works is, there are A,B and a common pin for the encoder rotation , with a PUSH and a COM pin. The encoder pins work pretty much like common encoders, as does the switch click: once you click it, PUSH and COM short-circuit, so the pushing mechanic can be easily integrated into a switch matrix and treated like a switch would.

The problem, however, lies in the directionals. For each directional, say N,S,W,E, there is a corresponding pin on the encoder; once one directional is hit its pin is shorted with PUSH and COM. This means that the directionals can be treated as four short-circuit keys and integrated into the matrix, but with the added hassle that every time one of them is registered, the encoder push is also registered.

The way this firmware deals with this problem is threefold.

- First, there is a is_click_blocked flag that is set true whenever one of the directionals is sensed by the matrix; the name suggests that in this case the click keycode processing should be "blocked". This allows the firmware to differentiate between an event where a directional was hit (the encoder push is recognized but is_click_blocked is true) and an event where only the push was used (is_click_blocked is false albeit the push being sensed).
- Second, in order to prevent the encoder push key from registering before the flag is set, a 20ms delay takes place when the encoder click was sensed; this means that when a directional is hit, the encoder action is guaranteed to be processed only after the is_click_blocked flag is true.
- Finally, held_click_timer and is_click_held are used to differentiate between a click short push and a long push; when a directional key is hit, is_click_held is immediately reset, further preventing any action corresponding to the encoder push click being held down.

automatic_encoder_mode_cycle is a flag used by the housekeeping function to communicate an encoder mode change was made during an encoder push, meaning that the user has held the encoder enough to trigger an encoder mode change. What the housekeeping function does is constantly monitor the timer so that, when it extrapolates the designated ENCODER_CLICK_DELAY, a mode change takes place; the held_click_timer timer is refreshed. The problem is that, once the user reaches their desired mode and releases the encoder, the timer had been refreshed and is lower than the designated delay, which would cause the "fast click" keycode to be triggered, which is of course unwanted. Hence the algorithm filters out these situations by knowing when the automatic mode change has taken place and not registering the click key, only resetting the automatic_encoder_mode_cycle flag.

Finally, the process_encoder_click function has two parts. In a click press event, it sets the flag is_click_held and triggers a timer. When the encoder push is released, the timer is sampled and the pertinent action is taken depending on how much time the encoder was held for.
*/

uint32_t held_click_timer = 0;
bool is_click_held = false;
bool is_shift_held = false;
bool automatic_encoder_mode_cycle = false; // This flag registers if the encoder mode was automatically cycled 
bool is_click_blocked = false;
void process_encoder_click(bool clickpress){
	// What to do when the encoder is pressed: turn the flag to true, start (or refresh) timer
	if (clickpress) { 
		is_click_held = true;
		held_click_timer = timer_read32();
	} else { // What to do when encoder is released
		is_click_held = false;
		// Checking if the time the encoder click was held was smaller than the delay defined and if an automatic mode change was not already performed. If it was, just register whatever it is the click does.
		if (timer_elapsed32(held_click_timer) < ENCODER_CLICK_DELAY && !automatic_encoder_mode_cycle ) tap_custom_keycode(encoder_modes[ encoder_mode_count ].clicked_key[ current_layer ]);
		automatic_encoder_mode_cycle = false;
	}
}

bool process_directional(uint16_t keycode, keyrecord_t *record){
	is_click_held = false;
	is_click_blocked = record->event.pressed ;
	process_custom_keycode( keycode , record );
	return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case KC_LSFT:
		case KC_RSFT:
			is_shift_held = record->event.pressed;
			break;
		case KC_LALT: // If this is not defined, if the encoder is activated in the alt-tab mode while the LALT key is pressed, the menu goes away.
			is_lalt_pressed = record->event.pressed;				
			break;
// ---------------------------------------------- CUSTOM KEYCODES: they do their thing and retun false right away to prevent any further action
// --------------------- Encoder directionals (note: process_directional always returns false)
		case ENCNTH: return process_directional( encoder_modes[ encoder_mode_count ].north_key[ current_layer ] , record);
		case ENCSTH: return process_directional( encoder_modes[ encoder_mode_count ].south_key[ current_layer ] , record);
		case ENCEST: return process_directional( encoder_modes[ encoder_mode_count ].east_key[ current_layer ] , record);
		case ENCWST: return process_directional( encoder_modes[ encoder_mode_count ].west_key[ current_layer ] , record);
// --------------------- Encoder click
		case ENCCLK:
			held_keycode_timer = timer_read32();
			while (timer_elapsed32(held_keycode_timer) < 20);
			if(!is_click_blocked) process_encoder_click(record->event.pressed);
			return false; // Skip all further processing of this key
// --------------------- Alt-tabbing
		case ALTTABN:
		case ALTTABP:
			if(record->event.pressed) process_alt_tabbing(keycode == ALTTABN); // alt-tabs forward if the keycode is ALTTABN, else alt-tabs backwards if it's ALTTABP
			return false;
		case ALTTABC:
			if(record->event.pressed) release_alt_tab();
			return false;
// --------------------- Encoder mode up/down
		case ENCMUP:
		case ENCMDN:
			if(record->event.pressed) cycle_encoder_mode(keycode == ENCMUP); // Cycles encoder mode up if keycode is ENCMUP, else cycles backwards if the keycode is ENCMDN
			return false;
// ---------------------------------------------- DEFAULT
		default:
			return true;
	}
	return true;
}

/* ---------------------------------------------- HOUSEKEEPING
Housekeeping keeps track of three events:
- Keeps track of the alt-tabbing timer. If it surpasses ALT_TAB_DELAY the release_alt_tab function is called;
- Keeps track of the encoder click hold timer; if the encoder click is held for more than a certain delay, cycles encoder mode and sets the automatic_mode_change flag.
- The is_click_blocked flag marks if the encoder click has been registered with a directional key (recall that in this encoder, when a directional key is hit, both the directional key and the encoder push key are triggered in the keymap). In this case, only the directional should be registered. Hence, this housekeeping function resets the held_click_timer timer because, if this is not done, if the directional key is held for more than ENCODER_CLICK_DELAY then this will trigger an automatic mode change.
*/
void housekeeping_task_user(void) {
	if (is_alt_tab_active){ 
		if (is_lalt_pressed) alt_tab_timer = timer_read32(); // If the user is holding the LALT key, refresh the timer
		else if (timer_elapsed32(alt_tab_timer) > ALT_TAB_DELAY) release_alt_tab(); // If the timer surpasses the delay, release alt tab
	}
	if (is_click_blocked) held_click_timer = timer_read32(); // To prevent mode changing when directionals are held
	if (is_click_held && timer_elapsed32(held_click_timer) > ENCODER_CLICK_DELAY ){
		automatic_encoder_mode_cycle = true;
		held_click_timer = timer_read32();
		if (is_shift_held) cycle_encoder_mode(false);
		else cycle_encoder_mode(true);
	}
}
