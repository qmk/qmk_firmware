#include QMK_KEYBOARD_H

#define ____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // BASE LAYER
    [0] = LAYOUT_all(
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,       KC_O,   KC_P,       KC_LBRC,    KC_RBRC,
        MO(2),      KC_A,       KC_S,       KC_D,       KC_F,   KC_G,   KC_H,   KC_J,   KC_K,       KC_L,   KC_SCLN,                KC_ENT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,    KC_DOT, KC_SLSH,                MO(3),
                    KC_LCTL,    KC_LALT,    KC_BSPC,    MO(1),          MO(1),          KC_SPC,     KC_RALT,            KC_LGUI
    ),
    // BASE LAYER TWO (Fn1)
    [1] = LAYOUT_all(
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,   KC_5,   KC_6,   KC_7,   KC_8,       KC_9,   KC_0,       KC_MINS,    KC_EQL,
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   ____,       ____,   KC_QUOT,                KC_BSLS,
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   ____,       ____,   ____,                   KC_RSFT,
                    ____,       ____,       ____,       ____,           ____,           ____,       ____,               ____
    ),
    // FROW LAYER AND ARROWS (Fn2)
    [2] = LAYOUT_all(
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,      KC_F9,  KC_F10,     KC_F11,     KC_F12,
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   ____,       KC_UP,  ____,                   ____,
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   KC_LEFT,    KC_DOWN,KC_RGHT,                MO(4),
                    ____,       ____,       ____,       ____,           ____,           ____,       ____,               ____
    ),
    // MEDIA AND RGB (Fn3)
    [3] = LAYOUT_all(
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   ____,       KC_MPRV,KC_MPLY,    KC_MNXT,    KC_DEL,
        ____,       ____,       ____,       RGB_HUI,    RGB_SAI,RGB_VAI,____,   ____,   ____,       ____,   ____,                   ____,
        ____,       RGB_MOD,    RGB_TOG,    RGB_HUD,    RGB_SAD,RGB_VAD,____,   ____,   ____,       ____,   ____,                   ____,
                    ____,       ____,       ____,       ____,           ____,           ____,       ____,               ____
    ),
    // UTIL (Fn1+Fn3)
    [4] = LAYOUT_all(
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   ____,       ____,   ____,       KC_PSCR,    ____,
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   ____,       KC_PGUP,____,                   ____,
        ____,       ____,       ____,       ____,       ____,   ____,   ____,   ____,   KC_HOME,    KC_PGDN,KC_END,                 ____,
                    RESET,      ____,       ____,       ____,           ____,           ____,       ____,               ____
    ),
};

/**
 * Status LED layer indicators courtesy of jetpacktuxedo's firmware
 */
layer_state_t layer_state_set_kb(layer_state_t state)
{
    // if we are on layer 1
    if (state & (1<<1)){
        // light num lock led
        PORTD |= (1 << PD0);
    } else{
        PORTD &= ~(1 << PD0);
    }

    // if we are on layer 2
    if (state & (1<<2)){
        // light caps lock led
        PORTD |= (1 << PD1);
    } else{
        PORTD &= ~(1 << PD1);
    }

    // if we are on layer 3
    if (state & (1<<3)){
        // light scroll lock led
        PORTD |= (1 << PD6);
    } else{
        PORTD &= ~(1 << PD6);
    }

    /*
    // if we are on layer 4
    if (state & (1<<4)){
        // light all leds
        PORTD |= (1 << PD0);
        PORTD |= (1 << PD1);
        PORTD |= (1 << PD6);
    } else{
        PORTD &= ~(1 << PD0);
        PORTD &= ~(1 << PD1);
        PORTD &= ~(1 << PD6);
    }
    */

    return state;
}
