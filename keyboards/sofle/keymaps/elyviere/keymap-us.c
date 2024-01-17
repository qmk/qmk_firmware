#include QMK_KEYBOARD_H
//#include "keymap_swedish.h"
//#include <stdio.h>
//#include <time.h>

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
	_COLEMAK,
    _PROGRAMMER_DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_COLEMAK,
	KC_P_DVORAK,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE
};

// A key replaced with '-------' represents a key identical to the base layer,
// whereas 'XXXXXXX' represents a key without value within that layer
#define L_RAISE MO(_RAISE)
#define L_LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |-<--->-.    ,-<--->-|   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|VOL -/+|    |SCROLL |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------|    |-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    | PLAY  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *           | LGUI | LAlt | LCtrl| / Enter / LOWER /      \ RAISE \ RAISE \ | Space| RAlt | RGUI |
 *           |      |      |      |/       /       /        \       \       \|      |      |      |
 *           `--------------------'-------'-------'          '-------'-------'--------------------'
 */

[_QWERTY] = LAYOUT(
   KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_GRV,
   KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
   KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_MPLY,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                    KC_LGUI, KC_LALT, KC_LCTL,  KC_ENT, L_LOWER,    L_RAISE, L_RAISE,  KC_SPC, KC_RALT, KC_RGUI
),
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |-<--->-.    ,-<--->-|   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|VOL -/+|    |SCROLL |------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |-------|    |-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    | PLAY  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *           | LGUI | LAlt | LCtrl| / Enter / LOWER /      \ RAISE \ RAISE \ | Space| RAlt | RGUI |
 *           |      |      |      |/       /       /        \       \       \|      |      |      |
 *            `-------------------'-------'-------'          '-------'-------'-------------------'
 */

[_COLEMAK] = LAYOUT(
   KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_GRV,
   KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC,
   KC_TAB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_MPLY,    KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                    KC_LGUI, KC_LALT, KC_LCTL,  KC_ENT, L_LOWER,    L_RAISE, L_RAISE,  KC_SPC, KC_RALT, KC_RGUI
),
/*
 * PROGRAMMER DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  $   |   &  |   [  |   {  |   }  |   (  |                    |   =  |   *  |   )  |   +  |   ]  |  !   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   ;  |   ,  |   .  |   P  |   Y  |-<--->-.    ,-<--->-|   F  |   G  |   C  |   R  |   L  | Bspc |
 * |------+------+------+------+------+------|VOL -/+|    |SCROLL |------+------+------+------+------+------|
 * | Tab  |   A  |   O  |   E  |   U  |   I  |-------|    |-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|  MUTE |    | PLAY  |------+------+------+------+------+------|
 * |LShift|   '  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *          |Compose| LAlt | LCtrl| / Enter / LOWER /      \ RAISE \ RAISE \ | Space| RAlt | RGUI |
 *          |       |      |      |/       /       /        \       \       \|      |      |      |
 *          `---------------------'-------'-------'          '-------'-------'-------------------'
 */

[_PROGRAMMER_DVORAK] = LAYOUT(
   KC_DLR, KC_AMPR, KC_LBRC, KC_LCBR, KC_RCBR, KC_LPRN,                       KC_EQL, KC_ASTR, KC_RPRN, KC_PLUS, KC_RBRC, KC_EXLM,
   KC_ESC, KC_SCLN, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC,
   KC_TAB,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
  KC_LSFT, KC_QUOT,    KC_Q,    KC_J,    KC_K,    KC_X, KC_MUTE,    KC_MPLY,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_RSFT,
                     KC_F13, KC_LALT, KC_LCTL,  KC_ENT, L_LOWER,    L_RAISE, L_RAISE,  KC_SPC, KC_RALT, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Tilde|   !  |   @  |   #  |      |-<--->-.    ,-<--->-|   *  |   1  |   2  |   3  |   #  |   @  |
 * |------+------+------+------+------+------|VOL -/+|    |SCROLL |------+------+------+------+------+------|
 * | Tab  |      |   $  |   %  |   ^  |      |-------|    |-------|   -  |   4  |   5  |   6  |   /  |   |  |
 * |------+------+------+------+------+------|  MUTE |    | PLAY  |------+------+------+------+------+------|
 * |LShift|   `  |   &  |   *  |   /  |      |-------|    |-------|   +  |   7  |   8  |   9  |   \  |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *           |      |      |      | /       /       /      \ ADJUST\ ADJUST\ |      |   0  |   .  |
 *           |      |      |      |/       /       /        \       \       \|      |      |      |
 *           `--------------------'-------'-------'          '-------''---------------------------'
 */
[_LOWER] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  _______, KC_TILD, KC_EXLM,   KC_AT, KC_HASH, XXXXXXX,                      KC_PAST,    KC_1,    KC_2,    KC_3, KC_HASH,   KC_AT,
  _______, XXXXXXX,  KC_DLR, KC_PERC, KC_CIRC, XXXXXXX,                      KC_PMNS,    KC_4,    KC_5,    KC_6, KC_PSLS, KC_PIPE,
  _______,  KC_GRV, KC_AMPR, KC_ASTR, KC_SLSH, XXXXXXX, KC_MUTE,    KC_MPLY, KC_PPLS,    KC_7,    KC_8,    KC_9, KC_BSLS, _______,
                    _______, _______, _______, _______, _______,    _______, _______, _______,    KC_0, KC_PDOT
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |-<--->-.    ,-<--->-|      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|VOL -/+|    |SCROLL |------+------+------+------+------+------|
 * | Tab  | LAlt | LCtl |LShift|      | Caps |-------|    |-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------| MUTE  |    | PLAY  |------+------+------+------+------+------|
 * |LShift| Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *          |       |      |      | /       / ADJUST/      \       \       \ |      |      |      |
 *          |       |      |      |/       /       /        \       \       \|      |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                       KC_PGUP,KC_PRVWD,   KC_UP,KC_NXTWD,KC_DLINE, KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  _______, KC_UNDO,   KC_CUT,  KC_COPY, KC_PASTE, XXXXXXX, KC_MUTE,     KC_MPLY, XXXXXXX,KC_LSTRT, XXXXXXX, KC_LEND, XXXXXXX, _______,
                       _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
),
/* ADJUST
 * ,-------------------------------------------.                    ,-----------------------------------------.
 * |       |      |      |       |      |      |                    |      |      |      |      |      |      |
 * |-------+------+------+-------+------+------|                    |------+------+------+------+------+------|
 * |QK_BOOT|      |QWERTY|COLEMAK|DVORAK|      |-<--->-.    ,-<--->-|      |      |      |      |      |      |
 * |-------+------+------+-------+------+------|VOL -/+|    |SCROLL |------+------+------+------+------+------|
 * |       |      |MACWIN|       |      |      |-------|    |-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |-------+------+------+-------+------+------|  MUTE |    | PLAY  |------+------+------+------+------+------|
 * |       |      |      |       |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-------------------------------------------/       /    \       \-----------------------------------------'
 *            |Compose| LAlt | LCtrl| / Enter / LOWER /      \ RAISE \ RAISE \ | Space| RAlt | RGUI |
 *            |       |      |      |/       /       /        \       \       \|      |      |      |
 *            `-------------------------------------'          '------''---------------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX ,  XXXXXXX ,    XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_PWR,
  QK_BOOT, XXXXXXX,KC_QWERTY,KC_COLEMAK,KC_P_DVORAK, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WAKE,
  XXXXXXX, XXXXXXX,  CG_TOGG,   XXXXXXX,    XXXXXXX, XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, KC_SLEP,
  XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                     _______,   _______,    _______, _______, _______,   _______, _______, _______, _______, _______
  )
};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t next_track_override = 
ko_make_with_layers_negmods_and_options(
		MOD_MASK_CTRL,       // Trigger modifiers: ctrl
		KC_MPLY,             // Trigger key: play/pause
		KC_MNXT,             // Replacement key
		~0,                  // Activate on all layers
		MOD_MASK_SA,         // Do not activate when shift or alt are pressed
		ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting ctrl

const key_override_t prev_track_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CS, KC_MPLY,
		KC_MPRV, ~0, MOD_MASK_ALT, ko_option_no_reregister_trigger);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
	&next_track_override,
	&prev_track_override,
	NULL // Null terminate the array of overrides!
};

#ifdef OLED_ENABLE

//#include "oled.c" //Stock OLED code
//Note that the keyboard animations below take a large amount of space!
//#include "bongocat.c" //OLED code for Bongocat, original code by foureight84.
#include "luna.c" //OLED code for Luna, original code by Hellsingcoder and adapted by Jackasaur.
//#include "snakey.c" //OLED code for Snakey, customized from Luna. If not used, do not use OLED_LOGO in config.h.
//#include "snakey_minimal.c" //OLED code for Snakey, without WPM/related animations to save space. If not used, do not use OLED_LOGO in config.h.

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
	return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined(KEYBOARD_PET) || defined(OLED_LOGO)
	if (record->event.pressed) { //OLED timeout code
		oled_timer = timer_read32();
	}
#endif
	switch (keycode) {
		case KC_QWERTY:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTY);
			}
			return false;
		case KC_COLEMAK:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_COLEMAK);
			}
			return false;
		case KC_P_DVORAK:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_PROGRAMMER_DVORAK);
			}
			return false;
		case KC_PRVWD:
			if (record->event.pressed) {
				if (keymap_config.swap_lctl_lgui) {
					register_mods(mod_config(MOD_LALT));
					register_code(KC_LEFT);
				} else {
					register_mods(mod_config(MOD_LCTL));
					register_code(KC_LEFT);
				}
			} else {
				if (keymap_config.swap_lctl_lgui) {
					unregister_mods(mod_config(MOD_LALT));
					unregister_code(KC_LEFT);
				} else {
					unregister_mods(mod_config(MOD_LCTL));
					unregister_code(KC_LEFT);
				}
			}
			break;
		case KC_NXTWD:
			if (record->event.pressed) {
				if (keymap_config.swap_lctl_lgui) {
					register_mods(mod_config(MOD_LALT));
					register_code(KC_RIGHT);
				} else {
					register_mods(mod_config(MOD_LCTL));
					register_code(KC_RIGHT);
				}
			} else {
				if (keymap_config.swap_lctl_lgui) {
					unregister_mods(mod_config(MOD_LALT));
					unregister_code(KC_RIGHT);
				} else {
					unregister_mods(mod_config(MOD_LCTL));
					unregister_code(KC_RIGHT);
				}
			}
			break;
		case KC_LSTRT:
			if (record->event.pressed) {
				if (keymap_config.swap_lctl_lgui) {
					//CMD-arrow on Mac, but we have CTL and GUI swapped
					register_mods(mod_config(MOD_LCTL));
					register_code(KC_LEFT);
				} else {
					register_code(KC_HOME);
				}
			} else {
				if (keymap_config.swap_lctl_lgui) {
					unregister_mods(mod_config(MOD_LCTL));
					unregister_code(KC_LEFT);
				} else {
					unregister_code(KC_HOME);
				}
			}
			break;
		case KC_LEND:
			if (record->event.pressed) {
				if (keymap_config.swap_lctl_lgui) {
					//CMD-arrow on Mac, but we have CTL and GUI swapped
					register_mods(mod_config(MOD_LCTL));
					register_code(KC_RIGHT);
				} else {
					register_code(KC_END);
				}
			} else {
				if (keymap_config.swap_lctl_lgui) {
					unregister_mods(mod_config(MOD_LCTL));
					unregister_code(KC_RIGHT);
				} else {
					unregister_code(KC_END);
				}
			}
			break;
		case KC_DLINE:
			if (record->event.pressed) {
				register_mods(mod_config(MOD_LCTL));
				register_code(KC_BSPC);
			} else {
				unregister_mods(mod_config(MOD_LCTL));
				unregister_code(KC_BSPC);
			}
			break;
		case KC_COPY:
			if (record->event.pressed) {
				register_mods(mod_config(MOD_LCTL));
				register_code(KC_C);
			} else {
				unregister_mods(mod_config(MOD_LCTL));
				unregister_code(KC_C);
			}
			return false;
		case KC_PASTE:
			if (record->event.pressed) {
				register_mods(mod_config(MOD_LCTL));
				register_code(KC_V);
			} else {
				unregister_mods(mod_config(MOD_LCTL));
				unregister_code(KC_V);
			}
			return false;
		case KC_CUT:
			if (record->event.pressed) {
				register_mods(mod_config(MOD_LCTL));
				register_code(KC_X);
			} else {
				unregister_mods(mod_config(MOD_LCTL));
				unregister_code(KC_X);
			}
			return false;
			break;
		case KC_UNDO:
			if (record->event.pressed) {
				register_mods(mod_config(MOD_LCTL));
				register_code(KC_Z);
			} else {
				unregister_mods(mod_config(MOD_LCTL));
				unregister_code(KC_Z);
			}
			return false;
		case KC_RSFT: //Shift Backspace to Delete Whole Word. Inspired by Hellsingcoder.
			//rshift_held = record->event.pressed;
			//held_shift = keycode;
#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
			if (record->event.pressed) {
				isBarking = true;
			} else {
				isBarking = false;
			}
#endif
			return true;
		case KC_LSFT:
			//lshift_held = record->event.pressed;
			//held_shift = keycode;
#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
			if (record->event.pressed) {
				isBarking = true;
			} else {
				isBarking = false;
			}
#endif
			return true;

#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
		case KC_LCTL:
		case KC_RCTL:
#ifndef SNEAK_DISABLE
			if (record->event.pressed) { //Pet sneaks when control held.
				isSneaking = true;
			} else {
				isSneaking = false;
			}
#endif
			return true;
		case KC_SPC:
			if (record->event.pressed) { //Pet jumps when enter is pressed.
				isJumping = true;
				showedJump = false;
			} else {
				isJumping = false;
			}
			return true;
#endif
	}

	return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) {
		if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	} else if (index == 1) {
		if (clockwise) {
			tap_code(KC_MS_WH_DOWN);
		} else {
			tap_code(KC_MS_WH_UP);
		}
	}
	return false;
}

#endif
