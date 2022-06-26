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

#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    KN_CLK = SAFE_RANGE, //Knob Click
    KN_Scl,              //Knob is Mouse scroll
    KN_Vol,              //Knob is Volume
    KN_Zm,               //Knob is zoom (ctrl + & ctrl -)
    KN_Sel,              //Knob is select (shift-right & shift-left click is copy)
    KN_Arr,              //Knob is arrow (right, left)
    KN_AUD,              //When know is arrow this shift to up, down
};


#ifdef ENCODER_ENABLE

typedef enum knob_mode_e {
    KNOB_SCROLL = 0,
    KNOB_VOLUME,
    KNOB_ZOOM,
    KNOB_SELECT,
    KNOB_ARROW
} knob_mode;

const uint16_t PROGMEM knobMappings[][3] = { // (cw, ccw, click)
    [KNOB_SCROLL] = { KC_WH_U, KC_WH_D, KC_LSFT }, // Scroll Up, Scroll Down, Shift
    [KNOB_VOLUME] = { KC_VOLU, KC_VOLD, KC_MUTE }, // Vol Up, Vol Down, Mute
    [KNOB_ZOOM]   = { LGUI(LSFT(KC_EQUAL)), LGUI(KC_MINUS), LGUI(KC_0) },
    [KNOB_SELECT] = { LSFT(KC_RIGHT), LSFT(KC_LEFT), LGUI(KC_C) },
    [KNOB_ARROW]  = { LCTL(KC_RIGHT), LCTL(KC_LEFT), KN_AUD },
};

knob_mode defaultKnob = KNOB_SCROLL;

struct knob_state_s {
    knob_mode current;
    knob_mode atClick;
} knob_state;
#endif


#define _Def 0
#define _Fn  1
#define _Mo  2

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_Def] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KN_CLK,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, MO(_Fn), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_Fn] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,           KC_MPLY,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KN_Scl,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, RESET,            KN_Vol,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______,          KN_Zm,
        _______, _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          TG(_Mo),          RGB_MOD, KN_Sel,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_Mo] = LAYOUT(
        _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG(_Mo),          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    */

};
// clang-format on


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef ENCODER_ENABLE
        case KN_CLK: {
            uint16_t code = knobMappings[knob_state.current][2];
/*
            if (IS_MOD(code)) {
                uint8_t mods = (code >> 8) & 0xff;
                if (record->event.pressed)
                {
                    register_mods( mods );
                }
                else {
                    unregister_mods( mods );
                }

                return true;
            } else
            */
             {
                if (record->event.pressed) {
                    tap_code16(code);
                }
                return false;
            }
        }

        case KN_Scl:
        case KN_Vol:
        case KN_Zm:
        case KN_Sel: {
            int newMode = keycode - KN_Scl;
            if (record->event.pressed) {
                knob_state.current = newMode;
            }

            return false;
        }
#endif

        default:
            return true; //Process all other keycodes normally
    }
}


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    int fnIndex = clockwise ? 0 : 1;

    uint16_t code = knobMappings[knob_state.current][fnIndex];

    switch (knob_state.current) {
        default:
            tap_code16( code );
            break;
    };

    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    knob_state.current = KNOB_SCROLL;
};

/*
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};
*/

void rgb_matrix_indicators_user(void) {
    const int modeIndicatorLedIndex[] = { 72, 75, 86, 82, 69 };
    rgb_matrix_set_color( modeIndicatorLedIndex[knob_state.current], 25, 25, 255 );
}

#endif // ENCODER_ENABLE
