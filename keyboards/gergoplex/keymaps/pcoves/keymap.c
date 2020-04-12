#include QMK_KEYBOARD_H

#include "pcoves.h"
#include "tapDance.h"

#define LAYER_0 0
#define LAYER_1 1

#define L1_SPC LT(LAYER_1, KC_SPC)

#define CTL_A CTL_T(KC_A)
#define CTL_SCLN CTL_T(KC_SCLN)

#define SFT_Z SFT_T(KC_Z)
#define SFT_SLSH SFT_T(KC_SLSH)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_0] = LAYOUT_gergoplex(
        KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , /**/ KC_Y     , KC_U    , KC_I    , KC_O    , KC_P     ,
        CTL_A   , KC_S    , KC_D    , KC_F    , KC_G    , /**/ KC_H     , KC_J    , KC_K    , KC_L    , CTL_SCLN ,
        SFT_Z   , KC_X    , KC_C    , KC_V    , KC_B    , /**/ KC_N     , KC_M    , KC_COMM , KC_DOT  , SFT_SLSH ,
                            TD(ALT), KC_SFTENT, TD(LEFT), /**/ TD(RIGHT), L1_SPC, KC_RGUI
        ),
[LAYER_1] = LAYOUT_gergoplex(
        KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , /**/ KC_6    , KC_7    , KC_8    , KC_9    , KC_0     ,
        _______ , KC_HOME , KC_PGDN , KC_PGUP , KC_END  , /**/ KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______  ,
#if SECRET_ENABLE
        SECRET0 , SECRET1 , SECRET2 , SECRET3 , SECRET4 , /**/ EMOTE0  , EMOTE1  , EMOTE2  , EMOTE3  , AUTRUCHE ,
#else
        _______ , _______ , _______ , _______ , _______ , /**/ EMOTE0  , EMOTE1  , EMOTE2  , EMOTE3  , AUTRUCHE ,
#endif
                               _______, _______, _______, /**/ _______, _______, _______
    ),
};
//clang-format on
