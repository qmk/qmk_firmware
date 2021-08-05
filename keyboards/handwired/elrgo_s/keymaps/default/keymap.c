#include QMK_KEYBOARD_H


#define _QWERTY 0

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define ONE_GRV LT(1,KC_GRAVE)
#define CTL_Z LCTL_T(KC_Z)
#define ALT_SHFT LALT(KC_LSFT)
#define ALT_MENU LALT_T(KC_MENU)
#define LG_QUOT LGUI_T(KC_QUOT)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_SLS LCTL_T(KC_SLSH)
#define LT2_COL LT(_RAISE, KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_6x4(
        KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO ,                  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
        KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO ,                  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
        KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO ,                  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
                KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO ,                  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,       
    ),
};
