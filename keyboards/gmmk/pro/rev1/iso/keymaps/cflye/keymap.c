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
#include "keymap_danish.h"
#include "version.h"

#include QMK_KEYBOARD_H

enum qmmk_layers {
    _COLEMAK,
    _QWERTY,
    _LOWER,
   _RAISE,
   _ADJUST,
};

enum custom_keycodes {
   VRSN = SAFE_RANGE,
   COLEMAK,
   QWERTY
};

#define ESC_CTL LCTL_T(KC_ESC)
#define ENT_CTL LCTL_T(KC_ENT)
#define SPC_CTL LCTL_T(KC_SPC)

#define TOG_WS MT(MOD_LGUI | MOD_LSFT, KC_PSCR)

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

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.

    [_COLEMAK] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TOG_WS,           KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX, KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_RBRC,                   KC_PGUP,
        ESC_CTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    DK_ARNG, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_NUHS, ENT_CTL,          KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    DK_AE,   DK_OSTR, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_RSFT,          KC_UP,   KC_END,
        KC_LALT, KC_LGUI, MO(_LOWER),                            KC_SPC,                           MO(_RAISE), KC_LGUI, KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, _______,                   _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, _______, _______,          _______,
        _______, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______, _______,          _______,
        _______, _______, _______, KC_UP,   _______, _______, _______, _______, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, _______,                   _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_P4  , KC_P5  , KC_P6  , KC_DOT,  DK_COLN, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1  , KC_P2  , KC_P3  , _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, KC_P0, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, DK_EXLM, DK_AT,   DK_HASH, DK_DLR,  DK_PERC, _______, DK_CIRC, DK_AMPR, DK_ASTR, DK_MINS, DK_UNDS, _______,                   _______,
        _______, DK_GRV,  DK_LCBR, DK_LBRC, DK_LPRN, DK_LABK, XXXXXXX, DK_QUOT, DK_DQUO, DK_QUES, DK_PLUS, DK_SCLN, DK_COLN, _______,          _______,
        _______, DK_TILD, DK_RCBR, DK_RBRC, DK_RPRN, DK_RABK, XXXXXXX, XXXXXXX, DK_EQL,  DK_BSLS, DK_SLSH, DK_PIPE, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    
    [_ADJUST] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, KC_MS_U, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______,                   _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, VRSN,   _______, KC_MPRV, KC_MNXT, KC_VOLU,  _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, KC_BTN2, QWERTY,  COLEMAK,_______, KC_MSTP, KC_MPLY, KC_VOLD,  _______,          RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
};
// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};  
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
        switch (keycode) {
            case QWERTY: 
                set_single_persistent_default_layer(_QWERTY);
                return false;   
            case COLEMAK: 
                set_single_persistent_default_layer(_COLEMAK);
                return false;      
            case VRSN:
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
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