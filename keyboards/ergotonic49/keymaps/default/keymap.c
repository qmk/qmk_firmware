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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY]=LAYOUT(   //QWERTY
			KC_ESC	,	KC_Q	,	KC_W	,	KC_E	,	KC_R	,	KC_T	,							KC_Y	,	KC_U	,	KC_I	,	KC_O	,	KC_P	,	KC_MINS	,	KC_EQL	,
			KC_TAB	,	KC_A	,	KC_S	,	KC_D	,	KC_F	,	KC_G	,							KC_H	,	KC_J	,	KC_K	,	KC_L	,	KC_SCLN	,	KC_QUOT	,	KC_ENT	,
			KC_LSFT	,	KC_Z	,	KC_X	,	KC_C	,	KC_V	,	KC_B	,	KC_DEL	,			KC_LGUI	,	KC_N	,	KC_M	,	KC_COMM	,	KC_DOT	,	KC_SLSH	,	KC_RSFT	,
	XXXXXXX	,							WIN_T(KC_LEFT)	,	ALT_T(KC_RIGHT)	,	LT(_NUM,KC_SPC)	,	KC_LCTL	,	MO(_NUM)	,	SFT_T(KC_ENT)	,	LT(_FN, KC_BSPC)	,	LT(_NUM, KC_DOWN)	,	LT(_SYS, KC_UP)	,
			C(KC_PMNS)	,	C(KC_PPLS)	,							KC_WH_L	,	KC_WH_R	,			KC_VOLD	,	KC_VOLU
),

[_EXT]=LAYOUT(   // Extension
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),

[_NUM]=LAYOUT(    // NUM (Num pad)
			KC_GRV	,	KC_1	,	KC_2	,	KC_3	,	KC_4	,	KC_5	,							KC_6	,	KC_7	,	KC_8	,	KC_9	,	KC_0	,	KC_LBRC	,	KC_RBRC	,
			_______	,	KC_EXLM	,	KC_AT	,	KC_HASH	,	KC_DLR	,	KC_PERC	,							XXXXXXX	,	KC_4	,	KC_5	,	KC_6	,	KC_ASTR	,	KC_PLUS	,	KC_BSLS	,
			_______	,	KC_CIRC	,	KC_AMPR	,	KC_ASTR	,	KC_LPRN	,	KC_RPRN	,	_______	,			_______	,	KC_0	,	KC_1	,	KC_2	,	KC_3	,	KC_SLSH	,	_______	,
	_______	,							C(LWIN(KC_LEFT))	,	C(LWIN(KC_RIGHT))	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),
[_FN]=LAYOUT(    //FN (additional keys)
			_______	,	KC_F1	,	KC_F2	,	KC_F3	,	KC_F4	,	KC_F5	,							XXXXXXX	,	KC_PGDN	,	KC_UP	,	KC_PGUP	,	XXXXXXX	,	C(LWIN(KC_LEFT))	,	C(LWIN(KC_RIGHT))	,
			KC_CAPS	,	KC_F6	,	KC_F7	,	KC_F8	,	KC_F9	,	KC_F10	,							XXXXXXX	,	KC_LEFT	,	KC_DOWN	,	KC_RIGHT	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,
			_______	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	_______	,			_______	,	XXXXXXX	,	KC_HOME	,	KC_DOWN	,	KC_END	,	XXXXXXX	,	XXXXXXX	,
	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),
[_SYS]=LAYOUT(  //SYS (System utilz)
			RESET	,	RGB_TOG	,	RGB_VAD	,	RGB_VAI	,	KC_ASON	,	KC_ASOFF	,							XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,
			EEP_RST	,	RGB_MOD	,	RGB_SAD	,	RGB_SAI	,	KC_ASUP	,	KC_ASDN	,							XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,
			XXXXXXX	,	RGB_RMOD	,	RGB_HUD	,	RGB_HUI	,	KC_ASRP	,	XXXXXXX	,	XXXXXXX	,			XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,
	_______	,							_______	,	_______	,	_______	,	_______	,	XXXXXXX	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      return true;
}

const uint8_t rt_matrix[][3][2] = {
    {{3,1},{3,2}},
    {{0,6},{1,6}},
    {{0,7},{3,11}},
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    int      cw = 0;
    if (clockwise) cw = 1;
    key.row          = rt_matrix[index][cw][0];
    key.col          = rt_matrix[index][cw][1];
    uint8_t  layer   = layer_switch_get_layer(key);
    uint16_t keycode = keymap_key_to_keycode(layer, key);
    tap_code16(keycode);
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
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    autoshift_disable();
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
}
