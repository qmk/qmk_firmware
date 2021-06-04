#include QMK_KEYBOARD_H

// [Tap Dance Functions] ---------------------------------------------------------------------------------------------------------------------//

// Tap Dance Enums Init
enum {
	OPQ = 0,
	CLQ,
	TDQ,
};

// Tap Dance Functions
void tri_open(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		tap_code16(KC_LPRN);
	} else if (state->count == 2) {
		tap_code(KC_LBRC);
	} else if (state->count == 3) {
		tap_code16(S(KC_LBRC));
	}
}

void tri_close(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		tap_code16(KC_RPRN);
	} else if (state->count == 2) {
		tap_code(KC_RBRC);
	} else if (state->count == 3) {
		tap_code16(S(KC_RBRC));
	}
}

void dquote(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted|state->pressed)
			tap_code(KC_QUOT);
		else
			tap_code16(KC_DQUO),
			tap_code(KC_SPC);
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[OPQ] = ACTION_TAP_DANCE_FN(tri_open),
	[CLQ] = ACTION_TAP_DANCE_FN(tri_close),
	[TDQ] = ACTION_TAP_DANCE_FN(dquote),
};

// [Layer Keymaps] ---------------------------------------------------------------------------------------------------------------------------//

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | App  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, TDQ,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LGUI, KC_LALT, KC_APP,  LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F0  |  F11 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   7  |   8  |   9  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | OPQ  |   4  |   5  |   6  |      |      |      |      |      |      |      | CLQ  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |      |      |      |      |      |      |  |\  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   0  |      |  .   |      |             |      |MPrev |Voldo |VolUp |MNext |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_5x12(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, _______, _______, _______, _______,
    OPQ,     KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______, _______, _______, _______, CLQ,
    _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______, _______, _______, KC_PIPE, _______,
    _______, KC_P0,   _______, KC_PDOT, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home |PageDn|PageUp| End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Adjust (Lower + Raise)

 * ,-----------------------------------------------------------------------------------.
 * |-RESET|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |RGBVA-|RGBVA+|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |RGBSA-|RGBSA+|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |RGBTOG|RGBHU-|RGBHU+|RGBMOD|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |BLTOGG|  BL- |  BL+ |BLBRTG|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_5x12(
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUD, RGB_HUI, RGB_MOD,
    _______, _______, _______, _______, _______, _______, _______, _______, BL_TOGG, BL_DEC,  BL_INC,  BL_BRTG
)

};

// [RGB Settings] ----------------------------------------------------------------------------------------------------------------------------//

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 4, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_mode(RGBLIGHT_MODE_TWINKLE + 2);
        rgblight_sethsv(25, 255, 128);
        break;
    case _LOWER:
        rgblight_mode(RGBLIGHT_MODE_TWINKLE + 2);
        rgblight_sethsv(135, 255, 128);
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode(RGBLIGHT_MODE_TWINKLE + 2);
        rgblight_sethsv(80, 255, 128);
        break;
    }
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
