#include "ymd96.h"
#include "action_layer.h"

/*
#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2*/
/*
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};*/

void matrix_scan_user(void) {
  // runs at every matrix scan.
}

enum {
  TD_H_E = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_H_E] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END)
};
#define ______ KC_TRNS
#define _DEFLT 0
#define _LOWER 1
#define _RAISE 2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	/* Layer 0, default layer
	*  | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |Print | Home | End  |Insert|Delete| PgUp | 19 keys
	*  |  ~`  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |    0 |    - |    = |    BkSpc    |NumLck|   /  |   *  | PgDn | 18 keys
	*  |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |    P |    { |    } |     \    |  7   |   8  |   9  |   -  | 18 keys
	*  |   Caps   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |    ; |   '  |     Return     |  4   |   5  |   6  |   +  | 17 keys
	*  |    LShft     |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |       RShft       |  1   |   2  |   3  |  En  | 16 keys
	*  | Ctrl  |  Win  |  Alt  |                  Space                      |  Fn  |  Win | Left | Down |  Up  | Right|   0  |   .  |      | 12 keys
	*/
	
    [_DEFLT] = KEYMAP(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_MAIL, KC_HOME,  KC_END, KC_INSERT, KC_DEL, \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS, \
    MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
    KC_LSFT, KC_SPC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_DEL,  KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
    KC_LCTL, KC_LGUI, KC_LALT,                            MO(1),                              KC_RALT, KC_RGUI, KC_RGUI, MO(1),   KC_RCTL, KC_P0,   KC_P0,   KC_PDOT, KC_PENT \
	),
	/* Layer 1, raise layer
	*  |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
	*  |      |      |      |      |      |      |      |      |      |      |      |      |      |             |      |      |      |      |
	*  |         |      |rgb_up|rgb_dn|rgb_mo|      |      |      |      |      |  F22 |  F23  |  F24 |         |      |      |      |      |
	*  |          |      |      |      |      |      |      |      |      |      |      |      |                |      |      |      |      |
	*  |              |      |      |      |      |      |      |      | VolDn| VolUp| Mute |     Play/Pause    |      |      |      |      |
	*  |       |       |       |                                             |      |      |MPrev |      |      | MNext|      |      |      |
	*/ 
	[_LOWER] = KEYMAP(
      RESET, RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLEP, KC_PWR, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_CALC, KC_HOME, KC_UP  , KC_END , KC_PGUP, KC_PSCR, _______, _______,          _______, _______, _______, _______, \
    _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_INS ,                   _______, _______, _______, _______, \
    _______, MO(2),   _______, _______, _______, _______, KC_MYCM, KC_APP,  _______, _______, _______, _______, KC_CAPS,          KC_ESC,  _______, _______, _______, _______, \
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______, _______ \
	),
	
		/* Layer 1, raise layer
	*  |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
	*  |      |      |      |      |      |      |      |      |      |      |      |      |      |             |      |      |      |      |
	*  |         |      |rgb_up|rgb_dn|rgb_mo|      |      |      |      |      |  F22 |  F23  |  F24 |         |      |      |      |      |
	*  |          |      |      |      |      |      |      |      |      |      |      |      |                |      |      |      |      |
	*  |              |      |      |      |      |      |      |      | VolDn| VolUp| Mute |     Play/Pause    |      |      |      |      |
	*  |       |       |       |                                             |      |      |MPrev |      |      | MNext|      |      |      |
	*/ 
	[_RAISE] = KEYMAP(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_PSLS, KC_7, 	KC_8, 	 KC_9,    KC_PMNS, KC_DEL,  _______, _______,          _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_PAST, KC_4, 	KC_5, 	 KC_6,    KC_PPLS, KC_ESC,  _______,                   _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_0,    KC_1, 	KC_2, 	 KC_3, 	  KC_DOT,  _______, _______,          _______, _______, _______, _______, _______, \
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______, _______ \
	),
};
