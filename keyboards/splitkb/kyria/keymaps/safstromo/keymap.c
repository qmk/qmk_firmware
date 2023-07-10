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
    _COLEMAK_DH = 0,
    _QWERTY,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};

enum custom_keycodes {
    ARROW = SAFE_RANGE,
    ARROW_EQL,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define ALT_GUI  MT(MOD_LALT, KC_LGUI)
#define COPY     LCTL(KC_C)
#define PASTE    LCTL(KC_V)


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |alt(R)|sft(S)|ctl(T)|   G  |                              |   M  |ctl(N)|sft(E)|alt(I)|   O  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  | [ {  |CapsLk|  |F-keys|  ] } |   K  |   H  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI/| Sym  | Space| Copy |  | Paste| Enter| Nav  | AltGr|Browse|
 *                        |      | ALT  |      |      |      |  |      |      |      |      |search|
 *                        `----------------------------------'  `----------------------------------'
 */
[_COLEMAK_DH] = LAYOUT(
        KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_BSPC,
        CTL_ESC , KC_A ,  LALT_T(KC_R)   ,  LSFT_T(KC_S)  ,  LCTL_T(KC_T) , KC_G ,     KC_M,   RCTL_T(KC_N) ,  RSFT_T(KC_E) ,   LALT_T(KC_I) ,  KC_O , CTL_QUOT,
        KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , _______ ,KC_CAPS,         FKEYS  , KC_RBRC, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                        ADJUST, ALT_GUI, SYM, KC_SPC , COPY   ,         PASTE , KC_ENT , NAV , KC_RALT, KC_WSCH
),

/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI/| Sym  | Space| Copy |  | Paste| Enter| Nav  | AltGr|Browse|
 *                        |      | ALT  |      |      |      |  |      |      |      |      |search|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                    ADJUST, ALT_GUI, SYM, KC_SPC , COPY   ,         PASTE    , KC_ENT , NAV , KC_RALT, KC_WSCH
    ),

/*
 * Nav/Num Layer: Numbers, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  PrtSc |   1  |   2  |  3   |  4   |  5   |                              |   6  |   7  |   8  |   9  |  0   | Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Shift| CTRL |      |                              | PgUp |  ←   |   ↓  |   ↑  | →    | Backspc|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | PgDn | Home |  End |Insert|Delete| Backspc|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |F-keys|      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      KC_PSCR,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                     KC_6   ,  KC_7  ,  KC_8  , KC_9 ,  KC_0  , KC_DEL,
      _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,                                     KC_PGUP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSPC,
      _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PGDN , KC_HOME, KC_END , KC_INS, KC_DEL, KC_BSPC,
                                 _______, _______, FKEYS  , _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  [   |  ]   |  &   |  *   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  "   |  '   |  |   |                              |   _  |  {   |  }   |  =   |Bckspc|   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   ~  |   `  |   |  |  \   |   \  |  {   |      |  |      |   }  |   -  |  (   |  )   |  +   |   /   |   ?   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |F-keys|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      KC_GRV  , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, KC_ASTR, KC_EQL ,
      KC_TILD , KC_EXLM,  KC_AT , LSFT(RALT(KC_DQT)), RALT(KC_QUOT), KC_PIPE,                          KC_UNDS, KC_LCBR, KC_RCBR, KC_EQL , KC_BSPC, KC_PLUS,
      KC_PIPE , KC_TILD, KC_TILD, KC_GRV, KC_PIPE, KC_BSLS, KC_LCBR, _______, _______, KC_RCBR,  KC_MINS, KC_LPRN, KC_RPRN, KC_PPLS, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______, _______, _______, FKEYS   , _______, _______
    ),

/*
 * Function/media Layer: Function/media keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Shift| Ctrl |  Alt |  GUI |      |                              |      | Shift| Ctrl |  Alt |  GUI |  F12   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | Play |Vol Up|Vol DN| Mute |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                                      KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 ,
      _______,  KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,                                     _______, KC_RCTL, KC_LSFT, KC_LALT, KC_RGUI, KC_F12 ,
      _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, COLEMAK, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

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
        oled_write_P(PSTR("Kyria\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Nav/Num\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case 4:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case 5:
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
        // Window tab
        if (clockwise) {
            tap_code16(C(KC_TAB));
        } else {
            tap_code16(S(C(KC_TAB)));
        }
    } else if (index == 1) {
        // Mouse scroll
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    return false;
}
#endif

const uint16_t PROGMEM backspace_combo[] = {RCTL_T(KC_N), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM a_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ae_combo[] = {RSFT_T(KC_E), LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM lprn_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lcbr_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rcbr_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM under_combo[] = {KC_M, KC_K, COMBO_END};
const uint16_t PROGMEM arrow_combo[] = {LCTL_T(KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM arroweql_combo[] = {KC_P, KC_B, COMBO_END};
combo_t key_combos[] = {
        COMBO(backspace_combo, KC_BSPC),
        COMBO(esc_combo, KC_ESC),
        COMBO(tab_combo, KC_TAB),
        COMBO(del_combo, KC_DEL),
        COMBO(ae_combo, RALT(KC_Q)),
        COMBO(oe_combo, RALT(KC_P)),
        COMBO(a_combo, RALT(KC_W)),
        COMBO(lprn_combo, KC_LPRN),
        COMBO(lcbr_combo, KC_LCBR),
        COMBO(rprn_combo, KC_RPRN),
        COMBO(rcbr_combo, KC_RCBR),
        COMBO(under_combo, KC_UNDS),
        COMBO(arrow_combo, ARROW),
        COMBO(arroweql_combo, ARROW_EQL),
};
void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;

        case ARROW_EQL:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
    }
    return true;
};