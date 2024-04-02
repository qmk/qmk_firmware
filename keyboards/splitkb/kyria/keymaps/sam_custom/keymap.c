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
    _SHIFT,
    _MAGIC,
    _WINDOW,
};

// Macro enums
enum {
    UP_DIR
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TMUX_SCROLL,
    WIN_TAPDANCE,
    ALT_TAPDANCE,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void tmux_finished(tap_dance_state_t *state, void *user_data);
void tmux_reset(tap_dance_state_t *state, void *user_data);

// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYMBOL   MO(_SYMBOL)
#define NUMPAD   MO(_NUMPAD)
#define MAGIC    MO(_MAGIC)
#define WINDOW   MO(_WINDOW)
#define SHIFT    MO(_SHIFT)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// Tmux
#define TMUX_LEADER LCTL(KC_A)

// Tabs
#define CLOSE_TAB LCTL(KC_W)
#define REOPEN_TAB LCTL(LSFT(KC_T))

// General Linux
#define LINUX_COPY LCTL(LSFT(KC_C))
#define LINUX_PASTE LCTL(LSFT(KC_V))

// General Windows
#define TASK_MANAGER LCTL(LSFT(KC_ESC))

// Window Management
#define WMGMT_BASE LSFT(LALT(LCTL(KC_0)))
#define WMGMT_MONITOR_1 LALT(LGUI(LCTL(KC_1)))
#define WMGMT_MONITOR_2 LALT(LGUI(LCTL(KC_2)))
#define WMGMT_MONITOR_3 LALT(LGUI(LCTL(KC_3)))
#define WMGMT_MONITOR_4 LALT(LGUI(LCTL(KC_4)))
#define WMGMT_LEFT_50 LSFT(LALT(LCTL(KC_H)))
#define WMGMT_DOWN_50 LSFT(LALT(LCTL(KC_J)))
#define WMGMT_UP_50 LSFT(LALT(LCTL(KC_K)))
#define WMGMT_RIGHT_50 LSFT(LALT(LCTL(KC_L)))
#define WMGMT_PREV_MONITOR LSFT(LALT(LCTL(KC_M)))
#define WMGMT_NEXT_MONITOR LSFT(LALT(LCTL(KC_N)))
#define WMGMT_TOPLEFT LSFT(LALT(LCTL(KC_P)))
#define WMGMT_TOPRIGHT LSFT(LALT(LCTL(KC_MINUS)))
#define WMGMT_BOTTOMLEFT LSFT(LALT(LCTL(KC_SCLN)))
#define WMGMT_BOTTOMRIGHT LSFT(LALT(LCTL(KC_QUOTE)))
#define WMGMT_FULLSCREEN LSFT(LALT(LCTL(KC_F)))
#define WMGMT_NEXT_WALLPAPER LSFT(LALT(LCTL(KC_R)))
#define WMGMT_LEFT_33 LSFT(LALT(LCTL(KC_1)))
#define WMGMT_HCENTER_33 LSFT(LALT(LCTL(KC_2)))
#define WMGMT_RIGHT_33 LSFT(LALT(LCTL(KC_3)))
#define WMGMT_TOP_33 LSFT(LALT(LCTL(KC_4)))
#define WMGMT_VCENTER_33 LSFT(LALT(LCTL(KC_5)))
#define WMGMT_BOTTOM_33 LSFT(LALT(LCTL(KC_6)))
#define WMGMT_LEFT_66 LSFT(LALT(LCTL(KC_7)))
#define WMGMT_RIGHT_66 LSFT(LALT(LCTL(KC_8)))
#define WMGMT_CENTER LALT(LGUI(LCTL(KC_C)))

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────┬───┬───┬──────────────────┬──────────────────┬─────┐                                                                 ┌─────┬───┬───┬───┬───┬──────────────┐
//    │   tab   │ q │ w │        e         │        r         │  t  │                                                                 │  y  │ u │ i │ o │ p │      -       │
//    ├─────────┼───┼───┼──────────────────┼──────────────────┼─────┤                                                                 ├─────┼───┼───┼───┼───┼──────────────┤
//    │ CTL_ESC │ a │ s │        d         │        f         │  g  │                                                                 │  h  │ j │ k │ l │ ; │      '       │
//    ├─────────┼───┼───┼──────────────────┼──────────────────┼─────┼───────────────┬─────────────────┬─────────────────┬─────────────┼─────┼───┼───┼───┼───┼──────────────┤
//    │  lsft   │ z │ x │        c         │        v         │  b  │  OSL(NUMPAD)  │    CLOSE_TAB    │   REOPEN_TAB    │ OSL(SYMBOL) │  n  │ m │ , │ . │ / │ LT(SHIFT, \) │
//    └─────────┴───┴───┼──────────────────┼──────────────────┼─────┼───────────────┼─────────────────┼─────────────────┼─────────────┼─────┼───┼───┼───┴───┴──────────────┘
//                      │ TD(WIN_TAPDANCE) │ TD(ALT_TAPDANCE) │ ent │ OSM(MOD_LSFT) │ TD(TMUX_SCROLL) │ TD(TMUX_SCROLL) │    bspc     │ spc │ [ │ ] │
//                      └──────────────────┴──────────────────┴─────┴───────────────┴─────────────────┴─────────────────┴─────────────┴─────┴───┴───┘
[_QWERTY] = LAYOUT(
  KC_TAB  , KC_Q , KC_W , KC_E             , KC_R             , KC_T   ,                                                                   KC_Y   , KC_U    , KC_I    , KC_O   , KC_P    , KC_MINUS               ,
  CTL_ESC , KC_A , KC_S , KC_D             , KC_F             , KC_G   ,                                                                   KC_H   , KC_J    , KC_K    , KC_L   , KC_SCLN , KC_QUOTE               ,
  KC_LSFT , KC_Z , KC_X , KC_C             , KC_V             , KC_B   , OSL(NUMPAD)   , CLOSE_TAB       , REOPEN_TAB      , OSL(SYMBOL) , KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH , LT(SHIFT, KC_BACKSLASH),
                          TD(WIN_TAPDANCE) , TD(ALT_TAPDANCE) , KC_ENT , OSM(MOD_LSFT) , TD(TMUX_SCROLL) , TD(TMUX_SCROLL) , KC_BSPC     , KC_SPC , KC_LBRC , KC_RBRC
),

//    ┌─────┬──────┬──────┬────────────┬─────────────┬────────┐                         ┌────────┬──────┬──────┬──────┬──────┬────────┐
//    │ tab │ kp_1 │ kp_2 │    kp_3    │    kp_4     │  kp_5  │                         │  kp_6  │ kp_7 │ kp_8 │ kp_9 │ kp_0 │  kp_-  │
//    ├─────┼──────┼──────┼────────────┼─────────────┼────────┤                         ├────────┼──────┼──────┼──────┼──────┼────────┤
//    │     │      │      │            │             │        │                         │        │ kp_4 │ kp_5 │ kp_6 │ kp_* │  kp_+  │
//    ├─────┼──────┼──────┼────────────┼─────────────┼────────┼─────┬─────┬──────┬──────┼────────┼──────┼──────┼──────┼──────┼────────┤
//    │     │      │      │ LINUX_COPY │ LINUX_PASTE │        │     │     │ pscr │      │        │ kp_1 │ kp_2 │ kp_3 │      │ kp_ent │
//    └─────┴──────┴──────┼────────────┼─────────────┼────────┼─────┼─────┼──────┼──────┼────────┼──────┼──────┼──────┴──────┴────────┘
//                        │            │             │ kp_ent │     │     │      │ bspc │ kp_ent │ kp_. │ kp_. │
//                        └────────────┴─────────────┴────────┴─────┴─────┴──────┴──────┴────────┴──────┴──────┘
[_NUMPAD] = LAYOUT(
  KC_TAB  , KC_KP_1 , KC_KP_2 , KC_KP_3    , KC_KP_4     , KC_KP_5     ,                                         KC_KP_6     , KC_KP_7   , KC_KP_8   , KC_KP_9 , KC_KP_0        , KC_KP_MINUS,
  _______ , _______ , _______ , _______    , _______     , _______     ,                                         _______     , KC_KP_4   , KC_KP_5   , KC_KP_6 , KC_KP_ASTERISK , KC_KP_PLUS ,
  _______ , _______ , _______ , LINUX_COPY , LINUX_PASTE , _______     , _______ , _______ , KC_PSCR , _______ , _______     , KC_KP_1   , KC_KP_2   , KC_KP_3 , _______        , KC_KP_ENTER,
                                _______    , _______     , KC_KP_ENTER , _______ , _______ , _______ , KC_BSPC , KC_KP_ENTER , KC_KP_DOT , KC_KP_DOT
),

//    ┌─────┬───┬───┬─────┬─────┬───┐                       ┌──────┬──────┬─────┬──────┬───┬─────┐
//    │  `  │ ` │ { │  }  │  @  │ * │                       │  !   │  :   │  (  │  )   │ ; │     │
//    ├─────┼───┼───┼─────┼─────┼───┤                       ├──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ ^ │ = │  #  │  $  │ _ │                       │ left │ down │ up  │ rght │ ~ │     │
//    ├─────┼───┼───┼─────┼─────┼───┼─────┬─────┬─────┬─────┼──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ - │ < │  >  │  |  │ & │     │     │     │     │  %   │  +   │  [  │  ]   │ / │     │
//    └─────┴───┴───┼─────┼─────┼───┼─────┼─────┼─────┼─────┼──────┼──────┼─────┼──────┴───┴─────┘
//                  │     │     │ \ │  :  │  %  │     │     │      │      │     │
//                  └─────┴─────┴───┴─────┴─────┴─────┴─────┴──────┴──────┴─────┘
[_SYMBOL] = LAYOUT(
  KC_GRV  , KC_GRV        , KC_LCBR  , KC_RCBR , KC_AT   , KC_ASTR       ,                                             KC_EXCLAIM , KC_COLON , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_SCLN  , _______,
  _______ , KC_CIRCUMFLEX , KC_EQUAL , KC_HASH , KC_DLR  , KC_UNDERSCORE ,                                             KC_LEFT    , KC_DOWN  , KC_UP         , KC_RIGHT       , KC_TILDE , _______,
  _______ , KC_MINUS      , KC_LT    , KC_GT   , KC_PIPE , KC_AMPR       , _______  , _______    , _______ , _______ , KC_PERCENT , KC_PLUS  , KC_LBRC       , KC_RBRC        , KC_SLSH  , _______,
                                       _______ , _______ , KC_BACKSLASH  , KC_COLON , KC_PERCENT , _______ , _______ , _______    , _______  , _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐                       ┌──────┬──────┬──────┬──────┬─────┬─────┐
//    │  `  │  !  │  @  │  #  │  $  │  %  │                       │  ^   │  &   │  *   │  (   │  )  │  \  │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤                       ├──────┼──────┼──────┼──────┼─────┼─────┤
//    │     │     │     │     │     │     │                       │      │      │      │      │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┬─────┬─────┼──────┼──────┼──────┼──────┼─────┼─────┤
//    │     │     │     │     │     │     │     │     │     │     │ mply │ mute │ vold │ volu │     │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼──────┼──────┴─────┴─────┘
//                      │     │     │     │     │     │     │     │      │      │      │
//                      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴──────┴──────┴──────┘
[_SHIFT] = LAYOUT(
  KC_GRV  , KC_EXCLAIM , KC_AT   , KC_HASH , KC_DLR  , KC_PERCENT ,                                         KC_CIRCUMFLEX       , KC_AMPR , KC_ASTR , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_BACKSLASH,
  _______ , _______    , _______ , _______ , _______ , _______    ,                                         _______             , _______ , _______ , _______       , _______        , _______     ,
  _______ , _______    , _______ , _______ , _______ , _______    , _______ , _______ , _______ , _______ , KC_MEDIA_PLAY_PAUSE , KC_MUTE , KC_VOLD , KC_VOLU       , _______        , _______     ,
                                   _______ , _______ , _______    , _______ , _______ , _______ , _______ , _______             , _______ , _______
),

//    ┌─────┬─────┬─────────┬─────────┬────────────┬──────────────────┐                       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │     │         │         │            │     RGB_TOG      │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────────┼─────────┼────────────┼──────────────────┤                       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │ RGB_HUI │ RGB_SAI │  RGB_VAI   │ RGB_MODE_FORWARD │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────────┼─────────┼────────────┼──────────────────┼─────┬─────┬─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │ RGB_HUD │ RGB_SAD │  RGB_VAD   │ RGB_MODE_REVERSE │     │     │     │     │     │     │     │     │     │     │
//    └─────┴─────┴─────────┼─────────┼────────────┼──────────────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
//                          │         │ TG(_MAGIC) │                  │     │     │     │     │     │     │     │
//                          └─────────┴────────────┴──────────────────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_MAGIC] = LAYOUT(
  _______ , _______ , _______ , _______ , _______    , RGB_TOG          ,                                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , RGB_HUI , RGB_SAI , RGB_VAI    , RGB_MODE_FORWARD ,                                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , RGB_HUD , RGB_SAD , RGB_VAD    , RGB_MODE_REVERSE , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
                                _______ , TG(_MAGIC) , _______          , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────┬──────────────────┬──────────────────┬──────────────────────┬──────────────────┐                       ┌────────────────────┬────────────────────┬─────────────────┬─────────────────┬──────────────────┬───────────────────┐
//    │     │     │ WMGMT_FULLSCREEN │                  │ WMGMT_NEXT_WALLPAPER │   WMGMT_TOP_33   │                       │  WMGMT_MONITOR_1   │  WMGMT_MONITOR_2   │ WMGMT_MONITOR_3 │ WMGMT_MONITOR_4 │  WMGMT_TOPLEFT   │  WMGMT_TOPRIGHT   │
//    ├─────┼─────┼──────────────────┼──────────────────┼──────────────────────┼──────────────────┤                       ├────────────────────┼────────────────────┼─────────────────┼─────────────────┼──────────────────┼───────────────────┤
//    │     │     │  WMGMT_LEFT_33   │ WMGMT_HCENTER_33 │    WMGMT_RIGHT_33    │ WMGMT_VCENTER_33 │                       │   WMGMT_LEFT_50    │   WMGMT_DOWN_50    │   WMGMT_UP_50   │ WMGMT_RIGHT_50  │ WMGMT_BOTTOMLEFT │ WMGMT_BOTTOMRIGHT │
//    ├─────┼─────┼──────────────────┼──────────────────┼──────────────────────┼──────────────────┼─────┬─────┬─────┬─────┼────────────────────┼────────────────────┼─────────────────┼─────────────────┼──────────────────┼───────────────────┤
//    │     │     │  WMGMT_LEFT_66   │   WMGMT_CENTER   │    WMGMT_RIGHT_66    │ WMGMT_BOTTOM_33  │     │     │     │     │ WMGMT_PREV_MONITOR │ WMGMT_NEXT_MONITOR │                 │                 │                  │                   │
//    └─────┴─────┴──────────────────┼──────────────────┼──────────────────────┼──────────────────┼─────┼─────┼─────┼─────┼────────────────────┼────────────────────┼─────────────────┼─────────────────┴──────────────────┴───────────────────┘
//                                   │   TG(_WINDOW)    │                      │                  │     │     │     │     │                    │                    │   WMGMT_BASE    │
//                                   └──────────────────┴──────────────────────┴──────────────────┴─────┴─────┴─────┴─────┴────────────────────┴────────────────────┴─────────────────┘
[_WINDOW] = LAYOUT(
  _______ , _______ , WMGMT_FULLSCREEN , _______          , WMGMT_NEXT_WALLPAPER , WMGMT_TOP_33     ,                                         WMGMT_MONITOR_1    , WMGMT_MONITOR_2    , WMGMT_MONITOR_3 , WMGMT_MONITOR_4 , WMGMT_TOPLEFT    , WMGMT_TOPRIGHT   ,
  _______ , _______ , WMGMT_LEFT_33    , WMGMT_HCENTER_33 , WMGMT_RIGHT_33       , WMGMT_VCENTER_33 ,                                         WMGMT_LEFT_50      , WMGMT_DOWN_50      , WMGMT_UP_50     , WMGMT_RIGHT_50  , WMGMT_BOTTOMLEFT , WMGMT_BOTTOMRIGHT,
  _______ , _______ , WMGMT_LEFT_66    , WMGMT_CENTER     , WMGMT_RIGHT_66       , WMGMT_BOTTOM_33  , _______ , _______ , _______ , _______ , WMGMT_PREV_MONITOR , WMGMT_NEXT_MONITOR , _______         , _______         , _______          , _______          ,
                                         TG(_WINDOW)      , _______              , _______          , _______ , _______ , _______ , _______ , _______            , _______            , WMGMT_BASE
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Hold NUMPAD and SYMBOL layers to get to MAGIC
    switch (keycode) {
        case UP_DIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            break;
    }
    return true;
}

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

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
        oled_write_P(PSTR("Kyria rev3\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case _NUMPAD:
                oled_write_P(PSTR("Numpad\n"), false);
                break;
            case _SYMBOL:
                oled_write_P(PSTR("Symbol\n"), false);
                break;
            case _MAGIC:
                oled_write_P(PSTR("Magic\n"), false);
                break;
            case _WINDOW:
                oled_write_P(PSTR("Window\n"), false);
                break;
            case _SHIFT:
                oled_write_P(PSTR("Shift\n"), false);
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

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    return TD_UNKNOWN;
}

static td_tap_t tmuxtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void tmux_finished(tap_dance_state_t *state, void *user_data) {
    tmuxtap_state.state = cur_dance(state);
    switch (tmuxtap_state.state) {
        case TD_SINGLE_TAP: register_code16(LCTL(KC_A)); break;
        case TD_DOUBLE_TAP: register_code16(LCTL(KC_A)); unregister_code16(LCTL(KC_A)); tap_code(KC_LBRC); break;
        default: break;
    }
}
void tmux_reset(tap_dance_state_t *state, void *user_data) {
    switch (tmuxtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(LCTL(KC_A)); break;
        case TD_DOUBLE_TAP: break;
        default: break;
    }
    tmuxtap_state.state = TD_NONE;
}

static td_tap_t wintap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void win_finished(tap_dance_state_t *state, void *user_data) {
    wintap_state.state = cur_dance(state);
    switch (wintap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: layer_on(_WINDOW); break;
        default: break;
    }
}
void win_reset(tap_dance_state_t *state, void *user_data) {
    switch (wintap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: break;
        default: break;
    }
    wintap_state.state = TD_NONE;
}

static td_tap_t alttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void alt_finished(tap_dance_state_t *state, void *user_data) {
    alttap_state.state = cur_dance(state);
    switch (alttap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: layer_on(_MAGIC); break;
        default: break;
    }
}
void alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (alttap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LALT); break;
        case TD_DOUBLE_TAP: break;
        default: break;
    }
    alttap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TMUX_SCROLL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tmux_finished, tmux_reset),
    [WIN_TAPDANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, win_finished, win_reset),
    [ALT_TAPDANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
};

/*
const uint16_t PROGMEM dot_slash[] = {KC_DOT, KC_SLASH, COMBO_END};
combo_t key_combos[] = {
    COMBO(dot_slash, UP_DIR)
};
 */

/* layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUMPAD, _SYMBOL, _WINDOW);
    state = update_tri_layer_state(state, _NUMPAD, _SHIFT, _MAGIC);
    return state;
}; */
