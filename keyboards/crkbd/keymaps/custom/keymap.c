/*
Copyright 2022 x123 <@x123>
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
#include "keycodes.h"

enum layer_names {
    _DEFAULT,
    _GAMER,
    _NO_HOMEROW,
    _NUMS,
    _SYMS,
    _ONESHOT,
    _NAVI
};

enum custom_keycodes {
  SMTD_KEYCODES_BEGIN = SAFE_RANGE,
  CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
  CKC_S,
  CKC_D,
  CKC_F,
  CKC_J, // reads as C(ustom) + KC_A, but you may give any name here
  CKC_K,
  CKC_L,
  CKC_SCLN,
  CKC_NUMS,
  CKC_SYMS,
  SMTD_KEYCODES_END,
  GAMER,
  COLEMAK,
  COLEMAK_NOHOMEROW,
  ADJUST,
  ONESHOT,
  DT_UP_50,
  DT_DOWN_50,
  DT_UP_X2,
  DT_DOWN_X2,
  DT_200,
  DT_MAX,
  ALT_TAB,
  ALT_F4,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ENTER_CLOSE_TAB,
  TAB_CLOSE,
  TURBO_MODIFIER,
  TURBO_UP,
  TURBO_DOWN,
  TURBO_LEFT,
  TURBO_RIGHT,
  SNAP_TAP_A,
  SNAP_TAP_D,
  TAP_DOWN,
  TAP_UP,
  SEQ_DOWN,
  SEQ_UP,
  FOLLOW_DOWN,
  FOLLOW_UP,
  RELEASE_DOWN,
  RELEASE_UP,
};

#include "sm_td.h"

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
bool supascroll_active = false; // For supascrolling
uint16_t alt_tab_timer = 0;     // we will be using them soon.
uint16_t turbo_threshold = 5; // Delay in ms between pressing the up/down keys during turbo mode.
uint16_t caps_timer = 0;

#define LSFT_KA LSFT_T(KC_A)
#define LCTL_KS LCTL_T(KC_S)
#define LGUI_KD LGUI_T(KC_D)
#define LALT_KF LALT_T(KC_F)
#define LALT_KJ LALT_T(KC_J)
#define RGUI_KK RGUI_T(KC_K)
#define RCTL_KL RCTL_T(KC_L)
#define RS_SCLN RSFT_T(KC_SCLN)

#define LCTL_KR LCTL_T(KC_R)
#define LGUI_KS LGUI_T(KC_S)
#define LALT_KT LALT_T(KC_T)
#define LALT_KN LALT_T(KC_N)
#define RGUI_KE RGUI_T(KC_E)
#define RCTL_KI RCTL_T(KC_I)
#define RSFT_KO RSFT_T(KC_O)

#define LOWSPC_MO LT(_NUMS, KC_SPC)
#define RAISPC_MO LT(_SYMS, KC_SPC)
#define ONESHOT_RALT LT(_ONESHOT, KC_RALT)
#define LOWSHIFT_CAPS MT(MOD_LSFT, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
       TAB_CLOSE,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_ESC, CKC_A, CKC_S, CKC_D, CKC_F,    KC_G,                               KC_H, CKC_J, CKC_K, CKC_L, CKC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                 KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, ENTER_CLOSE_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          QK_LEAD, ALT_TAB, CKC_NUMS,        CKC_SYMS,   MO(_NAVI), MO(_ONESHOT)
                                      //`--------------------------'        `--------------------------'
  ),

#ifdef BIG_MEMORY
   [_GAMER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
       KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TAB, KC_A, KC_S, KC_D, KC_F,    KC_G,                                          KC_H, LALT_KJ, RGUI_KK, RCTL_KL, RS_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LEFT_SHIFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                                KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_SPC,        RAISPC_MO,   MO(_NAVI), MO(_ONESHOT)
                                      //`--------------------------'        `--------------------------'
  ),
#endif

  [_NO_HOMEROW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
       TAB_CLOSE,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_A, KC_S, KC_D, KC_F,    KC_G,                                         KC_H, KC_J, KC_K, KC_L, RS_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, ENTER_CLOSE_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, ALT_TAB, LOWSPC_MO,        RAISPC_MO,   MO(_NAVI), ONESHOT_RALT
                                      //`--------------------------'        `--------------------------'
  ),

  [_NAVI] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
     TAB_CLOSE, KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,   KC_NO  ,                      KC_NO  , KC_PGUP, UP, KC_NO  , KC_HOME, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|'
      KC_ESC , KC_LEFT_GUI, KC_LEFT_ALT, KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_APP ,         KC_HOME, LEFT, DOWN, RIGHT, KC_END, KC_PSCR  ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
     KC_MUTE, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                             KC_NO  , KC_PGDN, KC_NO  , KC_NO  , KC_END,  ENTER_CLOSE_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, KC_BSPC, TURBO_MODIFIER,         KC_NO  , KC_NO  , KC_NO
                                      //`--------------------------'        `--------------------------'
  ), 

  [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                            KC_6,  KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CALC, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                      KC_PAST,  KC_P4,  KC_P5,    KC_P6,    KC_PPLS, KC_PEQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NUM  , KC_NO  , KC_NO  , KC_NO  , KC_NO, KC_NO,                      KC_PSLS, KC_P1,  KC_P2, KC_P3, KC_PMNS, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , KC_NO  , KC_NO  ,    KC_ENT, KC_P0, KC_PDOT 
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR,   KC_ASTR,  KC_LPRN,  KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD  , KC_NO, KC_NO  , KC_SLSH, KC_LCBR, KC_LBRC,                      KC_RBRC, KC_RCBR, KC_BSLS, KC_MINS, KC_PPLS, KC_NO  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO  , KC_LEFT_ANGLE_BRACKET , KC_RIGHT_ANGLE_BRACKET , KC_COPY, KC_PSTE, KC_NO  ,                     KC_NO  , KC_NO  , KC_PIPE, KC_UNDS, KC_EQL, KC_NO  ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , KC_NO  , KC_ENT  ,    KC_ENT, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

#ifdef BIG_MEMORY
[_ONESHOT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        TAP_UP  ,   SEQ_UP  ,   FOLLOW_UP  ,   RELEASE_UP  ,  TURBO_UP  ,  DF(_DEFAULT)  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F7,  KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12,                      TAP_DOWN, SEQ_DOWN, FOLLOW_DOWN, RELEASE_DOWN  , TURBO_DOWN  , DF(_GAMER)  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                      QK_BOOT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , DF(_NO_HOMEROW)  ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , ALT_F4  , KC_NO  ,    KC_NO  , KC_NO  , KC_NO
                                      //`--------------------------'  `--------------------------'
  )
#else
[_ONESHOT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        TAP_UP  ,   SEQ_UP  ,   FOLLOW_UP  ,   RELEASE_UP  ,  TURBO_UP  ,  DF(_DEFAULT)  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F7,  KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12,                      TAP_DOWN, SEQ_DOWN, FOLLOW_DOWN, RELEASE_DOWN  , TURBO_DOWN  , KC_NO  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                      QK_BOOT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , DF(_NO_HOMEROW)  ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , ALT_F4  , KC_NO  ,    KC_NO  , KC_NO  , KC_NO
                                      //`--------------------------'  `--------------------------'
  )
#endif
};

void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(CKC_D, KC_D, KC_LEFT_CTRL)
        SMTD_MT(CKC_F, KC_F, KC_LSFT)
        SMTD_MT(CKC_SCLN, KC_SCLN, KC_LEFT_GUI)
        SMTD_MT(CKC_L, KC_L, KC_LEFT_ALT)
        SMTD_MT(CKC_K, KC_K, KC_LEFT_CTRL)
        SMTD_MT(CKC_J, KC_J, KC_LSFT)
        SMTD_LT(CKC_NUMS, KC_SPACE, _NUMS)
        SMTD_LT(CKC_SYMS, KC_SPACE, _SYMS)
    }
}

uint32_t timeout_tap = 200;
uint32_t timeout_seq = 100;
uint32_t timeout_following = 200;
uint32_t timeout_release_key = 50;

uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case CKC_A:
            if (timeout == SMTD_TIMEOUT_RELEASE)
            {
                return 1;
            }
        case CKC_SCLN:
            if (timeout == SMTD_TIMEOUT_RELEASE)
            {
                return 1;
            }
    }

    if (timeout == SMTD_TIMEOUT_TAP)
    {
        return timeout_tap;
    }
    else if (timeout == SMTD_TIMEOUT_SEQUENCE)
    {
        return timeout_seq;
    }
    else if (timeout == SMTD_TIMEOUT_FOLLOWING_TAP)
    {
        return timeout_following;
    }
    else if (timeout == SMTD_TIMEOUT_RELEASE)
    {
        return timeout_release_key;
    }

    return get_smtd_timeout_default(timeout);
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable(); // enables RGB, without saving settings
  rgblight_sethsv(195, 66, 58); // sets the color to red without saving
  rgblight_mode(1);
#elif RGB_MATRIX_ENABLE
  rgb_matrix_enable();
  rgb_matrix_sethsv(195, 180, 90);
  rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
#endif

  set_single_persistent_default_layer(_DEFAULT);
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    led_t led_usb_state = host_keyboard_led_state();
    switch (get_highest_layer(layer_state)) 
    {
        case _NUMS:
            rgb_matrix_sethsv(118, 180, 90);
            break;
        case _SYMS:
            rgb_matrix_sethsv(50, 180, 90);
            break;
        case _DEFAULT:
            if (led_usb_state.caps_lock)
            {
                rgb_matrix_sethsv(255, 255, 90);
            }
            else
            {
                rgb_matrix_sethsv(195, 180, 90);
            }
            break;
        case _NAVI:
            rgb_matrix_sethsv(255, 180, 90);
            break;    
        default:
            break;
    }

    return true;
}
#endif /* RGB_MATRIX */


#ifdef OLED_ENABLE
static void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

#ifdef BIG_MEMORY
static void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

static void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}
#endif /* BIG_MEMORY */

static void render_kb_LED_state(void) {
    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    uint8_t led_count = 0;
    if (led_usb_state.num_lock)
    {
        oled_write_P(PSTR("N"), false);
        led_count++;
    }
    if (led_usb_state.caps_lock)
    {
        if (led_count != 0)
        {
            oled_write_P(PSTR(" "), false);
            led_count++;
        }
        oled_write_P(PSTR("C"), false);
        led_count++;
    }
    if (led_usb_state.scroll_lock)
    {
        if (led_count != 0)
        {
            oled_write_P(PSTR(" "), false);
            led_count++;
        }
        oled_write_P(PSTR("S"), false);
        led_count++;
    }
    while (led_count < 5)
    {
        oled_write_P(PSTR(" "), false);
        led_count++;
    }
}

static void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM syms_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM nums_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM navi_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _NUMS:
            oled_write_P(PSTR("NUMS "), false);
            oled_write_P(nums_layer, false);
            break;
        case _SYMS:
            oled_write_P(PSTR("SYMS "), false);
            oled_write_P(syms_layer, false);
            break;
        case _NAVI:
            oled_write_P(PSTR("NAVI "), false);
            oled_write_P(navi_layer, false);
            break;
        case _ONESHOT:
            oled_write_P(PSTR("ONES "), false);
            oled_write_P(default_layer, false);
            break;
#ifdef BIG_MEMORY
        case _GAMER:
            oled_write_P(PSTR("GAME "), false);
            oled_write_P(default_layer, false);
            break;
#endif
        case _NO_HOMEROW:
            oled_write_P(PSTR("NOROW"), false);
            oled_write_P(default_layer, false);
            break;
        default:
            oled_write_P(PSTR("HOME "), false);
            oled_write_P(default_layer, false);
            break;
    }
}

#ifdef WPM_ENABLE
static void render_wpm(void)
{
    oled_write_P(PSTR("APM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
}
#endif /* WPM_ENABLE */

static void render_tap(void)
{
    oled_write(get_u16_str(timeout_tap, ' '), false);
}

static void render_seq(void)
{
    oled_write(get_u16_str(timeout_seq, ' '), false);
}

static void render_following(void)
{
    oled_write(get_u16_str(timeout_following, ' '), false);
}

static void render_release(void)
{
    oled_write(get_u16_str(timeout_release_key, ' '), false);
}

static void render_turbo_threshold(void)
{
    oled_write_P(PSTR("TURB:"), false);
    oled_write(get_u16_str(turbo_threshold, ' '), false);
}



bool oled_task_user(void)
{
    if (is_keyboard_master())
    {
        render_layer_state();
        render_space();
        render_tap();
        render_seq();
        render_following();
        render_release();
        render_space();
        render_turbo_threshold();
    }
    else
    {
#ifdef BIG_MEMORY
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
#endif
        render_kb_LED_state();
        render_space();
#ifdef WPM_ENABLE
        render_wpm();
#endif /* WPM_ENABLE */
    }
    return false;
}
#endif

bool turbo_up = false;
bool turbo_down = false;
bool turbo_left = false;
bool turbo_right = false;

#ifdef SNAP_TAP
typedef enum
{
    NONE,
    A,
    D,
} snap_tap_state;

snap_tap_state most_recent;

bool a_pressed = false;
bool d_pressed = false;
bool snap_tap_updated = false;

void snap_tap_handler(snap_tap_state current)
{

    if (current == A)
    {
        unregister_code(KC_D);
        register_code(KC_A);
    }
    else if (current == D)
    {
        unregister_code(KC_A);
        register_code(KC_D);
    }
    else
    {
        unregister_code(KC_A);
        unregister_code(KC_D);
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_smtd(keycode, record))
    {
        return false;
    }
    switch (keycode) 
    {
        case TURBO_MODIFIER:
            if (record->event.pressed)
            {
                supascroll_active = true;
            }
            else
            {
                supascroll_active = false;
            }
            break;
        case UP:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_UP);
                }
                else if (supascroll_active)
                {
                    turbo_up = true;
                }
                else
                {
                    register_code(KC_UP);
                }
            }
            else
            {
                unregister_code(KC_UP);
                turbo_up = false;
            }
            break;
        case DOWN:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_DOWN);
                }
                else if (supascroll_active)
                {
                    turbo_down = true;
                }
                else
                {
                    register_code(KC_DOWN);
                }
            }
            else
            {
                unregister_code(KC_DOWN);
                turbo_down = false;
            }
            break;
        case LEFT:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_LEFT);
                }
                else if (supascroll_active)
                {
                    turbo_left = true;
                }
                else
                {
                    register_code(KC_LEFT);
                }
            }
            else
            {
                unregister_code(KC_LEFT);
                turbo_left = false;
            }
            break;
        case RIGHT:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_RIGHT);
                }
                else if (supascroll_active)
                {
                    turbo_right = true;
                }
                else
                {
                    register_code(KC_RIGHT);
                }
            }
            else
            {
                unregister_code(KC_RIGHT);
                turbo_right = false;
            }
            break;
        case ENTER_CLOSE_TAB:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    register_code(KC_ENTER);
                    unregister_code(KC_LALT);
                    is_alt_tab_active = false;
                }
                else
                {
                    register_code(KC_ENTER);
                }
            }
            else
            {
                unregister_code(KC_ENTER);
            }
            break;
        case TAB_CLOSE:
            if (record->event.pressed) 
            {
                if (is_alt_tab_active)
                {
                    alt_tab_timer = timer_read();
                    register_code(KC_LEFT_CTRL);
                    tap_code(KC_W);
                    unregister_code(KC_LEFT_CTRL);
                }
                else
                {
                    register_code(KC_TAB);
                }
            }
            else
            {
                unregister_code(KC_TAB);
            }
            break;
        case TURBO_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((uint16_t)(turbo_threshold + 3) > turbo_threshold)
                {
                    turbo_threshold += 3;
                }
            }
            break;
        case TURBO_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((uint16_t)(turbo_threshold - 3) < turbo_threshold)
                {
                    turbo_threshold -= 3;
                }
                else
                {
                    turbo_threshold = 0;
                }
            }
            break;
        case ALT_TAB:
            if (record->event.pressed)
            {
                if (!is_alt_tab_active) 
                {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } 
            else 
            {
                unregister_code(KC_TAB);
            }
            break;
        case ALT_F4:
            if (record->event.pressed) 
            {
                register_code(KC_LALT);
                register_code(KC_F4);
                unregister_code(KC_F4);
                unregister_code(KC_LALT);
            }
            break;
        case TAP_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_tap + 3) > timeout_tap)
                {
                    timeout_tap += 3;
                }
            }
            break;
        case TAP_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_tap - 3) < timeout_tap)
                {
                    timeout_tap -= 3;
                }
                else
                {
                    timeout_tap = 0;
                }
            }
            break;
            case SEQ_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_seq + 3) > timeout_seq)
                {
                    timeout_seq += 3;
                }
            }
            break;
        case SEQ_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_seq - 3) < timeout_seq)
                {
                    timeout_seq -= 3;
                }
                else
                {
                    timeout_seq = 0;
                }
            }
            break;
        case FOLLOW_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_following + 3) > timeout_following)
                {
                    timeout_following += 3;
                }
            }
            break;
        case FOLLOW_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_following - 3) < timeout_following)
                {
                    timeout_following -= 3;
                }
                else
                {
                    timeout_following = 0;
                }
            }
            break;
        case RELEASE_UP:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_release_key + 3) > timeout_release_key)
                {
                    timeout_release_key += 3;
                }
            }
            break;
        case RELEASE_DOWN:
            if (record->event.pressed) 
            {
                /* Check for wrap! */
                if ((timeout_release_key - 3) < timeout_release_key)
                {
                    timeout_release_key -= 3;
                }
                else
                {
                    timeout_release_key = 0;
                }
            }
            break;
#ifdef SNAP_TAP
        case SNAP_TAP_A:
            if (record->event.pressed)
            {
                most_recent = A;
                a_pressed = true;
                snap_tap_updated = false;
            }
            else
            {
                a_pressed = false;
                if (d_pressed)
                {
                    most_recent = D;
                    snap_tap_updated = false;
                }

                unregister_code(KC_A);
            }
            break;
        case SNAP_TAP_D:
            if (record->event.pressed)
            {
                most_recent = D;
                d_pressed = true;
                snap_tap_updated = false;
            }
            else
            {
                d_pressed = false;

                if (a_pressed)
                {
                    most_recent = A;
                    snap_tap_updated = false;
                }

                unregister_code(KC_D);
            }
            break;
#endif
    }

    if (record->event.pressed)
    {
        caps_timer = timer_read();
    }

    return true;
}

uint16_t turbo_timer = 0;

void leader_start_user(void)
{
    rgb_matrix_sethsv(62, 180, 90);
    layer_on(_NO_HOMEROW);
}

void leader_end_user(void)
{
    if (leader_sequence_two_keys(KC_A, KC_E))
    {
        register_code(KC_RALT);
        tap_code(KC_Z); /* æÆ */
        unregister_code(KC_RALT);
    }
    else if (leader_sequence_two_keys(KC_O, KC_E))
    {
        register_code(KC_RALT);
        tap_code(KC_L); /* øØ */
        unregister_code(KC_RALT);
    }
    else if (leader_sequence_two_keys(KC_A, KC_A))
    {
        register_code(KC_RALT);
        tap_code(KC_W); /* åÅ */
        unregister_code(KC_RALT);
    }
    else if (leader_sequence_two_keys(KC_M, KC_U))
    {
        register_code(KC_RALT);
        tap_code(KC_M); /* µ */
        unregister_code(KC_RALT);
    }
    layer_off(_NO_HOMEROW);
}

void matrix_scan_user(void) // The very important timer.
{
    if (is_alt_tab_active)
    {
        if (timer_elapsed(alt_tab_timer) > 1000)
        {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    if (turbo_up && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_UP);
        turbo_timer = timer_read();
    }

    if (turbo_down && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_DOWN);
        turbo_timer = timer_read();
    }

    if (turbo_right && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_RIGHT);
        turbo_timer = timer_read();
    }

    if (turbo_left && timer_elapsed(turbo_timer) > turbo_threshold)
    {
        /* Get variable that can be altered by keypresses, and use that for delay, so that we can set it ourselves. */
        tap_code(KC_LEFT);
        turbo_timer = timer_read();
    }

    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.caps_lock && timer_elapsed(caps_timer) > 3000 )
    {
        tap_code(KC_CAPS);
    }

#ifdef SNAP_TAP   
    if (a_pressed && most_recent == A && !snap_tap_updated)
    {
        unregister_code(KC_D);
        register_code(KC_A);
        snap_tap_updated = true;
    }
    else if (d_pressed && most_recent == D && !snap_tap_updated)
    {
        unregister_code(KC_A);
        register_code(KC_D);
        snap_tap_updated = true;
    }
#endif
}
