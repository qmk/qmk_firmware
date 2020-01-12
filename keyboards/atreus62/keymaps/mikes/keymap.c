#include QMK_KEYBOARD_H

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum layers {
	_DEFAULT,
	_RAISE,
	_LOWER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Default
	 * ,-----------------------------------------.                ,-----------------------------------------.
	 * | Esc  |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  -   |
	 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
	 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |Enter |
	 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
	 * | Caps |   A  |   S  |   D  |   F  |   G  |,------.,------.|   H  |   J  |   K  |   L  |   ;  |  "   |
	 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
	 * |Shift |   Z  |   X  |   C  |   V  |   B  ||Lower ||Raise ||   N  |   M  |   ,  |   .  |   /  |Shift |
	 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
	 * | Ctrl | Alt  |PG DN |PG UP | Gui  | Bksp |`------'`------'|Space | Gui  | Left | Down | Up   |Right |
	 * `-----------------------------------------'                `-----------------------------------------'
	 */
	[_DEFAULT] = LAYOUT(
		KC_ESC,  KC_1,     KC_2,    KC_3,   KC_4,    KC_5,                       KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
		KC_TAB,  KC_Q,     KC_W,    KC_E,   KC_R,    KC_T,                       KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
		KC_HYPR, KC_A,     KC_S,    KC_D,   KC_F,    KC_G,                       KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
		KC_LSFT, KC_Z,     KC_X,    KC_C,   KC_V,    KC_B,                       KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		KC_LCTL, KC_LALT,  KC_PGDN,  KC_PGUP, KC_LGUI, KC_BSPC,   LOWER,   RAISE,  KC_SPC, KC_RGUI, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
	),
	/* Raise
	 * ,-----------------------------------------.                ,-----------------------------------------.
	 * |      |      |      |      |      |      |                |      |      |      |      |      | Del  |
	 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
	 * |      |      |      |      |      |      |                |      |      |      |      |      |  \   |
	 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
	 * |      |      |      |      |      |      |,------.,------.| Left | Down | Up   |Right |      |      |
	 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
	 * |Shift |      |      |      |      |      ||      ||      || Play | Mute | VolD | VolU | Last | Next |
	 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
	 * |      |      |      |      |      |      |`------'`------'|      |      |      |      |      |      |
	 * `-----------------------------------------'                `-----------------------------------------'
	 */
	[_RAISE] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
	),
	/* Lower
	 * ,-----------------------------------------.                ,-----------------------------------------.
	 * | F1   | F2   | F3   | F4   | F5   | F6   |                |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
	 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
	 * |   `  |      |      |   =  |      |      |                |      |      |      |      |      |      |
	 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
	 * |      |      |      |   {  |   [  |  (   |,------.,------.|   )  |   ]  |   }  |      |      |      |
	 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
	 * |      |      |      |      |      |      ||      ||      ||      |      |      |      |      |      |
	 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
	 * |Reset |      |      |      |      |      |`------'`------'|      |      |      |      |      |      |
	 * `-----------------------------------------'                `-----------------------------------------'
	 */
	[_LOWER] = LAYOUT(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,      KC_F10,  KC_F11,  KC_F12,
	    KC_GRV,  XXXXXXX, XXXXXXX, KC_EQL,     XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, S(KC_LBRC), KC_LBRC, S(KC_9),                   S(KC_0), KC_RBRC, S(KC_RBRC), XXXXXXX, XXXXXXX, XXXXXXX,
		_______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
		RESET,   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
	)
};

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
#endif
};
