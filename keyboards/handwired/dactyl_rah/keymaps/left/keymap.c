#include QMK_KEYBOARD_H

#define BASE 0
#define NAV 1

#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_CAP LCTL_T(KC_CAPS)
#define CTL_SPC LCTL_T(KC_SPC)
#define ALT_BSP LALT_T(KC_BSPC)
#define LT_SLSH LT(NAV, KC_SLSH)
#define LT_Z LT(NAV, KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_6x6(
        KC_GRV , KC_1  ,KC_2   , KC_3  , KC_4  , KC_5  ,                                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_HOME,
        KC_TAB , KC_Q  ,KC_W   , KC_E  , KC_R  , KC_T  ,                                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
        CTL_CAP, KC_A  ,KC_S   , KC_D  , KC_F  , KC_G  ,                                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LSFT, LT_Z  ,KC_X   , KC_C  , KC_V  , KC_B  ,                                         KC_N  , KC_M  ,KC_COMM, KC_DOT,LT_SLSH,KC_RSFT,
        CTL_ESC,KC_MINS,KC_EQL ,KC_LBRC,KC_RBRC,                                                        KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,KC_END ,
                                                        TT(NAV),KC_DEL ,        KC_PGDN,KC_PGUP,
                                                                KC_LGUI,        KC_RGUI,
                                                KC_BSPC,CTL_ESC,KC_LALT,        KC_RALT,KC_ENT ,CTL_SPC
    ),
    [NAV] = LAYOUT_6x6(
         RESET , KC_NO ,KC_MPRV,KC_MPLY,KC_MNXT, KC_NO ,                                         KC_NO ,  KC_7 , KC_8  , KC_9  , KC_NO , RESET ,
        _______,KC_VOLU,KC_WBAK,KC_MS_U,KC_WFWD,KC_WH_U,                                         KC_NO ,  KC_4 , KC_5  , KC_6  , KC_NO , KC_F9 ,
        _______,KC_VOLD,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_D,                                         KC_PSLS, KC_1 , KC_2  , KC_3  ,KC_PAST, KC_F10,
         KC_NO , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_NO ,                                         KC_PMNS, KC_0 , KC_NO ,_______,KC_PPLS, KC_F11,
        _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 ,                                                        _______,_______,_______,_______, KC_F12,
                                                        _______,_______,        KC_END ,KC_HOME,
                                                                _______,        _______,
                                                KC_BTN1,KC_BTN2,_______,        ALT_BSP,_______,_______
    )
};
