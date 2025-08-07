/* Copyright (c) 2022 David Kuehling < dvdkhlng TA posteo TOD de >
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

enum layer_names { _DEFAULT, _FUNCTION };
#define KC_FUN TG(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_FUN,  KC_NUM, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_PSCR,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
     
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_VOLU, KC_ESC, KC_P4, KC_P5, KC_P6, KC_PAST, KC_SCRL,  KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, 
        KC_NUBS,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_VOLD, KC_GRV, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_BRK,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, 
        KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_MUTE, KC_WSCH,KC_P0,KC_PDOT,KC_PENT,KC_PPLS,KC_INS,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, 
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                                                            KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT, 
        /* */  KC_LCTL, KC_LGUI,KC_LALT,KC_RBRC,                                                                         KC_NUHS,KC_RALT,KC_APP, KC_RCTL, /* */
        
        /* thumb keys: */                      KC_BSPC, KC_HOME, KC_END,                       KC_LEFT, KC_RGHT, KC_DEL,
        /* thumb keys: */                      KC_SPC,  KC_TAB,  KC_PGUP,                      KC_UP,   KC_ENT,  KC_SPC,
        /* thumb keys: */                                        KC_PGDN,                      KC_DOWN
        ),
    
    /* This is the "function key locked" layer.  It is not documented by
     * Maltron, so just putting some "Quantum" keycodes here for testing that
     * the layer exists and Fun Lock LED works. */
    [_FUNCTION] = LAYOUT(
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,KC_TRNS,KC_BTN3,KC_MS_U,KC_WH_U,KC_NO, KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, 
        
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  CK_UP,  AU_ON,  KC_MS_L,KC_BTN1,KC_MS_R,KC_NO, KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  CK_DOWN,AU_OFF, KC_BTN2,KC_MS_D,KC_WH_D,KC_NO, KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   
        KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  CK_TOGG,KC_NO,  KC_ACL0,KC_ACL1,KC_ACL2,KC_NO, KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                                                           KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   
        /* */  KC_NO,   KC_NO,  KC_NO,  KC_NO,                                                                           KC_NO,  KC_NO,  KC_NO,  KC_NO,   /* */
        
        /* thumb keys: */                      KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO, 
        /* thumb keys: */                      KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO, 
        /* thumb keys: */                                        KC_NO,                         KC_NO
        )
};

/* Show "Fun Lock" layer state via the "Fun Lock" LED */
layer_state_t layer_state_set_user(layer_state_t state) {
   
    gpio_set_pin_output(LED_FUN_LOCK_PIN);
   
    if (layer_state_cmp(state, _FUNCTION))
        gpio_write_pin_high(LED_FUN_LOCK_PIN);
    else
        gpio_write_pin_low(LED_FUN_LOCK_PIN);

    return state;
}

/*
 * Local Variables:
 * c-basic-offset:4
 * fill-column: 76
 * End:
 */
