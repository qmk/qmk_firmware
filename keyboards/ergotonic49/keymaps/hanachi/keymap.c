/* Copyright 2021 hanachi-ap
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _EXT,
    _NUM,
    _FN,
    _SYS,
};

enum custom_keycodes {
    RE_TOGGLE = SAFE_RANGE,
    RE_MODE0,
    RE_MODE1,
    RE_MODE2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY]=LAYOUT(   //QWERTY
			KC_ESC	,	KC_Q	,	KC_W	,	KC_E	,	KC_R	,	KC_T	,							KC_Y	,	KC_U	,	KC_I	,	KC_O	,	KC_P	,	KC_EQL	,	KC_QUOT	,
			KC_TAB	,	KC_A	,	KC_S	,	KC_D	,	KC_F	,	KC_G	,							KC_H	,	KC_J	,	KC_K	,	KC_L	,	KC_SCLN	,	KC_MINS	,	KC_ENT	,
			KC_LSFT	,	KC_Z	,	KC_X	,	KC_C	,	KC_V	,	KC_B	,	KC_DEL	,			KC_LGUI	,	KC_N	,	KC_M	,	KC_COMM	,	KC_DOT	,	KC_SLSH	,	KC_RSFT	,
	RE_TOGGLE	,							KC_LGUI	,	KC_LALT	,	LT(_NUM,KC_SPC)	,	CTL_T(KC_F13)	,	MO(_NUM)	,	SFT_T(KC_ENT)	,	LT(_FN, KC_BSPC)	,	LT(_NUM, KC_DOWN)	,	LT(_SYS, KC_UP)	,
			C(KC_PMNS)	,	C(KC_PPLS)	,							KC_WH_L	,	KC_WH_R	,			KC_VOLD	,	KC_VOLU
),

[_EXT]=LAYOUT(   //
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),

[_NUM]=LAYOUT(    // NUM
			KC_GRV	,	KC_EXLM	,	KC_AT	,	KC_HASH	,	KC_DLR	,	KC_PERC	,							KC_CIRC	,	KC_AMPR	,	KC_ASTR	,	KC_LPRN	,	KC_RPRN	,	KC_LBRC	,	KC_RBRC	,
			_______	,	KC_1	,	KC_2	,	KC_3	,	KC_4	,	KC_5	,							KC_6	,	KC_7	,	KC_8	,	KC_9	,	KC_0	,	KC_MINS	,	KC_PLUS	,
			_______	,	S(KC_MINS)	,	S(KC_BSLS)	,	S(KC_GRV)	,	KC_LPRN	,	KC_RPRN	,	_______	,			_______	,	S(KC_LBRC)	,	S(KC_RBRC)	,	KC_COMM	,	KC_DOT	,	KC_SLSH	,	KC_BSLS	,
	_______	,							C(LWIN(KC_LEFT))	,	C(LWIN(KC_RIGHT))	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),
[_FN]=LAYOUT(    //FN (additional keys)
			_______	,	KC_F1	,	KC_F2	,	KC_F3	,	KC_F4	,	KC_F5	,							KC_PGUP	,	XXXXXXX	,	KC_UP	,	XXXXXXX	,	KC_NLCK	,	C(LWIN(KC_LEFT))	,	C(LWIN(KC_RIGHT))	,
			KC_CAPS	,	KC_F6	,	KC_F7	,	KC_F8	,	KC_F9	,	KC_F10	,							KC_PGDN	,	KC_LEFT	,	KC_DOWN	,	KC_RIGHT	,	KC_SLCK	,	XXXXXXX	,	XXXXXXX	,
			_______	,	KC_F11	,	KC_F12	,	KC_F13	,	XXXXXXX	,	XXXXXXX	,	_______	,			_______	,	KC_HOME	,	KC_END	,	KC_DOWN	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,
	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),
[_SYS]=LAYOUT(  //SYS (System utilz)
			RE_MODE0	,	RGB_TOG	,	RGB_VAD	,	RGB_VAI	,	KC_ASON	,	KC_ASOFF	,							XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	RE_MODE0	,	RESET	,
			RE_MODE1	,	RGB_MOD	,	RGB_SAD	,	RGB_SAI	,	KC_ASUP	,	KC_ASDN	,							XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	RE_MODE1	,	EEP_RST	,
			RE_MODE2	,	RGB_RMOD	,	RGB_HUD	,	RGB_HUI	,	KC_ASRP	,	XXXXXXX	,	XXXXXXX	,			XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	RE_MODE2	,
	_______	,							_______	,	_______	,	_______	,	_______	,	XXXXXXX	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
)



};

int encoder_mode = 0;

void set_re_mode(uint16_t i) {
    encoder_mode = i;
}

void toggle_re_mode(void) {
    encoder_mode += 1;
    if (encoder_mode >= 3) encoder_mode = 0;
}

const uint16_t rot_key[][3] = {
    {0, KC_VOLD, KC_VOLU},                  // Audio volume
    {0, LCTL(KC_MINUS), LCTL(KC_PLUS)},      // zooming
    {0, KC_WH_L, KC_WH_R},     // Horizontal scroll
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RE_TOGGLE:
            if (record->event.pressed) {
                toggle_re_mode();
            }
            return false;
        case RE_MODE0:
            if (record->event.pressed) {
                set_re_mode(0);
            }
            return false;

        case RE_MODE1:
            if (record->event.pressed) {
                set_re_mode(1);
            }
            return false;

        case RE_MODE2:
            if (record->event.pressed) {
                set_re_mode(2);
            }
            return false;

    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    uint16_t modifier = rot_key[encoder_mode][0];
    if (modifier != 0) {
        register_code16(modifier);
        wait_ms(10);
    }
    if (clockwise) {
        tap_code16(rot_key[encoder_mode][2]);
    } else {
        tap_code16(rot_key[encoder_mode][1]);
    }
    if (rot_key[encoder_mode][0] != 0) {
        unregister_code16(modifier);
    }
    return false;
}

const rgblight_segment_t PROGMEM rgb_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_scllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_caps_layer,
    rgb_numlock_layer,
    rgb_scllock_layer
);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, IS_HOST_LED_ON(USB_LED_NUM_LOCK));
    rgblight_set_layer_state(1, IS_HOST_LED_ON(USB_LED_CAPS_LOCK));
    rgblight_set_layer_state(2, IS_HOST_LED_ON(USB_LED_SCROLL_LOCK));

    return true;
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
//    rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
}
