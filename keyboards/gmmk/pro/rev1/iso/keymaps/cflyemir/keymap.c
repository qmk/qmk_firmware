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
#include "version.h"

#include QMK_KEYBOARD_H

enum qmmk_layers {
    _COLEMAK,
    _QWERTY,
    _NUM,
   _SYM,
   _MEDIA,
   _NAV,
   _MOUSE,
   _FUN
};

enum custom_keycodes {
   VRSN = SAFE_RANGE,
   COLEMAK,
   QWERTY
};

enum unicode_names {
    AE_L,
    AE_U,
    OE_L,
    OE_U,
    AA_L,
    AA_U,
    IRONY,
    SNEK
};

const uint32_t unicode_map[] PROGMEM = {
    [AE_L]  = 0x00E6,  // æ
    [AE_U]  = 0x00C6,  // Æ
    [OE_L]  = 0x00F8,  // ø
    [OE_U]  = 0x00D8,  // Ø
    [AA_L]  = 0x00E5,  // å
    [AA_U]  = 0x00C5,  // Å
    [SNEK]  = 0x1F40D, // 🐍
};

#define KC_AE XP(AE_L,AE_U)
#define KC_OE XP(OE_L,OE_U)
#define KC_AA XP(AA_L,AA_U)

#define ESC_CTL LCTL_T(KC_ESC)
#define ENT_CTL LCTL_T(KC_ENT)
#define SPC_CTL LCTL_T(KC_SPC)

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

  // Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I RALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)


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
    
    // TODO: add base without homerow mod.
    [_COLEMAK] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TOG_WS,           KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_SLSH ,                  KC_PGUP,
        ESC_CTL, HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,    KC_AA,   KC_M,    HOME_N,  HOME_E,  HOME_I,  HOME_O,  KC_QUOT, ENT_CTL,          KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_AE,   KC_OE,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_RSFT,          KC_UP,   KC_END,
        KC_LGUI, MO(_MEDIA), MO(_NAV),                        KC_SPC,                       MO(_SYM), MO(_NUM), KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    _______, _______, _______, KC_N,    KC_E,    KC_I,    KC_O,    _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_LALT,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, KC_7  ,  KC_8  ,  KC_9  ,  _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, KC_4  ,  KC_5  ,  KC_6  ,  _______, _______, _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______, _______,          _______,
        _______, _______, KC_1  ,  KC_2  ,  KC_3  ,  _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_0,                              _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_QUOT, KC_LABK, KC_RABK, KC_DQUO, KC_GRV,  _______, KC_AMPR, KC_UNDS, KC_LBRC, KC_RBRC, KC_PERC, _______,                   _______,
        _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_HASH, XXXXXXX, KC_PIPE, KC_NO,   KC_LPRN, KC_RPRN, KC_QUES, _______, _______,          _______,
        _______, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, KC_NO,   XXXXXXX, XXXXXXX, KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_AT,            _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_FUN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL, VRSN,    _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______, _______,          _______,
        _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, QWERTY,  COLEMAK, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    
    [_MEDIA] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            KC_MPLY, KC_MSTP, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,   _______, U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   _______,                   _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, _______, CW_TOGG, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,           _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, _______, _______, _______, _______, U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   _______,                   _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, VRSN,    _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,          _______, _______,
        _______, _______, _______,                            _______,                            KC_BTN1, KC_BTN2, _______, _______, _______, _______
    ),
};
// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_COLEMAK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_QWERTY]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NUM]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_SYM]     = { ENCODER_CCW_CW(RGB_RMOD,RGB_MOD)},
    [_FUN]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_MEDIA]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NAV]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_MOUSE]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
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
    state = update_tri_layer_state(state, _NUM, _SYM, _FUN);
    state = update_tri_layer_state(state, _NAV, _MEDIA, _MOUSE);
    return state;
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