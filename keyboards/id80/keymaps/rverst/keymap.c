#include "rverst.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , MO(4)  , KC_DEL ,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_PGUP,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN,
        KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC ,                            MO(1)  , KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,
        KC_NLCK, KC_P1  , KC_P2  , KC_P3  , KC_P4  , KC_P5  , KC_P6  , KC_P7  , KC_P8  , KC_P9  , KC_P0  , KC_PMNS, KC_PPLS, KC_TRNS, KC_VOLU,
        KC_TRNS, KC_TRNS, KC_TRNS, RV_EUR , KC_TRNS, KC_TRNS, KC_TRNS, RV_UUML, KC_TRNS, RV_OUML, KC_TRNS, KC_TRNS, KC_PEQL, KC_TRNS, KC_VOLD,
        KC_CAPS, RV_AUML, RV_SZ  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PDOT, KC_PSLS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_RGUI,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[2] = LAYOUT(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_TRNS, MO(4)  , KC_MUTE,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_VOLU,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_VOLD,
        KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC ,                            MO(3),                     KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,
        KC_NLCK, KC_P1  , KC_P2  , KC_P3  , KC_P4  , KC_P5  , KC_P6  , KC_P7  , KC_P8  , KC_P9  , KC_P0  , KC_PMNS, KC_PPLS, KC_TRNS, KC_VOLU,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_UUML, KC_TRNS, KC_TRNS, KC_TRNS, KC_PEQL, KC_TRNS, KC_VOLD,
        KC_CAPS, RV_AUML, KC_TRNS, RV_SZ  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_EUR , KC_TRNS, RV_OUML, KC_PAST, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PDOT, KC_PSLS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_RGUI,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[4] = LAYOUT(
        RESET  , RV_SM0 , RV_SM1 , RV_SM2 , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , DF(0)  , DF(2)  , KC_TRNS, MO(5)  ,
        KC_NO  , RV_SM3 , RV_SM4 , RV_SM5 , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_NO  ,
        KC_NO  , KC_NO  , GUI_ON ,                   KC_NO  ,                            KC_NO  , RCG_SWP,          KC_NO  , KC_NO  , KC_NO\
    ),
	[5] = LAYOUT(
        EEP_RST, RV_SM0S, RV_SM1S, RV_SM2S, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
        KC_NO  , RV_SM3S, RV_SM4S, RV_SM5S, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_NO  ,
        KC_NO  , KC_NO  , GUI_OFF,                   KC_NO  ,                            KC_NO  , RCG_NRM,          KC_NO  , KC_NO  , KC_NO
    )
};
// clang-format on
