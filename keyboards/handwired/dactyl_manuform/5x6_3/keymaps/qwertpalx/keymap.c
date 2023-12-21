#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _CARPALX 2

#define QWERTY TG(_QWERTY)
#define LOWER TG(_LOWER)
#define CARPALX TG(_CARPALX)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
                        KC_LBRC,KC_RBRC,CARPALX, KC_SPC,                         KC_SPC, LOWER ,KC_RGUI, KC_EQL,                        
                                                KC_LALT,                         KC_ENT
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_F12 ,KC_F1  , KC_F2 ,KC_F3  ,KC_F4  ,KC_F5  ,                         KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                         KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                         KC_TRNS, KC_P4 , KC_P5 , KC_P6 ,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                         KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                        KC_CTRL,KC_LSFT,CARPALX, KC_SPC,                         KC_SPC , QWERTY,KC_TRNS,KC_TRNS,
                                                KC_LALT,                         KC_RALT
    ),

    [_CARPALX] = LAYOUT_5x6(
        QK_BOOT, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6   , KC_7  , KC_8  , KC_9  ,KC_10  ,KC_11  ,
        KC_TAB , KC_Q  , KC_G  , KC_M  , KC_L  , KC_W  ,                         KC_Y   , KC_F  , KC_U  , KC_B  ,KC_LBRC,KC_RBRC,
        KC_LSFT, KC_D  , KC_S  , KC_T  , KC_N  , KC_R  ,                         KC_I   , KC_A  , KC_E  , KC_O  , KC_H  ,KC_SCLN,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_J  ,                         KC_K   , KC_P  ,KC_COMM, KC_DOT,KC_QUOT,KC_RGUI,
                        KC_MNS , KC_EQL, QWERTY, KC_SPC,                         KC_SPC , QWERTY,KC_SLSH,KC_BSLS,
                                                KC_LALT,                         KC_ENT
    )
};

