/*TO DO
* implement dragscroll trigger via numlock
* get into lighting layers to fix capsword led animation
*/

#include QMK_KEYBOARD_H

////DEFINITIONS////
//Layers:
enum layers {
	_QTY  = 0, //QwerTY
	_QTYe = 1, //Qwerty for monkytype emulation
	_CAD  = 2, //CAD mode
	_NUM  = 3, //NUMbers and symbols
	_RNUM = 4, //NUMpad Right hand only
	_MISC = 9, //MISCelaneous;
};

///Custom keycodes..
//Tap-hold keys:
#define EQL_RLT RALT_T(KC_EQL)
#define UND_SFT LSFT_T(KC_UNDS) //further defined in macro (because shifted keycodes in _T() is not possible)
#define FFF_NUM LT(_NUM, KC_F)
#define JJJ_NUM LT(_NUM, KC_J)
#define SPC_SFT LSFT_T(KC_SPC)
//Bottom row mods:
#define AAA_GUI LGUI_T(KC_A)
#define SSS_ALT LALT_T(KC_S)
#define DDD_CTL LCTL_T(KC_D)
//Oneshot Mods:
#define OSMLSFT OSM(MOD_LSFT)
#define OSMLCTL OSM(MOD_LCTL)
#define OSMLALT OSM(MOD_LALT)
#define OSMRALT OSM(MOD_RALT)
//Dead-hold keys:                //normal on tap, dead key on hold; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define DH_QUOT LT(11, KC_QUOT)  //further defined in macro
#define DH_DQOT LT(12, KC_QUOT)  //further defined in macro
#define DH_GRV  LT(11, KC_GRV)   //further defined in macro
#define DH_TILD LT(12, KC_TILD)  //further defined in macro
#define DH_CIRC LT(12, KC_CIRC)  //further defined in macro
//Other:
#define DOTCOMM LT(10, KC_DOT)   //KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
//Macros:
enum custom_keycodes {
		CLEARKB = SAFE_RANGE,   //clears all keys and/or layers that might be stuck
        EE_BOOT,                //clear eeprom, then boot mode
		CADTOGG,                //toggle CAD mode
		RNUMTOG,                //toggle RNUM layer
        QTYTOGG,                //toggle QTYe layer
};

//Combos:
#include "g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def

///..custom keycodes

///Keymaps..
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //Qwerty:
  [_QTY] = LAYOUT_split_3x5_3(
	  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
	  KC_A,    KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    DH_QUOT,
	  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
						KC_LALT, SPC_SFT, KC_LCTL,          KC_RALT, SPC_SFT, MO(_MISC)
  ),
  //Qwerty e: (unmodified qwerty layout for emulation in for example monkeytype)
  [_QTYe] = LAYOUT_split_3x5_3(
	  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
	  KC_A,    KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    KC_SCLN,
	  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
						KC_LALT, KC_LSFT, KC_LCTL,          KC_RALT, SPC_SFT, MO(_MISC)
  ),
  //CAD mode: (a mostly transparent layer, but will activate extra combos)
  [_CAD] = LAYOUT_split_3x5_3(
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
						_______, SPC_SFT, _______,          _______, _______, _______
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_split_3x5_3(
	  KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, DH_TILD,          DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
	  KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, DH_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
	  KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
						_______, UND_SFT, _______,          EQL_RLT, KC_0,    DOTCOMM
  ),
  [_RNUM] = LAYOUT_split_3x5_3(
	  _______, _______, _______, _______, _______,          DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
	  _______, _______, _______, _______, _______,          KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
	  _______, _______, _______, _______, _______,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
						_______, _______, _______,          EQL_RLT, KC_0,    DOTCOMM
  ),
  //OTHER:
  [_MISC] = LAYOUT_split_3x5_3(
	  QK_BOOT, XXXXXXX, EE_CLR,  XXXXXXX, XXXXXXX,          KC_PGUP, KC_BRIU, KC_INS,  KC_VOLU, KC_PSCR,
	  XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX,          KC_PGDN, KC_BRID, XXXXXXX,  KC_VOLD, XXXXXXX,
	  XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BRK,           KC_NUM,  KC_MENU, XXXXXXX, KC_MUTE, XXXXXXX,
						XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
};
///..keymaps

////LED INDICATORS////
/* LED numbering:
 * Left  hand LED = 0;
 * Right hand LED = 1;
*/
//rgb lighting variables:
int rgb_hue = 40; int rgb_sat = 255; int rgb_val = 255; int rgb_mode = 1; //initial values
int rgb_hue_q = 32;  //qwerty (yellow)
int rgb_hue_c = 60;  //CAD (lime)
int rgb_hue_n = 12;  //NUM (red/orange)
int rgb_hue_m = 185; //MISC (purple)
int rgb_hue_e = 165; //emulation (blue)

//animation speed:
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {2, 2, 2, 2};

//Set initial LED lighting state:
void matrix_init_user(void) {
	// initiate rgb underglow (default mode as per ASW_on true):
	rgblight_enable();
	rgblight_mode(rgb_mode);                                //set light effect for both LEDs
	rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);             //set HSV value for both LEDs
};

//Capsword indicator:
void caps_word_set_user(bool active) {
	if (active) {
		rgb_mode = 2;
		rgblight_mode(rgb_mode);
		if (IS_LAYER_ON(_RNUM)) {
			rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val); //override both LEDs, since can't override one when mode = 2;
		} else {
			rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
		}
	} else {
		rgb_mode = 1;
		rgblight_mode(rgb_mode);
		rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
		if (IS_LAYER_ON(_RNUM)) {
            rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val);
			rgblight_sethsv_at(rgb_hue, rgb_sat, rgb_val, 0);
		}
	}
};

//Layer indicators:
layer_state_t layer_state_set_user(layer_state_t state) {
	if (IS_LAYER_ON_STATE(state, _RNUM) && is_caps_word_on()) {
		rgblight_mode(rgb_mode);
		rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val); //override both LEDs, since can't override one when mode = 2;
	} else if (IS_LAYER_ON_STATE(state, _RNUM)) {
		if      (IS_LAYER_ON_STATE(state, _MISC)) {rgb_hue = rgb_hue_m;}
		else if (IS_LAYER_ON_STATE(state, _NUM))  {rgb_hue = rgb_hue_n;}
		else if (IS_LAYER_ON_STATE(state, _CAD))  {rgb_hue = rgb_hue_c;}
        else if (IS_LAYER_ON_STATE(state, _QTYe)) {rgb_hue = rgb_hue_e;}
		else                                      {rgb_hue = rgb_hue_q;}
		rgblight_mode(rgb_mode);
		rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val);
		rgblight_sethsv_at(rgb_hue, rgb_sat, rgb_val, 0);
	} else {
		if      (IS_LAYER_ON_STATE(state, _MISC)) {rgb_hue = rgb_hue_m;}
		else if (IS_LAYER_ON_STATE(state, _NUM))  {rgb_hue = rgb_hue_n;}
		else if (IS_LAYER_ON_STATE(state, _CAD))  {rgb_hue = rgb_hue_c;}
        else if (IS_LAYER_ON_STATE(state, _QTYe)) {rgb_hue = rgb_hue_e;}
		else                                      {rgb_hue = rgb_hue_q;}
		rgblight_mode(rgb_mode);
		rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
	}
	return state;
};

////CUSTOM KEY BEHAVIOURS////
//Turn on/off CAD combos:
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
	switch (combo_index) {
		case CAD_START ... CAD_FINAL:
			if (!IS_LAYER_ON(_CAD)) {
				return false;
			} return true;
	}
	return true;
};

//Tap-hold per key config:
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case UND_SFT:
			return 250;
		default:
			return TAPPING_TERM;
	}
};

///Customshift keycodes..
typedef struct _customshift_keycode_t { //define customshift functions
	uint16_t keycode_record;  //unmodified keycode
	uint16_t keycode_shifted; //alternate keycode to output on shift
} customshift_keycode_t;
#define KEY_MAP_SIZE 10 //amount of instances in customshift map
customshift_keycode_t keymap[KEY_MAP_SIZE] = { // customshift mapping, format: {keycode_record, keycode_shifted}
	//punctuation
	{KC_EXLM, KC_QUES},  {KC_COMM, KC_SCLN},  {KC_DOT,  S(KC_SCLN)}, // !?  ,;  .:
	//symbols
	{KC_SLSH, KC_BSLS},  {KC_PIPE, KC_BSLS},  {KC_DLR,  RALT(KC_5)}, // /\  |\  $€
	{KC_LCBR, KC_LBRC},  {KC_RCBR, KC_RBRC},  //brackets for qwertai
	//Volume and brightness
	{KC_VOLU, KC_BRIU},  {KC_VOLD, KC_BRID},
};
int get_index_customshift(uint16_t keycode_record) { //find corresponding item in customshift map for pressed key
	for (int i = 0; i < KEY_MAP_SIZE; i++) {
		if (keymap[i].keycode_record == keycode_record) return i;
	}
	return -1; //return -1 if pressed key is not in customshift map
};
///..customshift keycodes

///Macros..
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    //variables:
	int index = get_index_customshift(keycode);// check if keycode is in customshift map
	const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift state for customshift behaviours
	static bool dotcomm_state = true; //true = dot; false = comma;

    //macros:
	switch(keycode) {
		case CLEARKB: //clear keyboard
			if (record->event.pressed) {
				clear_keyboard(); //clears all keys and modifiers that might be stuck
				layer_clear();    //clears all layers that might be stuck
			} return false;
        case EE_BOOT: //clear eeprom and boot
            if (record->event.pressed) {
                eeconfig_init(); //clear eeprom
                wait_ms(10); //wait 10 ms
                reset_keyboard(); //enter bootmode
            } return false; //enter boot mode

        //layer toggles:
		case CADTOGG: //toggle CAD mode
			if(record->event.pressed) {
                layer_off(_RNUM);   //always turn off _RNUM when toggling CAD mode on/off
                layer_invert(_CAD); //toggle CAD mode on/off
			} return false;
		case RNUMTOG: //toggle numpad on/off (only right hand side)
			if(record->event.pressed) {
				layer_invert(_RNUM);
			} return false;
        case QTYTOGG: //toggle emulation mode (unmodified qwerty layout)
			if(record->event.pressed) {
				layer_invert(_QTYe);
			} return false;

        //special keycodes:
		case UND_SFT:
			if(record->event.pressed && record->tap.count) { //underscore when tapped
				tap_code16(S(KC_UNDS));
				return false;
			} return true; //shift when held
		case DOTCOMM:
			if (record->event.pressed && record->tap.count == 2) {//invert DOTCOMM state on double tap
				dotcomm_state = !dotcomm_state; //invert state
				tap_code16(KC_BSPC);            //remove character output from first tap
			} else if (record->event.pressed && dotcomm_state) {//when state is true
				if (mod_shift) { //send comm when shifted
					unregister_mods(mod_shift);
					tap_code16(KC_COMM);
					register_mods(mod_shift);
				} else { //send dot by default
					tap_code16(KC_DOT);
				}
			} else if (record->event.pressed) {//when state is false
				if (mod_shift) { //send dot when shifted
					unregister_mods(mod_shift);
					tap_code16(KC_DOT);
					register_mods(mod_shift);
				} else { //send comm by default
					tap_code16(KC_COMM);
				}
			} return false;

		//Dead-hold keys (acts like dead key when held), requires "English(US)"+"Qwerty US" language+kbd settings in windows:
		case DH_QUOT: //works for both ['] and ["] (except when ["] is accessed via combo, because then shift is not activated)
			if (record->event.pressed && record->tap.count) { //if tapped, behave as normal key
				tap_code16(KC_QUOT); tap_code16(KC_SPC);
			} else if (record->event.pressed) { //if held, behave as dead key
				tap_code16(KC_QUOT);
				if (mod_shift) {unregister_mods(mod_shift);} //unregister shift to resolve conflict of holding shifted dead key
			} return false;
		case DH_DQOT: //workaround for combo-["] on CAD layer
			if (record->event.pressed && record->tap.count) { //if tapped, behave as normal key
				tap_code16(S(KC_QUOT)); tap_code16(KC_SPC);
			} else if (record->event.pressed) { //if held, behave as dead key
				tap_code16(S(KC_QUOT));
			} return false;
		case DH_GRV:
			if (record->event.pressed && record->tap.count) {
				tap_code16(KC_GRV); tap_code16(KC_SPC);
			} else if (record->event.pressed) {
				tap_code16(KC_GRV); layer_off(_NUM);
			} return false;
		case DH_TILD:
			if (record->event.pressed && record->tap.count) {
				tap_code16(S(KC_GRV)); tap_code16(KC_SPC);
			} else if (record->event.pressed) {
				tap_code16(S(KC_GRV)); layer_off(_NUM);
			} return false;
		case DH_CIRC:
			if (record->event.pressed && record->tap.count) {
				tap_code16(S(KC_6)); tap_code16(KC_SPC);
			} else if (record->event.pressed) {
				tap_code16(S(KC_6)); layer_off(_NUM);
			} return false;

		default:
			//Customshift:
			if (index != -1) { //if key is in customshift map, then:
				if (record->event.pressed && mod_shift) { //shifted action
					unregister_mods(mod_shift);
					tap_code16(keymap[index].keycode_shifted); //custom shift key
					register_mods(mod_shift);
					return false; //ignore default shift behaviour
				} return true; //return as normal when not shifted
			}//end of if(index != -1)
	}//..switch(keycode)

	return true; //if key is not in customshift map or other macro, return normal key behaviour
};
///..Macros


