#include QMK_KEYBOARD_H

#include "pcoves.h"
#include "tapDance.h"

#define LAYER_0 0

#define L1_SPC LT(1, KC_SPC)
#define SFT_ENT SFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//clang-format off
[LAYER_0] = LAYOUT_buzzsaw(
        KC_ESC   , KC_GRAVE , KC_1    , KC_2     , KC_3 , KC_4   , KC_5 , /**/ KC_6 , KC_7      , KC_8     , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_BSPC , KC_DEL ,
        KC_TAB   , KC_Q     , KC_W    , KC_E     , KC_R , KC_T          , /**/ KC_Y , KC_U      , KC_I     , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_BSLS , KC_PGUP ,
        TD(CTRL) , KC_A     , KC_S    , KC_D     , KC_F , KC_G          , /**/ KC_H , KC_J      , KC_K     , KC_L    , KC_SCLN , KC_QUOT , KC_ENT  , /*******/ KC_PGDN ,
        KC_LSPO  , KC_Z     , KC_X    , KC_C     , KC_V , KC_B          , /**/ KC_N , KC_M      , KC_COMM  , KC_DOT  , KC_SLSH , KC_RSPC , /*******/ KC_UP   ,
                              KC_LGUI   , TD(ALT)  , SFT_ENT , TD(LEFT) , /**/ TD(RIGHT) , L1_SPC , /***********************************/ KC_LEFT , KC_DOWN  , KC_RIGHT
        )
};
//clang-format on
