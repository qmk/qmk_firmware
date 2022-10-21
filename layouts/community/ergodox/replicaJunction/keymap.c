/* Copyright 2021 Joshua T.
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
#include "replicaJunction.h"

// Most layers are defined in my userspace, but this keyboard has
// an extra one.
enum additional_keyboard_layers {
    L_SYSLEDS = _LAYER_SAFE_RANGE
};

#define BSP_SYM LT(L_SYMBOLS, KC_BSPC)
#define SPC_NAV LT(L_NAVIGATION, KC_SPC)

#define MO_FN MO(L_FN)
#define MO_MAC MO(L_MACROS)
#define MO_SLED MO(L_SYSLEDS)

#define TG_GAME TG(L_GAMING)

#define ESC_SFT  LSFT_T(KC_ESC)
#define TAB_SFT  RSFT_T(KC_TAB)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[L_BASE] = LAYOUT_ergodox(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,
    KC_EQL,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    NUMWORD,
    KC_MINS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_RBRC,
    KC_LCTL, KC_LGUI ,KC_LALT, MO_FN,   ESC_SFT,
                                                 KC_HOME, KC_END,
                                                          KC_PGUP,
                                        BSP_SYM, CTL_DEL, KC_PGDN,

    TG_GAME, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    CAPWORD, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
             KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    QK_LOCK, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                      TAB_SFT, MO_FN,   KC_RALT, KC_RGUI, MO_SLED,
    KC_LEFT, KC_RGHT,
    KC_UP,
    KC_DOWN, ALT_ENT, SPC_NAV
),


[L_GAMING] = LAYOUT_ergodox(
    KC_GRV, _______,_______,_______,_______,_______,_______,
    KC_TAB, _______,_______,_______,_______,_______,_______,
    KC_ESC, KC_A,   KC_R,   KC_S,   KC_T,   _______,
    KC_LSFT,_______,_______,KC_C,   KC_D,   _______,_______,
    _______,_______,KC_TAB, KC_LALT,KC_LCTL,
                                            QK_LOCK,_______,
                                                    _______,
                                    KC_SPC, KC_LSFT,_______,

    ooooooo,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
            _______,KC_N,   KC_E,   KC_I,   KC_O,   _______,
    _______,_______,_______,_______,_______,_______,_______,
                    MO_FN,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,
    KC_BTN3,_______,
    KC_BTN2,
    KC_BTN1,KC_ENT, KC_BSPC
),


[L_NUMBERS] = LAYOUT_ergodox(
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
    _______,KC_LGUI,KC_LALT,KC_LSFT,KC_LCTL,_______,
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,
                                            _______,_______,
                                                    _______,
                                    _______,_______,_______,

    _______,KC_NUM, _______,_______,_______,_______,_______,
    KC_NUM, KC_HASH,KC_P7,  KC_P8,  KC_P9,  KC_PSLS,SFT_TAB,
            KC_PPLS,KC_P4,  KC_P5,  KC_P6,  KC_PAST,KC_TAB,
    _______,KC_PMNS,KC_P1,  KC_P2,  KC_P3,  KC_BSLS,KC_EQL,
                    KC_P0,  KC_P0,  KC_PDOT,KC_PENT,_______,
    _______,_______,
    _______,
    _______,_______,_______
),


[L_SYMBOLS] = LAYOUT_ergodox(
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
    _______,KC_AT,  KC_LT,  KC_DLR, KC_GT,  XXXXXXX,_______,
    _______,KC_BSLS,KC_LPRN,KC_DQUO,KC_RPRN,KC_HASH,
    _______,KC_EXLM,KC_COLN,KC_ASTR,KC_PLUS,XXXXXXX,_______,
    _______,_______,_______,_______,_______,
                                            _______,_______,
                                                    _______,
                                    ooooooo,_______,_______,

    _______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    _______,XXXXXXX,KC_LBRC,KC_UNDS,KC_RBRC,XXXXXXX,KC_F12,
            KC_PERC,KC_LCBR,KC_EQL, KC_RCBR,KC_PIPE,_______,
    _______,XXXXXXX,KC_AMPR,KC_CIRC,KC_TILD,KC_GRV, _______,
                    _______,_______,_______,_______,_______,
    _______,_______,
    _______,
    _______,_______,ooooooo
),


[L_NAVIGATION] = LAYOUT_ergodox(
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
    _______,OS_UNDO,OS_CUT, OS_PAST,OS_COPY,OS_SALL,_______,
    _______,KC_LGUI,KC_LSFT,KC_LALT,KC_LCTL,_______,
    _______,WIN_V,  _______,_______,OS_FIND,SEARCH, _______,
    _______,_______,_______,_______,_______,
                                            _______,_______,
                                                    _______,
                                    _______,_______,_______,

    _______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    _______,KC_PGUP,KC_HOME,KC_UP,  KC_END, KC_DEL, KC_F12,
            KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_BSPC,_______,
    _______,_______,SFT_TAB,KC_TAB, KC_APP, KC_PSCR,_______,
                    _______,_______,_______,_______,_______,
    _______,_______,
    _______,
    _______,_______,ooooooo
),


[L_FN] = LAYOUT_ergodox(
    _______,_______,_______,_______,_______,_______,_______,
    _______,QK_VERS,_______,DM_REC2,DM_REC1,DM_RSTP,_______,
    _______,QK_MAKE,_______,DM_PLY2,DM_PLY1,_______,
    _______,QK_FLSH,K_SECR1,K_SECR2,K_SECR3,K_SECR4,_______,
    _______,_______,_______,ooooooo,_______,
                                            _______,_______,
                                                    _______,
                                    KC_LCTL,_______,_______,

    _______,_______,_______,_______,_______,_______,_______,
    _______,KC_VOLU,KC_F9,  KC_F10, KC_F11, KC_F12, _______,
            KC_MUTE,KC_F5,  KC_F6,  KC_F7,  KC_F8,  _______,
    _______,KC_VOLD,KC_F1,  KC_F2,  KC_F3,  KC_F4,  _______,
                    _______,ooooooo,_______,_______,_______,
    _______,QK_BOOT,
    _______,
    _______,_______,KC_LALT
),


[L_MACROS] = LAYOUT_ergodox(
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,DM_REC2,DM_REC1,_______,_______,
    _______,_______,_______,DM_PLY2,DM_PLY1,DM_RSTP,
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,
                                            _______,_______,
                                                    _______,
                                    ooooooo,_______,_______,

    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,SHEBANG,_______,_______,_______,_______,
            PRG_NE, PRG_EQ, PRG_GEQ,PRG_LEQ,PRG_ARR,_______,
    _______,_______,PS_ITEM,FS_PIPE,_______,FS_ARR, _______,
                    _______,_______,_______,_______,_______,
    _______,_______,
    _______,
    _______,_______,ooooooo
),



[L_SYSLEDS] = LAYOUT_ergodox(
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,
                                            _______,_______,
                                                    _______,
                                    _______,_______,_______,

    KC_NUM, _______,_______,_______,_______,_______,_______,
    KC_CAPS,_______,_______,_______,_______,_______,_______,
            _______,_______,_______,_______,_______,_______,
    KC_SCRL,_______,_______,_______,_______,_______,_______,
                    _______,_______,_______,_______,ooooooo,
    _______,_______,
    _______,
    _______,_______,_______
)

// Template
// [_NUMBERS] = LAYOUT_ergodox(
//     _______,_______,_______,_______,_______,_______,_______,
//     _______,_______,_______,_______,_______,_______,_______,
//     _______,_______,_______,_______,_______,_______,
//     _______,_______,_______,_______,_______,_______,_______,
//     _______,_______,_______,_______,_______,
//                                             _______,_______,
//                                                     _______,
//                                     _______,_______,_______,

//     _______,_______,_______,_______,_______,_______,_______,
//     _______,_______,_______,_______,_______,_______,_______,
//             _______,_______,_______,_______,_______,_______,
//     _______,_______,_______,_______,_______,_______,_______,
//                     _______,_______,_______,_______,_______,
//     _______,_______,
//     _______,
//     _______,_______,_______
// ),

};

void keyboard_post_init_user_kb(void) {
    ergodox_right_led_1_on();
}


////////////////////////////////////////////////////////////
// System LED code
////////////////////////////////////////////////////////////

// We need to track both the layer state and the system LED state in
// order to update the LEDs appropriately when either one changes.
// These are both represented as a bitmask.
//
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user(), so it doesn't work properly for our
// purposes.
static uint32_t current_layer_state = 0;
static uint8_t sys_led_state = 0;

// Whether the given layer (one of the constant defined at the top) is active.
#define LAYER_ON(state, layer) (state & (1<<layer))

// Brightness of LEDs (0-255)
// Default value is 255. Use a lesser value for dimmer LEDs.
static const uint8_t max_led_value = 255;

void led_1_on(void) {
    ergodox_right_led_1_on();
    ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
    ergodox_right_led_2_on();
    ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
    ergodox_right_led_3_on();
    ergodox_right_led_3_set(max_led_value);
}

// The onboard LED doesn't support brightness, but this function keeps
// things consistent.
void led_board_on(void) {
    ergodox_board_led_on();
}

void led_1_off(void) {
    ergodox_right_led_1_off();
}

void led_2_off(void) {
    ergodox_right_led_2_off();
}

void led_3_off(void) {
    ergodox_right_led_3_off();
}

void led_board_off(void) {
    ergodox_board_led_off();
}

void set_leds_by_system_state(uint8_t led_state) {
    led_t host_led_state = host_keyboard_led_state();

    if (led_state & host_led_state.num_lock) {
        led_1_on();
    }
    else {
        led_1_off();
    }

    if (led_state & host_led_state.caps_lock) {
        led_2_on();
    }
    else {
        led_2_off();
    }

    if (led_state & host_led_state.scroll_lock) {
        led_3_on();
    }
    else {
        led_3_off();
    }
}

void set_leds_by_layer_state(uint32_t layer_state) {
    if (LAYER_ON(layer_state, L_FN)) {
        led_1_on();
        led_2_on();
        led_3_on();
        led_board_off();
    }
    else if (LAYER_ON(layer_state, L_GAMING)) {
        led_1_off();
        led_2_off();
        led_3_off();
        led_board_on();
    }
    else if (LAYER_ON(layer_state, L_NUMBERS)) {
        led_1_on();
        led_2_off();
        led_3_off();
        led_board_off();
    }
    else if (LAYER_ON(layer_state, L_NAVIGATION)) {
        led_1_off();
        led_2_on();
        led_3_off();
        led_board_off();
    }
    else {
        led_1_on();
        led_2_off();
        led_3_off();
        led_board_off();
    }
}

void led_set_kb(uint8_t usb_led) {
    sys_led_state = usb_led;

    if (LAYER_ON(current_layer_state, L_SYSLEDS)) {
        set_leds_by_system_state(sys_led_state);
    }
    else {
        set_leds_by_layer_state(current_layer_state);
    }

    led_set_user(usb_led);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    current_layer_state = state;

    if (LAYER_ON(state, L_SYSLEDS)) {
        set_leds_by_system_state(sys_led_state);
    }
    else {
        set_leds_by_layer_state(state);
    }

    return update_tri_layer_state(state, L_SYMBOLS, L_NAVIGATION, L_MACROS);
}
