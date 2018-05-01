#include "dz60.h"

/* Features TODO:
 * Recordable macros
 * Lock key on one of the layer switchers? or far right, r4?
 * Meh/Hyper for fun
 *
 * Leader functions
 *
 */

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#undef KEYMAP
#define KEYMAP( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       \
	      K301, K302, K303, K304, K305, K306, K307, K308, K309, K310,       K312, K313, K314, \
	K400, K401,       K403,       K405,       K407, K408,       K410, K411, K412, K413, K414  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  KC_NO, K014 }, \
	{ K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
	{ K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO }, \
	{ KC_NO, K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  KC_NO, K312,  K313,  K314 }, \
	{ K400,  K401,  KC_NO, K403,  KC_NO, K405,  KC_NO, K407,  K408,  KC_NO, K410,  K411,  K412,  K413,  K414 }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Layer 0: basic qwerty */
	KEYMAP(
KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,     KC_9,     KC_0,            KC_MINS,  KC_EQL,   KC_BSPC,
KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,     KC_O,     KC_P,            KC_LBRC,  KC_RBRC,  KC_BSLS,
KC_LCTL,  KC_A,     KC_S,     KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,     KC_L,     KC_SCLN,         KC_QUOT,  KC_ENT,
KC_LSFT,  KC_Z,     KC_X,     KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT,   SFT_T(KC_SLSH),  KC_UP,    KC_HYPER,
KC_MEH,   KC_LALT,  KC_LGUI,  KC_SPC,  TG(2),  MO(1),  TG(3),  MO(4),  KC_LEFT,  KC_DOWN,  KC_RGHT
		),

	/* Layer 1: primary fn layer */
	KEYMAP(
KC_GRV,    KC_F1,    KC_F2,          KC_F3,                KC_F4,            KC_F5,     KC_F6,     KC_F7,     KC_F8,    KC_F9,     KC_F10,     KC_F11,   KC_F12,   KC_DEL,
KC_TAB,    KC_NO,    KC_HOME,        KC_UP,                KC_END,           KC_NO,     KC_NO,     KC_PGDN,   KC_PGUP,  KC_NO,     KC_NO,      KC_NO,    KC_NO,    KC_NO,
KC_CAPS,   KC_NO,    KC_LEFT,        KC_DOWN,              KC_RIGHT,         KC_NO,     KC_LEFT,   KC_DOWN,   KC_UP,    KC_RIGHT,  KC_NO,      KC_NO,    KC_ENT,
KC_LSHFT,  KC_NO,    KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,    KC_AUDIO_VOL_UP,  KC_NO,     KC_NO,     KC_NO,     KC_NO,    KC_NO,     KC_RSHIFT,  KC_HOME,  KC_PGUP,
KC_MEH,    KC_LALT,  KC_LGUI,        KC_MEDIA_PLAY_PAUSE,  KC_TRANS,         KC_TRANS,  KC_TRANS,  KC_TRANS,  KC_DEL,   KC_END,    KC_PGDN
		),

	/* Layer 2: mouse navigation */
	KEYMAP(
KC_NO,  KC_MS_ACCEL0,  KC_MS_ACCEL1,  KC_MS_ACCEL2,  KC_NO,        KC_NO,     KC_NO,          KC_NO,          KC_NO,        KC_NO,           KC_NO,  KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,         KC_MS_BTN2,    KC_MS_UP,      KC_MS_BTN1,   KC_NO,     KC_NO,          KC_NO,          KC_PGDN,      KC_PGUP,         KC_NO,  KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_MS_BTN3,    KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_RIGHT,  KC_NO,     KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,  KC_MS_WH_RIGHT,  KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,        KC_NO,     KC_NO,          KC_NO,          KC_NO,        KC_NO,           KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,         KC_NO,         KC_MS_BTN1,    KC_TRANS,     KC_TRANS,  KC_TRANS,       KC_TRANS,       KC_NO,        KC_NO,           KC_NO
		),

	/* Layer 3: numpad */
	KEYMAP(
KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_NO,      KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_DOT,  KC_NO,  KC_NO,  KC_NO,
KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_KP_0,  KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO
		),
	/* Layer 4: right cluster modifiers */
};

enum function_id {
	SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
	[0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
	static uint8_t shift_esc_shift_mask;
	switch (id) {
		case SHIFT_ESC:
			shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
			if (record->event.pressed) {
				if (shift_esc_shift_mask) {
					add_key(KC_GRV);
					send_keyboard_report();
				} else {
					add_key(KC_ESC);
					send_keyboard_report();
				}
			} else {
				if (shift_esc_shift_mask) {
					del_key(KC_GRV);
					send_keyboard_report();
				} else {
					del_key(KC_ESC);
					send_keyboard_report();
				}
			}
			break;
	}
}

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRB |= (1 << 2); PORTB &= ~(1 << 2);
	} else {
		DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
	}
}
