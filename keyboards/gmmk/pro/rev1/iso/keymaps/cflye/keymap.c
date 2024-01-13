/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "cflye.h"

#define LAYOUT_gmmk_pro_iso_wrapper(...) LAYOUT(__VA_ARGS__)

#define TOG_WS MT(MOD_LGUI | MOD_LSFT, KC_PSCR)
#define ESC_CTL LCTL_T(KC_ESC)

#undef _________________THUMB_RIGHT_______________
#define _________________THUMB_RIGHT_______________       LT(_FUN,KC_DEL),  LT(_SYM,KC_TAB),   LT(_NUM,KC_TAB),   KC_NO,              KC_NO

#define LAYOUT_gmmk_pro_iso_base(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
) \
LAYOUT_gmmk_pro_iso_wrapper(\
    KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   QK_BOOT,          KC_MPLY,\
    KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,          KC_DEL,\
    KC_TAB,     K00,     K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,     KC_LBRC, KC_RBRC,                    KC_PGUP,\
    KC_LCTL,    K10,     K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     KC_QUOT, KC_NUHS,  KC_ENT,           KC_PGDN,\
    KC_LSFT,    K20,     K21,     K22,     K23,     K24,     _______, K25,     K26,     K27,     K28,     K29,               KC_RSFT, KC_UP,   KC_END,\
    KC_LCTL,    KC_LGUI, LT(_NAV,KC_ESC),                KC_SPC,                       K36, K37,                   KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT\
)

#define LAYOUT_gmmk_pro_iso_gaming(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
) \
LAYOUT_gmmk_pro_iso_wrapper(\
    KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT,     KC_MPLY,\
    KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,     KC_DEL,\
    KC_TAB,     K00,     K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,     KC_AA,   XXX,                  KC_PGUP,\
    KC_LSFT,    K10,     K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     KC_AE,   KC_OE,   KC_NUHS,     KC_ENT,  KC_PGDN,\
    KC_LCTL,    KC_NUBS, K20,     K21,     K22,     K23,     K24,     K25,     K26,     K27,     K28,     K29,     KC_LSFT,     KC_UP,   KC_END,\
    KC_LCTL,    KC_LGUI, KC_LALT,                         KC_SPC,                       K36, K37, KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT\
)

#define LAYOUT_base_wrapper(...) LAYOUT_gmmk_pro_iso_base(__VA_ARGS__)
#define LAYOUT_gaming_wrapper(...) LAYOUT_gmmk_pro_iso_gaming(__VA_ARGS__)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
//      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

// ┌ ┐ ─ ┬ ┴ ├ ┼ ┤ └ ┘

// └────────┘               1u
// └──────────┘             1.25u
// └────────────┘           1.5u
// └────────────────┘       2u
/*

 KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,    TG(_CL),                  KC_MUTE,
└────────┘  └────────┴────────┴────────┴────────┘ └────────┴────────┴────────┴────────┘ └────────┴────────┴────────┴────────┘ └────────┘               └────────┘
 
 KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,             KC_DEL,
└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└──┬─────────────┤   └────────┘
 NUM_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                     KC_PGUP,
└──────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘  |                ├────────┤
 ESC_CTL,      KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    ENT_CTL,       KC_PGDN,
└────────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────────┘   ├────────┤
 KC_LSFT,  KC_NUBS,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,          KC_UP,      KC_END,
└─────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────┘└────────────┘    └────────┘  └────────┘
 KC_LCTL,   KC_LGUI,   KC_LALT,                          KC_SPC,                                   MO(_SL),  MO(_FL),  KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT
└─────────┘└─────────┘└─────────┘└───────────────────────────────────────────────────────────────┘└────────┘└────────┘└────────┘ └────────┘└────────┘└────────┘

TODO: hold print to hold win+lshift (to then press s for snippet, c for color)
https://docs.qmk.fm/#/one_shot_keys - to tap for symbols

*/
[_BASE] = LAYOUT_base_wrapper(
    _________________COLEMAK_L1_________________, _________________COLEMAK_R1_________________,
    _________________COLEMAK_L2_________________, _________________COLEMAK_R2_________________,
    _________________COLEMAK_L3_________________, _________________COLEMAK_R3_________________,
    _________________THUMB_LEFT________________,  _________________THUMB_RIGHT_______________
),
[_GAMING] = LAYOUT_gaming_wrapper(
    _________________GAMING_L1__________________, _________________GAMING_R1__________________,
    _________________GAMING_L2__________________, _________________GAMING_R2__________________,
    _________________GAMING_L3__________________, _________________GAMING_R3__________________,
    _________________THUMB_LEFT________________,  _________________THUMB_RIGHT_______________
),
[_SYM] = LAYOUT_base_wrapper(
    ___________________SYM_L1___________________, ___________________SYM_R1___________________,
    ___________________SYM_L2___________________, ___________________SYM_R2___________________,
    ___________________SYM_L3___________________, ___________________SYM_R3___________________,
    ___________________BLANK___________________,  ___________________BLANK___________________
),
[_NUM] = LAYOUT_base_wrapper(
    ___________________NUM_L1___________________, ___________________NUM_R1___________________,
    ___________________NUM_L2___________________, ___________________NUM_R2___________________,
    ___________________NUM_L3___________________, ___________________NUM_R3___________________,
    ___________________NUM_L4___________________,  ___________________BLANK___________________
),
[_FUN] = LAYOUT_base_wrapper(
    ___________________FUN_L1___________________, ___________________FUN_R1___________________,
    ___________________FUN_L2___________________, ___________________FUN_R2___________________,
    ___________________FUN_L3___________________, ___________________FUN_R3___________________,
    ___________________FUN_L4___________________, ___________________FUN_R4___________________
),
[_MEDIA] = LAYOUT_base_wrapper(
    __________________MEDIA_L1__________________, __________________MEDIA_R1__________________,
    __________________MEDIA_L2__________________, __________________MEDIA_R2__________________,
    __________________MEDIA_L3__________________, __________________MEDIA_R3__________________,
    __________________MEDIA_L4__________________, __________________MEDIA_R4__________________
),
[_NAV] = LAYOUT_base_wrapper(
    ___________________NAV_L1___________________, ___________________NAV_R1___________________,
    ___________________NAV_L2___________________, ___________________NAV_R2___________________,
    ___________________NAV_L3___________________, ___________________NAV_R3___________________,
    ___________________NAV_L4___________________, ___________________NAV_R4___________________
),
[_MOUSE] = LAYOUT_base_wrapper(
    __________________MOUSE_L1__________________, __________________MOUSE_R1__________________,
    __________________MOUSE_L2__________________, __________________MOUSE_R2__________________,
    __________________MOUSE_L3__________________, __________________MOUSE_R3__________________,
    __________________MOUSE_L4__________________, __________________MOUSE_R4__________________
),

};
// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_GAMING]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_NUM]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_SYM]     = { ENCODER_CCW_CW(RGB_RMOD,RGB_MOD)},
    [_FUN]     = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [_MEDIA]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NAV]     = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_MOUSE]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};  
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUM, _SYM, _FUN);
    state = update_tri_layer_state(state, _NAV, _MEDIA, _MOUSE);
    return state;
}


/*


[1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_LALT,                            KC_SPC,                             KC_RALT, _______, _______, _______, _______, _______
    ),
*/