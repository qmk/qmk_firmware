/* Copyright 2019 Erovia
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
#define USB_MAX_POWER_CONSUMPTION 900
// Act as Shift on hold and as CapsLock on tap
#define KC_SFT_CPS TD(TD_SFT_CPS)
// Left space on tap, LOWER on hold
#define SPC_LOW LT(_LOWER, KC_ENT)
// Left space on tap, UPPER on hold
#define SPC_UPR LT(_RAISE, KC_SPC)


enum custom_layers {
	_QWERTY,
	_LOWER,
	_RAISE,
	_ADJUST,
    _FKEY
};

enum {
    KC_EML = 0,
    TD_SFT_CPS,
};

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_RSFT);
        register_code (KC_2);
    } else {
        SEND_STRING("tom.campie@gmail.com");
    }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_RSFT);
        unregister_code (KC_2);
    } else {
    }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [KC_EML] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
    [TD_SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};


uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
//        case KC_SFT_CPS:
//            return 100;
//        case SPC_UPR:
//            return 50;
        case SPC_LOW:
            return 150;
////        case TD(KC_EML):
////            return 50;
        default:
            return TAPPING_TERM;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,---------------------------------------------------------------.
 * |Esc | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  |  Bspc  |
 * |---------------------------------------------------------------|
 * | Tab  | A  | S  | D  | F  | G  | H  | J  | K  | L  | '  |Enter |
 * |---------------------------------------------------------------|
 * | Shift  | Z  | X  | C  | V  | B  | N  | M  | ,  | Up |    .    |
 * |---------------------------------------------------------------|
 *      |Ctrl|Gui |Alt | Spc/Lwr |   Spc/Rse   |Left|Down|Rght|
 *      `-----------------------------------------------------'
 */

	[_QWERTY] = LAYOUT(
        KC_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_BSPC,
        LCTL_T(KC_TAB),  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
		KC_SFT_CPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_UP,   KC_DOT,
		KC_LCTL, KC_LGUI, KC_LALT, SPC_LOW,  SPC_UPR,  LT(_FKEY, KC_LEFT), KC_DOWN, KC_RGHT
	),

/*
 * ,---------------------------------------------------------------.
 * | ~  | !  | @  | #  | $  | %  | ^  | &  | *  | (  | )  |        |
 * |---------------------------------------------------------------|
 * | Del  | F1 | F2 | F3 | F4 | F5 | F6 | _  | +  | {  | }  |  |   |
 * |---------------------------------------------------------------|
 * |        | F7 | F8 | F9 |F10 |F11 |F12 |    | ;  |PgUp|   /     |
 * |---------------------------------------------------------------|
 *      |    |    |    |         |             |Home|PgDn|End |
 *      `-----------------------------------------------------'
 */

	[_LOWER] = LAYOUT(
		KC_TILD, KC_EXLM, TD(KC_EML),   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
		KC_DEL,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
		KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_SCLN, KC_PGUP, KC_SLSH,
		LCA(KC_DEL),   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
	),

/*
 * ,---------------------------------------------------------------.
 * | `  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  |        |
 * |---------------------------------------------------------------|
 * | Ins  | F1 | F2 | F3 | F4 | F5 | F6 | -  | =  | [  | ]  |  \   |
 * |---------------------------------------------------------------|
 * |        | F7 | F8 | F9 |F10 |F11 |F12  |    |    |   |         |
 * |---------------------------------------------------------------|
 *      |VolD|Mute|VolU|         |             |    |    |    |
 *      `-----------------------------------------------------'
 */

	[_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
		KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_DOT,
		KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS,   KC_NO,   KC_NO
	),

/*
 * ,---------------------------------------------------------------.
 * |RST |EEP |    |    |    |    |    |    |    |    |    |        |
 * |---------------------------------------------------------------|
 * |      |    |    |    |    |    |    |    |    |    |    |      |
 * |---------------------------------------------------------------|
 * |        |    |    |    |    |    |     |    |    |   |         |
 * |---------------------------------------------------------------|
 *      |RGB-|RGB |RGB+|         |             |    |    |    |
 *      `-----------------------------------------------------'
 */

	[_ADJUST] = LAYOUT(
		RESET,EEP_RST,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		RGB_M_P,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_M_SN,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
                       ),
    
    [_FKEY] = LAYOUT(
        KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
        RGB_M_P,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F12,   KC_F13,
        RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_M_SN,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_TRNS,   KC_NO, KC_NO
                       ),
};

void led_set_user(uint8_t usb_led) {
if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
	dimple_led_off();
	} else {
	dimple_led_on();
	}
}


uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (biton32(state)) {
        case _LOWER:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _RAISE:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_CYAN);
            break;
        default:
            rgblight_sethsv_noeeprom(50,140,201);
            break;
    }
    return state;
}

