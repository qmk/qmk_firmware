#include QMK_KEYBOARD_H
#include "muse.h"
#include "eeprom.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
/* #include "keymap_br_abnt2.h" */
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define NO_TH ALGR(KC_T)
#define NO_ETH ALGR(KC_D)

#define _____ KC_TRANSPARENT

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

// Okay.  Issue:  EZ keyboard code has hardcoded layers 3 and 4 as lower and raise,
// and 6 as adjust.  Weird?  That was causing some LED lighting issues, so I've
// disabled it inside the EZ driver so that I can control the LEDs myself.

#define COLEMAK_LAYER

enum planck_layers {
	_QWERTY,
#ifdef COLEMAK_LAYER
	_COLEMAK,
#endif
	_LOWER,
	_RAISE,
	_ADJUST,
};

enum planck_keycodes {
	RGB_SLD = SAFE_RANGE,
	TOGGLE_LAYER_COLOR,
	EPRM,
#ifdef COLEMAK_LAYER
	QWERTY,
	COLEMAK,
#endif
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define RAISEGUI LM(_RAISE,MOD_LGUI)
#define CTL_ESC LCTL_T(KC_ESCAPE) // tap-escape hold-lctrl
#define RSHFT_ENTER RSFT_T(KC_ENTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Qwerty
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |  Ctl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SH/En |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | HYPR | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_QWERTY] = LAYOUT_planck_grid(
			KC_TAB   ,KC_Q    ,KC_W   ,KC_E   ,KC_R ,KC_T    ,KC_Y ,KC_U ,KC_I    ,KC_O   ,KC_P     ,KC_BSPACE       ,
			CTL_ESC  ,KC_A    ,KC_S   ,KC_D   ,KC_F ,KC_G    ,KC_H ,KC_J ,KC_K    ,KC_L   ,KC_SCOLON,KC_QUOTE        ,
			/* KC_LCTL  ,KC_A    ,KC_S   ,KC_D   ,KC_F ,KC_G    ,KC_H ,KC_J ,KC_K    ,KC_L   ,KC_SCOLON,KC_QUOTE        , */
			KC_LSHIFT,KC_Z    ,KC_X   ,KC_C   ,KC_V ,KC_B    ,KC_N ,KC_M ,KC_COMMA,KC_DOT ,KC_SLASH ,RSHFT_ENTER     ,
			/* TD_SHIFT_CAPSLOCK,KC_Z    ,KC_X   ,KC_C   ,KC_V ,KC_B    ,KC_N ,KC_M ,KC_COMMA,KC_DOT ,KC_SLASH ,RSHFT_ENTER     , */
			/* RAISEGUI   ,KC_LCTRL,KC_LALT,KC_LGUI,LOWER,KC_SPACE,KC_NO,RAISE,KC_LEFT ,KC_DOWN,KC_UP    ,KC_RIGHT */
			KC_HYPR ,KC_ESC  ,KC_LALT,KC_LGUI,LOWER,KC_SPACE,KC_NO,RAISE,KC_LEFT ,KC_DOWN,KC_UP    ,KC_RIGHT
			),

	/* Lower
	 * ,-----------------------------------------------------------------------------------.
	 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Caps |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_LOWER] = LAYOUT_planck_grid(
			KC_TILD  ,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,KC_CIRC,KC_AMPR      ,KC_ASTR            ,KC_LPRN          ,KC_RPRN        ,_____  ,
			KC_ESC   ,KC_F1  ,KC_F2,KC_F3  ,KC_F4 ,KC_F5  ,KC_F6  ,KC_UNDS      ,KC_PLUS            ,KC_LCBR          ,KC_RCBR        ,KC_PIPE,
			KC_CAPS  ,KC_F7  ,KC_F8,KC_F9  ,KC_F10,KC_F11 ,KC_F12 ,KC_NONUS_HASH,KC_NONUS_BSLASH    ,KC_HOME          ,KC_END         ,KC_ENTER,
			_____    ,_____  ,_____,_____  ,_____ ,_____  ,KC_NO  ,_____        ,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE
			),

	/* Raise
	 * ,-----------------------------------------------------------------------------------.
	 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_RAISE] = LAYOUT_planck_grid(
			KC_GRAVE ,KC_1 ,KC_2 ,KC_3 ,KC_4  ,KC_5  ,KC_6  ,KC_7         ,KC_8               ,KC_9             ,KC_0           ,_____    ,
			KC_DELETE,KC_F1,KC_F2,KC_F3,KC_F4 ,KC_F5 ,KC_F6 ,KC_MINUS     ,KC_EQUAL           ,KC_LBRACKET      ,KC_RBRACKET    ,KC_BSLASH,
			_____    ,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_NONUS_HASH,KC_NONUS_BSLASH    ,KC_PGUP          ,KC_PGDOWN      ,KC_ENTER    ,
			_____    ,_____,_____,_____,_____ ,_____ ,KC_NO ,_____        ,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE
			),

	/* Adjust (Lower + Raise)
	 * ,-----------------------------------------------------------------------------------.
	 * | QWERTY|     |      |      |      |      |      |      |      |      |      | COLEM|
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |      |Aud on|Audoff|AGtog |      |      |RGBTog|RGBva+|RGBva-|      | RESET|
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      |Mus on|Musoff|MusTog|      |      |RGBMod| Hue+ | Hue- |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |             |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_ADJUST] = LAYOUT_planck_grid(
#ifdef COLEMAK_LAYER
			QWERTY    ,_____,_____,_____ ,_____ ,_____,_____,_____  ,_____  ,_____  ,_____,COLEMAK,
#else
			_____    ,_____,_____,_____ ,_____ ,_____,_____,_____  ,_____  ,_____  ,_____,_____,
#endif
			KC_DELETE,_____,AU_ON,AU_OFF,AU_TOG,_____,_____,RGB_TOG,RGB_VAI,RGB_VAD,_____,RESET,
			_____    ,_____,MU_ON,MU_OFF,MU_TOG,_____,_____,RGB_MOD,RGB_HUI,RGB_HUD,_____,_____,
			_____    ,_____,_____,_____ ,_____ ,_____,KC_NO,_____  ,_____  ,_____  ,_____,EPRM
			),

#ifdef COLEMAK_LAYER
	/* Colemak
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Hypr | Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_COLEMAK] = LAYOUT_planck_grid(
			KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
			CTL_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
			KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSHFT_ENTER,
			KC_HYPR, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
			),
#endif
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case EPRM:
			if (record->event.pressed) {
				eeconfig_init();
			}
			return false;
		case RGB_SLD:
			if (record->event.pressed) {
				rgblight_mode(1);
			}
			return false;
#ifdef COLEMAK_LAYER
		case QWERTY:
			if (record->event.pressed) {
#ifdef AUDIO_ENABLE
				PLAY_SONG(tone_qwerty);
#endif
				/* persistent_default_layer_set(1UL<<_QWERTY); */
				default_layer_set(1UL<<_QWERTY);
			}
			return false;
			break;
		case COLEMAK:
			if (record->event.pressed) {
#ifdef AUDIO_ENABLE
				PLAY_SONG(tone_colemak);
#endif
				default_layer_set(1UL<<_COLEMAK);
				/* persistent_default_layer_set(1UL<<_COLEMAK); */
			}
			return false;
			break;
#endif // COLEMAK_LAYER
		case LOWER:
			if (record->event.pressed) {
				layer_on(_LOWER);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_LOWER);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
			break;
		case RAISE:
			if (record->event.pressed) {
				layer_on(_RAISE);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_RAISE);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
			break;
		case KC_SCOLON:
			if (record->event.pressed && get_mods() & MOD_BIT(KC_LCTL))
			{
				/* register_code(KC_LSHIFT); */
				tap_code(KC_ESC);
				/* unregister_code(KC_LSHIFT); */
				return false;
			}
			return true;
			break;
	}
	return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
	if (muse_mode) {
		if (IS_LAYER_ON(_RAISE)) {
			if (clockwise) {
				muse_offset++;
			} else {
				muse_offset--;
			}
		} else {
			if (clockwise) {
				muse_tempo+=1;
			} else {
				muse_tempo-=1;
			}
		}
	} else {
		if (clockwise) {
#ifdef MOUSEKEY_ENABLE
			register_code(KC_MS_WH_DOWN);
			unregister_code(KC_MS_WH_DOWN);
#else
			register_code(KC_PGDN);
			unregister_code(KC_PGDN);
#endif
		} else {
#ifdef MOUSEKEY_ENABLE
			register_code(KC_MS_WH_UP);
			unregister_code(KC_MS_WH_UP);
#else
			register_code(KC_PGUP);
			unregister_code(KC_PGUP);
#endif
		}
	}
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
	if (muse_mode) {
		if (muse_counter == 0) {
			uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
			if (muse_note != last_muse_note) {
				stop_note(compute_freq_for_midi_note(last_muse_note));
				play_note(compute_freq_for_midi_note(muse_note), 0xF);
				last_muse_note = muse_note;
			}
		}
		muse_counter = (muse_counter + 1) % muse_tempo;
	}
#endif
}

bool music_mask_user(uint16_t keycode) {
	switch (keycode) {
		case RAISE:
		case LOWER:
			return false;
		default:
			return true;
	}
}

uint32_t layer_state_set_user(uint32_t state) {
	return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

