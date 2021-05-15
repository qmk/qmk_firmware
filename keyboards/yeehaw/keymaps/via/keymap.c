#include QMK_KEYBOARD_H


enum custom_keycodes {
    YEEHAW = SAFE_RANGE,
    SQUASHKB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [0] = LAYOUT(
         KC_VOLU, 
         KC_VOLD, 
         KC_MPRV, YEEHAW, KC_UP, SQUASHKB,
 MO(1), KC_MNXT, KC_LEFT, KC_DOWN, KC_RIGHT,
        KC_MPLY, LCTL(KC_S), 
             RGB_TOG
    ), 

     [1] = LAYOUT(
        RGB_HUI, 
        RGB_HUD, 
        RGB_SAI, RGB_VAI, RGB_VAD, RGB_SPI,
KC_TRNS, RGB_SAD, RGB_M_P, RGB_MOD, RGB_SPD,
        KC_TRNS, KC_TRNS, 
             RESET
    ),

      [2] = LAYOUT(
        ____, 
        ____, 
        ____, ____, ____, ____,
____, ____, ____, ____, ____,
        ____, ____, 
             ____
    ),

      [3] = LAYOUT(
        ____, 
        ____, 
        ____, ____, ____, ____,
____, ____, ____, ____, ____,
        ____, ____, 
             ____
    ),
   
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case YEEHAW:
        if (record->event.pressed) {
            SEND_STRING("yeehaw!");
        }
        break;
        
    case SQUASHKB:
        if (record->event.pressed) {
            SEND_STRING("http://squashkb.com");
        }
        break;
    }
    return true;
};
