 /* Copyright 2021 Milan Düwel
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

 /* This keymap is designed for use with a German keyboard layout.
  * It is essentially the same as the default via keymap but adds combo functionality to type umlauts as well as lighting layers for various actions.
  * Toggling the combo feature also disables KC_LGUI so both can be turned off for gaming. If you want to get rid of it without reflashing new firmware, use KC_RGUI instead.
  * Layers 2 and 3 are currently unused but are configurable within via.
  */

enum combos {
  UML_AE,
  UML_OE,
  UML_UE,
  UML_SZ
};

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, KC_Y, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [UML_AE] = COMBO(ae_combo, KC_QUOT),
  [UML_OE] = COMBO(oe_combo, KC_SCLN),
  [UML_UE] = COMBO(ue_combo, KC_LBRC),
  [UML_SZ] = COMBO(sz_combo, KC_MINS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_DEL,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   MO(1),   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT),

	[1] = LAYOUT(
    QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
    KC_TRNS, RGB_TOG, KC_TRNS, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
    BL_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CM_TOGG, BL_TOGG, BL_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END,  KC_TRNS, KC_TRNS, KC_MUTE),

	[2] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[3] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

/*  The lighting layers feature a caps indicator as well as layer blinks for mute and the function layer (blink only to allow unhindered adjustment of the RGB backlight settings).
    Sadly these colours can not be customized within VIA.
*/

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED},
    {15, 17, HSV_RED}
);

const rgblight_segment_t PROGMEM my_function_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 12, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_f2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_f3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_flash_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_RED}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_function_layer,    // Overrides caps lock layer
    my_f2_layer,
    my_f3_layer,
    my_flash_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
};

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    //rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
};

// Note we user post_process_record_user because we want the state
// after the flag has been flipped...
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
        case KC_MUTE:
        case QK_COMBO_TOGGLE:
            if (record->event.pressed) {
                rgblight_blink_layer(4, 250);
            }
            break;
        case MO(1):
            if (record->event.pressed) {
                rgblight_blink_layer(1, 250);
            }
            break;
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case KC_LGUI:   //use combo toggle to disable the win key while gaming
            if (record->event.pressed) {
                if (is_combo_enabled()==false) {
                    return false;
                }
            }
            return true; // Let QMK send the enter press/release events
        default:
            return true; // Process all other keycodes normally
  }
};
