#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _SYMB 1
#define _NAV 2
#define _INTER 3
#define _ADJUST 4

enum custom_keycodes {
	COLEMAK = SAFE_RANGE,
	SYMB,
	NAV,
	INTER,
	ADJUST,
	// These use process_record_user()
	M_BRACKET_LEFT,
	M_BRACKET_RIGHT,
	SHRUG,
	WAVE,
	YOSHI,
	THUMB_UP,
	NBSP
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Make macros a bit simpler with this shortcut.
#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

// Is shift being held? Let's store this in a bool.
static bool shift_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case SHRUG:
			if (record->event.pressed) {
				unicode_input_start(); register_hex(0xaf); unicode_input_finish();
				TAP_ONCE (KC_BSLS);
				register_code (KC_RSFT); TAP_ONCE (KC_MINS); TAP_ONCE (KC_9); unregister_code (KC_RSFT);
				unicode_input_start (); register_hex(0x30c4); unicode_input_finish();
				register_code (KC_RSFT); TAP_ONCE (KC_0); TAP_ONCE (KC_MINS); unregister_code (KC_RSFT);
				TAP_ONCE (KC_SLSH);
				unicode_input_start (); register_hex(0xaf); unicode_input_finish();
			}
			return false;
			break;
		case YOSHI:
			if (record->event.pressed) {
				SEND_STRING(":yellow_yoshi:");
			}
			return false;
			break;
		case THUMB_UP:
			if (record->event.pressed) {
				SEND_STRING(SS_LALT("D83D+DC4D"));
			}
			return false;
			break;
		case WAVE:
			if (record->event.pressed) {
				SEND_STRING(SS_LALT("D83D+DC4B"));
			}
			return false;
			break;
		case NBSP:
			if (record->event.pressed) {
				SEND_STRING("&nbsp;");
			}
			return false;
			break;
	case KC_LSFT:
		shift_held = record->event.pressed;
		return true;
		break;
	case KC_RSFT:
		shift_held = record->event.pressed;
		return true;
		break;
		case M_BRACKET_LEFT: {
			if (record->event.pressed) {
				if (shift_held) {
					unregister_code(KC_LSFT);
					unregister_code(KC_RSFT);
					register_code(KC_LBRC);
				} else {
					register_code(KC_LSFT);
					register_code(KC_9);
				}
			} else { // Release the key
				unregister_code(KC_LBRC);
				unregister_code(KC_LSFT);
				unregister_code(KC_RSFT);
				unregister_code(KC_9);
			}
			return false;
			break;
		}
		case M_BRACKET_RIGHT: {
			if (record->event.pressed) {
				if (shift_held) {
					unregister_code(KC_LSFT);
					unregister_code(KC_RSFT);
					register_code(KC_RBRC);
				} else {
					register_code(KC_LSFT);
					register_code(KC_0);
				}
			} else { // Release the key
				unregister_code(KC_RBRC);
				unregister_code(KC_LSFT);
				unregister_code(KC_RSFT);
				unregister_code(KC_0);
			}
			return false;
			break;
		}
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * ,------------------------------------------------.            ,------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  | Esc  |            | Exp  |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |  (   |            |   )  |   J  |   L  |   U  |   Y  |   ;  |   \  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Lay1 |   A  |   R  |   S  |   T  |   D  | Lay2 |            | Lay2 |   H  |   N  |   E  |   I  |   O  |'/Lay1|
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | Lay1 |            | Lay1 |   K  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Lay3 | Ctrl | Hyper|  Alt | Cmd  |Bcksp | Ctrl |            |Enter |Space | Cmd  | Lay4 | Hyper| Ctrl | Lay3 |
 * `------------------------------------------------'            `------------------------------------------------'
 */
  [_COLEMAK] = LAYOUT(
  //,----+----+----+----+----+----+----.                                                         ,----+----+----+----+----+----+----.
	 KC_GRV     , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,KC_ESC,                           LCTL(KC_DOWN), KC_6  , KC_7 ,   KC_8   , KC_9   , KC_0    , KC_EQL,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
	 KC_TAB     , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  , M_BRACKET_LEFT,               M_BRACKET_RIGHT , KC_J  , KC_L  ,   KC_U  , KC_Y   , KC_SCLN , KC_BSLS,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
	 MO(_SYMB)  , KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,TT(_NAV),                        TT(_NAV)    , KC_H  , KC_N  ,   KC_E  , KC_I   , KC_O    , LT(_SYMB,KC_QUOT),
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
	 KC_LSFT    , KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,TT(_SYMB),                       TT(_SYMB)   , KC_K  , KC_M  , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
	 MO(_INTER),KC_LCTL,KC_HYPR,KC_LALT,   KC_LCMD,   KC_BSPC,KC_LCTL,               KC_ENT,KC_SPC     ,    KC_RCMD    , TT(_ADJUST),KC_HYPR,KC_RCTL,MO(_INTER)
  //`----+----+----+----+----+----+----'                                                         `----+----+----+----+----+----+----'
  ),

/* Symbols
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |      |      |      |   6  |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |      |      |      |   ^  |   &  |   *  |   -  |   _  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */

  [_SYMB] = LAYOUT(
	_______, _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
	_______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_LCBR,                             KC_RCBR, KC_6   , KC_7   ,   KC_8 , KC_9   , KC_0   , _______,
	_______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,                             _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_UNDS, _______,
	_______, _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, _______
  ),

/* Navigation
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |VOLDOW|VOL UP| MUTE |      |      |      | LEFT | DOWN |  UP  |RIGHT |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_NAV] = LAYOUT(
	_______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, _______,                            _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______
  ),

/* i18n + emoji
* ,------------------------------------------------.      ,------------------------------------------------.
* |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
* |      |  à   | 👋   |      |      |      |      |      |      |      |  ü   |  è   | YOSHI|   ö  |      |
* |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
* |      |  á   |      |SHRUG |  👍  |      |      |      |      |      |   ú  |   é  |   í  |   ó  |      |
* |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
* |      |  â   |      |  ç   |      |      |      |      |      |      |   ű  |   ê  |      |  ő   |      |
* |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
* `------------------------------------------------'      `------------------------------------------------'
*/
  [_INTER] = LAYOUT(
	XXXXXXX, _______   , _______, _______   , _______ , _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
	XXXXXXX, UC(0x00E0), WAVE   , XXXXXXX   , XXXXXXX , XXXXXXX, _______,                            _______, XXXXXXX, UC(0x00FC), UC(0x00E8), YOSHI, UC(0x00F6), XXXXXXX,
	_______, UC(0x00E1), XXXXXXX, SHRUG     , THUMB_UP, XXXXXXX, _______,                            _______, XXXXXXX, UC(0x00F9), UC(0x00E9), UC(0x00ED)  , UC(0x00F3), _______,
	XXXXXXX, UC(0x00E2), XXXXXXX, UC(0x00E7), XXXXXXX , XXXXXXX, _______,                            _______, XXXXXXX, UC(0x0171), UC(0x00EA), XXXXXXX, UC(0x0151), XXXXXXX,
	_______, XXXXXXX   , XXXXXXX, XXXXXXX   , XXXXXXX , XXXXXXX, _______,                            _______, NBSP, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______
  ),

/* Adjust keyboard settings
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      | RGB- | RGB+ |RGB ON|      |      |      |      |      | RESET| DEBUG|AUD ON|      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_ADJUST] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	_______, XXXXXXX, RGB_VAD, RGB_VAI, RGB_TOG, XXXXXXX, _______,                            _______, XXXXXXX, RESET  , DEBUG  , AU_TOG , XXXXXXX, _______,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______
  )

};

#ifdef AUDIO_ENABLE
float tone_colemak[][2]     = SONG(ZELDA_TREASURE);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
	eeconfig_update_default_layer(default_layer);
	default_layer_set(default_layer);
}

// Set unicode in Mac OS.
void matrix_init_user(void) {
	set_unicode_input_mode(UC_OSX);
};

// Change LED colors depending on the layer.
uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(state)) {
		case _SYMB:
			rgblight_setrgb_orange();
			break;
		case _NAV:
			rgblight_setrgb_springgreen();
			break;
		case _INTER:
			rgblight_setrgb_teal();
			break;
		case _ADJUST:
			rgblight_setrgb_red();
			break;
		default: //  for any other layers, or the default layer
			rgblight_setrgb_yellow();
			break;
	}
	return state;
};
