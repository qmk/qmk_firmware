#include QMK_KEYBOARD_H
#include "dshields.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT(
    QK_BOOT, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , RGB_TOG,    DM_REC1, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
    KC_PGUP, MT_A   , MT_S   , MT_D   , MT_F   , LT_G   , KC_TAB ,    KC_ENT , LT_H   , MT_J   , MT_K   , MT_L   , MT_SCLN, KC_QUOT,
    KC_PGDN, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ESC ,    DM_PLY1, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
                                           OSMLCTL,                                 OSMRCTL,
                                              KC_BSPC,                           KC_SPC ,
                                                 KC_LGUI,                     OSMRALT,
                                                    OSMLSFT,               OSMRSFT,
                                        OSL_FUN,                                        OSL_FUN
    ),
[FUN] = LAYOUT(
    EE_CLR,  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    KC_TAB , _______, KC_MS_U, _______, KC_BTN3, _______, RGB_MOD,    DM_REC2, _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_F12 ,
    KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______, RGB_HUI,    DM_RSTP, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
    KC_END , KC_PSCR, KC_INS , _______, KC_BTN2, _______, RGB_HUD,    DM_PLY2, _______, _______, _______, _______, KC_BSLS, KC_PIPE,
                                           _______,                                 _______,
                                              KC_DEL ,                           KC_ENT ,
                                                 _______,                     _______,
                                                    _______,               _______,
                                        _______,                                        _______
    )
};

