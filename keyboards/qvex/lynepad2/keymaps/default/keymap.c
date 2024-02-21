/*
Copyright 2023 QVEX Tech

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define RGB_HUE_LAYER0 0 //default layer
#define RGB_HUE_LAYER1 50
#define RGB_HUE_LAYER2 100
#define RGB_HUE_LAYER3 150
#define RGB_HUE_LAYER4 200


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT //Default
    (
        G(KC_D),   G(KC_TAB), C(G(KC_LEFT)),   C(G(KC_RIGHT)),
        G(KC_E),   XXXXXXX,  C(KC_C),  C(KC_V),
        KC_LGUI,   XXXXXXX,  XXXXXXX,

        KC_VOLU,   KC_VOLD,   KC_MPRV,   KC_MNXT,   //joystick up, down, left, right
        KC_MPLY,   MO(4)                            //joystick center push, thumbwheel push
    ),

    [1] = LAYOUT //KiCad
    (
        KC_ESC,   KC_R,   KC_M,   KC_DEL,
        KC_V,     KC_G,   KC_D,   KC_X,
        MO(3),    KC_B,   C(KC_V),

        KC_PLUS,   KC_MINUS,   C(KC_Y),   C(KC_Z),  //joystick up, down, left, right
        KC_PGDN,   MO(4)                            //joystick center push, thumbwheel push
    ),

    [2] = LAYOUT
    (
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,

        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   //joystick up, down, left, right
        XXXXXXX,   MO(4)                            //joystick center push, thumbwheel push
    ),

    [3] = LAYOUT
    (
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,

        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   //joystick up, down, left, right
        XXXXXXX,   MO(4)                            //joystick center push, thumbwheel push
    ),

    [4] = LAYOUT
    (
        TO(0),     TO(1),     TO(2),     TO(3),
        BL_TOGG,   BL_STEP,   XXXXXXX,   XXXXXXX,
        QK_RBT,    EE_CLR,    QK_BOOT,

        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   //joystick up, down, left, right
        RGB_TOG,   XXXXXXX                          //joystick center push, thumbwheel push
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { 
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU), 
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  
    },

    [1] = { 
        ENCODER_CCW_CW(LSFT(KC_W), KC_W), 
        ENCODER_CCW_CW(KC_N, LSFT(KC_N))  
    },

    [2] = { 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX), 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  
    },

    [3] = { 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX), 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  
    },

    [4] = { 
        ENCODER_CCW_CW(RGB_VAD, RGB_VAI), 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  
    }
};
#endif

//set only hue, retain saturation, and value
void rgblight_sethue_noeeprom(uint8_t hue){
    //only if rgb led ring is on
    if (rgblight_get_mode()) {
        rgblight_sethsv_noeeprom(hue,rgblight_get_sat(),rgblight_get_val());
    }     
}

//set correct layer hue on layer change
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1:
            rgblight_sethue_noeeprom(RGB_HUE_LAYER1);
            break;
        case 2:
            rgblight_sethue_noeeprom(RGB_HUE_LAYER2);
            break;
        case 3:
            rgblight_sethue_noeeprom(RGB_HUE_LAYER3);
            break;
        case 4:
            rgblight_sethue_noeeprom(RGB_HUE_LAYER4);
            break;
        default:
            rgblight_sethue_noeeprom(RGB_HUE_LAYER0);
            break;

    }
    return state;
}

//set default layer hue upon init
void keyboard_post_init_user(void) {
  rgblight_init();
  rgblight_sethue_noeeprom(RGB_HUE_LAYER0);
}