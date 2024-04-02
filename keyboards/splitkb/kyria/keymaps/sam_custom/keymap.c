/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NUMPAD,
    _SYMBOL,
    _MAGIC,
};

tap_dance_action_t tap_dance_actions[] = {};

// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYMBOL   MO(_SYMBOL)
#define NUMPAD   MO(_NUMPAD)
#define MAGIC    MO(_MAGIC)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define TMUX_LEADER LCTL(KC_A)
#define CLOSE_TAB LCTL(KC_W)
#define REOPEN_TAB LCTL(LSFT(KC_T))
#define LINUX_COPY LCTL(LSFT(KC_C))
#define LINUX_PASTE LCTL(LSFT(KC_V))

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────┬───┬───┬──────┬──────┬─────┐                                             ┌─────┬───┬───┬───┬───┬──────────────┐
//    │   tab   │ q │ w │  e   │  r   │  t  │                                             │  y  │ u │ i │ o │ p │      -       │
//    ├─────────┼───┼───┼──────┼──────┼─────┤                                             ├─────┼───┼───┼───┼───┼──────────────┤
//    │ CTL_ESC │ a │ s │  d   │  f   │  g  │                                             │  h  │ j │ k │ l │ ; │      '       │
//    ├─────────┼───┼───┼──────┼──────┼─────┼────────┬─────────────┬─────────────┬────────┼─────┼───┼───┼───┼───┼──────────────┤
//    │  lsft   │ z │ x │  c   │  v   │  b  │ NUMPAD │  CLOSE_TAB  │ REOPEN_TAB  │ SYMBOL │  n  │ m │ , │ . │ / │ LT(MAGIC, \) │
//    └─────────┴───┴───┼──────┼──────┼─────┼────────┼─────────────┼─────────────┼────────┼─────┼───┼───┼───┴───┴──────────────┘
//                      │ lgui │ lalt │ ent │  lsft  │ TMUX_LEADER │ TMUX_LEADER │  bspc  │ spc │ [ │ ] │
//                      └──────┴──────┴─────┴────────┴─────────────┴─────────────┴────────┴─────┴───┴───┘
[_QWERTY] = LAYOUT(
  KC_TAB  , KC_Q , KC_W , KC_E    , KC_R    , KC_T   ,                                                 KC_Y   , KC_U    , KC_I    , KC_O   , KC_P    , KC_MINUS               ,
  CTL_ESC , KC_A , KC_S , KC_D    , KC_F    , KC_G   ,                                                 KC_H   , KC_J    , KC_K    , KC_L   , KC_SCLN , KC_QUOTE               ,
  KC_LSFT , KC_Z , KC_X , KC_C    , KC_V    , KC_B   , NUMPAD  , CLOSE_TAB   , REOPEN_TAB  , SYMBOL  , KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH , LT(MAGIC, KC_BACKSLASH),
                          KC_LGUI , KC_LALT , KC_ENT , KC_LSFT , TMUX_LEADER , TMUX_LEADER , KC_BSPC , KC_SPC , KC_LBRC , KC_RBRC
),

//    ┌─────┬──────┬──────┬────────────┬─────────────┬────────┐                        ┌────────┬──────┬──────┬──────┬──────┬────────┐
//    │ tab │ kp_1 │ kp_2 │    kp_3    │    kp_4     │  kp_5  │                        │  kp_6  │ kp_7 │ kp_8 │ kp_9 │ kp_0 │  kp_-  │
//    ├─────┼──────┼──────┼────────────┼─────────────┼────────┤                        ├────────┼──────┼──────┼──────┼──────┼────────┤
//    │     │      │      │            │             │        │                        │        │ kp_4 │ kp_5 │ kp_6 │ kp_* │  kp_+  │
//    ├─────┼──────┼──────┼────────────┼─────────────┼────────┼─────┬─────┬─────┬──────┼────────┼──────┼──────┼──────┼──────┼────────┤
//    │     │      │      │ LINUX_COPY │ LINUX_PASTE │        │     │     │     │      │        │ kp_1 │ kp_2 │ kp_3 │      │ kp_ent │
//    └─────┴──────┴──────┼────────────┼─────────────┼────────┼─────┼─────┼─────┼──────┼────────┼──────┼──────┼──────┴──────┴────────┘
//                        │            │             │ kp_ent │     │     │     │ bspc │ kp_ent │ kp_. │ kp_. │
//                        └────────────┴─────────────┴────────┴─────┴─────┴─────┴──────┴────────┴──────┴──────┘
[_NUMPAD] = LAYOUT(
  KC_TAB  , KC_KP_1 , KC_KP_2 , KC_KP_3    , KC_KP_4     , KC_KP_5     ,                                         KC_KP_6     , KC_KP_7   , KC_KP_8   , KC_KP_9 , KC_KP_0        , KC_KP_MINUS,
  _______ , _______ , _______ , _______    , _______     , _______     ,                                         _______     , KC_KP_4   , KC_KP_5   , KC_KP_6 , KC_KP_ASTERISK , KC_KP_PLUS ,
  _______ , _______ , _______ , LINUX_COPY , LINUX_PASTE , _______     , _______ , _______ , _______ , _______ , _______     , KC_KP_1   , KC_KP_2   , KC_KP_3 , _______        , KC_KP_ENTER,
                                _______    , _______     , KC_KP_ENTER , _______ , _______ , _______ , KC_BSPC , KC_KP_ENTER , KC_KP_DOT , KC_KP_DOT
),

//    ┌─────┬───┬───┬─────┬─────┬───┐                       ┌──────┬──────┬─────┬──────┬───┬─────┐
//    │  `  │ ` │ { │  }  │  @  │ * │                       │  !   │  :   │  (  │  )   │ ; │     │
//    ├─────┼───┼───┼─────┼─────┼───┤                       ├──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ ^ │ = │  #  │  $  │ _ │                       │ left │ down │ up  │ rght │ ~ │     │
//    ├─────┼───┼───┼─────┼─────┼───┼───┬─────┬─────┬───────┼──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ - │ < │  >  │  |  │ & │ / │     │     │ TO(0) │  %   │  +   │  [  │  ]   │ / │     │
//    └─────┴───┴───┼─────┼─────┼───┼───┼─────┼─────┼───────┼──────┼──────┼─────┼──────┴───┴─────┘
//                  │     │     │ \ │ : │  %  │     │       │      │      │     │
//                  └─────┴─────┴───┴───┴─────┴─────┴───────┴──────┴──────┴─────┘
[_SYMBOL] = LAYOUT(
  KC_GRV  , KC_GRV        , KC_LCBR  , KC_RCBR , KC_AT   , KC_ASTR       ,                                             KC_EXCLAIM , KC_COLON , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_SCLN  , _______,
  _______ , KC_CIRCUMFLEX , KC_EQUAL , KC_HASH , KC_DLR  , KC_UNDERSCORE ,                                             KC_LEFT    , KC_DOWN  , KC_UP         , KC_RIGHT       , KC_TILDE , _______,
  _______ , KC_MINUS      , KC_LT    , KC_GT   , KC_PIPE , KC_AMPR       , KC_SLASH , _______    , _______ , TO(0)   , KC_PERCENT , KC_PLUS  , KC_LBRC       , KC_RBRC        , KC_SLSH  , _______,
                                       _______ , _______ , KC_BACKSLASH  , KC_COLON , KC_PERCENT , _______ , _______ , _______    , _______  , _______
),

//    ┌─────┬─────┬─────────┬─────────┬─────────┬──────────────────┐                       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │     │         │         │         │     RGB_TOG      │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────────┼─────────┼─────────┼──────────────────┤                       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │ RGB_HUI │ RGB_SAI │ RGB_VAI │ RGB_MODE_FORWARD │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────────┼─────────┼─────────┼──────────────────┼─────┬─────┬─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │ RGB_HUD │ RGB_SAD │ RGB_VAD │ RGB_MODE_REVERSE │     │     │     │     │     │     │     │     │     │     │
//    └─────┴─────┴─────────┼─────────┼─────────┼──────────────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
//                          │         │         │                  │     │     │     │     │     │     │     │
//                          └─────────┴─────────┴──────────────────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_MAGIC] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , RGB_TOG          ,                                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , RGB_HUI , RGB_SAI , RGB_VAI , RGB_MODE_FORWARD ,                                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , RGB_HUD , RGB_SAD , RGB_VAD , RGB_MODE_REVERSE , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
                                _______ , _______ , _______          , _______ , _______ , _______ , _______ , _______ , _______ , _______
)
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _DVORAK:
                oled_write_P(PSTR("Dvorak\n"), false);
                break;
            case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */
