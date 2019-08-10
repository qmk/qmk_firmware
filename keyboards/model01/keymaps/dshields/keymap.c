#include QMK_KEYBOARD_H

enum { DEF, FUN };
enum { DYNAMIC_MACRO_RANGE = SAFE_RANGE };

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT(
    RESET  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
    KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , RGB_TOG,    DM_PLAY, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
    KC_PGUP, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_TAB ,    KC_ENT , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    KC_PGDN, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ESC ,    _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
                                           OSMLCTL,                                 KC_RCTL,
                                              KC_BSPC,                           KC_SPC ,
                                                 KC_LGUI,                     OSMRALT,
                                                    OSMLSFT,               OSMRSFT,
                                        OSL_FUN,                                        OSL_FUN
    ),
[FUN] = LAYOUT(
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    KC_TAB , _______, KC_MS_U, _______, KC_BTN3, _______, RGB_MOD,    DM_STRT, _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_F12 ,
    KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______, _______,    DM_STOP, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
    KC_END , KC_PSCR, KC_INS , _______, KC_BTN2, _______, _______,    _______, _______, _______, _______, _______, KC_BSLS, KC_PIPE,
                                           _______,                                 _______,
                                              KC_DEL ,                           KC_ENT ,
                                                 _______,                     _______,
                                                    _______,               _______,
                                        _______,                                        _______
    )
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case DEF:
            set_all_leds_to(0,0,0);
            break;
        case FUN:
            // TODO light the fn keys
            // set_led_to(?, 0, 128, 0);
            // set_led_to(?, 0, 128, 0);
            break;
    }
    return state;
}

/*
void matrix_init_user(void) {
    eeconfig_init();
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}

