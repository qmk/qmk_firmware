/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include <stdio.h>
#include "tap_dance_macro.h"

/*******************************************************************************
 * TODO.
 * add additional symbols to left hand of the symbol layer
 * : on double click (maybe not after symbol layer)
 * ? on double press or hold?
 * sort out oled display
 * mouse keys
 *
 *******************************************************************************/
enum userspace_layers {
    LCMK = 0,
    LNUM = 1,
    LSYM = 2,
    LMOV = 3,
};

// the layer mask
#define L_COLEMAK LCMK
#define L_NUMPAD (1 << LNUM)
#define L_SYMBOL (1 << LSYM)
#define L_MOTION (1 << LMOV)

#define MY_CESC MT(MOD_LCTL, KC_ESC)
#define MY_CQOT MT(MOD_LCTL, KC_QUOT)
#define MY_S_SL MT(MOD_LSFT, KC_SLSH)
#define MY_S_Z  MT(MOD_LSFT, KC_Z)CTRL
#define MY_TBUI MT(MOD_LGUI, KC_TAB)
#define MY_CLFT C(KC_LEFT)
#define MY_CRGT C(KC_RGHT)

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)

enum tap_dance_codes {
    // 0-9 are number on tap and function key on hold
    DC0,
    DC1,
    DC2,
    DC3,
    DC4,
    DC5,
    DC6,
    DC7,
    DC8,
    DC9,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LCMK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      MY_TBUI,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MY_CESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, MY_CQOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
OSM(MOD_LSFT),  MY_S_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, MY_S_SL, KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                           OSL(LSYM), OSL(LNUM), LT(LMOV, KC_SPC),       LT(LMOV, KC_ENT), KC_BSPC,  KC_LGUI
                                      //`--------------------------'  `--------------------------'

  ),

  [LNUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PLUS, TD(DC7), TD(DC8), TD(DC9), KC_PERC,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TO(LCMK), KC_LALT, KC_LCTL,   KC_LT,   KC_GT, KC_UNDS,                      KC_MINS, TD(DC4), TD(DC5), TD(DC6), KC_ASTR,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_EQL, TD(DC1), TD(DC2), TD(DC3), KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_SPC,     KC_ENT, _______, TD(DC0)
                                      //`--------------------------'  `--------------------------'
  ),

  [LSYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, KC_QUES, KC_COLN, KC_SCLN, XXXXXXX,                      KC_EXLM, KC_LPRN, KC_RPRN,   MY_AT, KC_NUBS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TO(LCMK), XXXXXXX, XXXXXXX,   KC_LT,   KC_GT,  KC_EQL,                      KC_NUHS, KC_LBRC, KC_RBRC, MY_PIPE, MY_TILD,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, KC_QUOT, MY_DQUO, XXXXXXX,                      KC_AMPR, KC_LCBR, KC_RCBR,  KC_DLR, KC_CIRC, KC_RSFT,

  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_SPC,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [LMOV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  RESET, MY_CRGT, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_UNDS, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, MY_CLFT,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,_______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};


/*******************************************************************************
 * Tap dance functions
 ******************************************************************************/
TD_TAP_HOLD_FUNCTIONS(0, KC_0, KC_F10)
TD_TAP_HOLD_FUNCTIONS(1, KC_1, KC_F1)
TD_TAP_HOLD_FUNCTIONS(2, KC_2, KC_F2)
TD_TAP_HOLD_FUNCTIONS(3, KC_3, KC_F3)
TD_TAP_HOLD_FUNCTIONS(4, KC_4, KC_F4)
TD_TAP_HOLD_FUNCTIONS(5, KC_5, KC_F5)
TD_TAP_HOLD_FUNCTIONS(6, KC_6, KC_F6)
TD_TAP_HOLD_FUNCTIONS(7, KC_7, KC_F7)
TD_TAP_HOLD_FUNCTIONS(8, KC_8, KC_F8)
TD_TAP_HOLD_FUNCTIONS(9, KC_9, KC_F9)
TD_TAP_HOLD_FUNCTIONS(semicolon, KC_SCLN, KC_COLN)  // TODO do we want this? perhaps double tap?

// single and double quotes '/" - a bit different here as double quote is on double tap
// as we want control on hold.
static td_tap_t dance_state_quote = {
    .is_press_action = true,
    .step = 0
};

void on_dance_quote(qk_tap_dance_state_t *state, void *user_data) {
    on_tap_hold_dance(state, user_data, KC_QUOT);
}

void dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state_quote.step = current_dance_step(state);
    switch (dance_state_quote.step) {
        case SINGLE_TAP: 
            tap_code16(KC_QUOT);
            break;
        case SINGLE_HOLD: 
            register_code16(KC_RCTL);
            break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            tap_code16(MY_DQUO);
            break;
    }
}

void dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state_quote.step) {
        case SINGLE_HOLD:
            unregister_code16(KC_RCTL);
            break;
    }
    dance_state_quote.step = 0;
}

////////////////////////////////////////////////////////////////////////////////
// end of simple tap/hold
////////////////////////////////////////////////////////////////////////////////

// list the actions and map to handlers
qk_tap_dance_action_t tap_dance_actions[] = {
    [DC0] = TD_TAP_HOLD_ACTION(0),
    [DC1] = TD_TAP_HOLD_ACTION(1),
    [DC2] = TD_TAP_HOLD_ACTION(2),
    [DC3] = TD_TAP_HOLD_ACTION(3),
    [DC4] = TD_TAP_HOLD_ACTION(4),
    [DC5] = TD_TAP_HOLD_ACTION(5),
    [DC6] = TD_TAP_HOLD_ACTION(6),
    [DC7] = TD_TAP_HOLD_ACTION(7),
    [DC8] = TD_TAP_HOLD_ACTION(8),
    [DC9] = TD_TAP_HOLD_ACTION(9),
};
/*******************************************************************************
 * End Tap dance functions
 ******************************************************************************/

/*******************************************************************************
 * user specific functions
 * here we map the numpad and symbol layer functions to be either one shot or hold.
 ******************************************************************************/


/*******************************************************************************
 * RGB lighting on layer change
 ******************************************************************************/
const rgblight_segment_t PROGMEM layer_default_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 27, HSV_OFF},
    {27, 54, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_YELLOW},
    {10, 5, HSV_BLUE},
    {15, 3, HSV_GREEN},
    {18, 3, HSV_ORANGE},
    {21, 3, HSV_RED},
    {27, 10, HSV_YELLOW},
    {37, 5, HSV_BLUE},
    {42, 3, HSV_GREEN},
    {45, 3, HSV_ORANGE},
    {48, 3, HSV_RED}
);

const rgblight_segment_t PROGMEM layer_symbols_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM layer_motion_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_RED}
);

const rgblight_segment_t PROGMEM oneshot_shift_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_BLUE},
    {27, 10, HSV_BLUE}
);

const rgblight_segment_t PROGMEM oneshot_locked_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_RED},
    {27, 10, HSV_RED}
);

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_default_lights,
    layer_numpad_lights,
    layer_symbols_lights,
    layer_motion_lights,
    oneshot_shift_lights,
    oneshot_locked_lights
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_mode(10);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(1, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(2, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(3, layer_state_cmp(state, LMOV));
    return state;
}
/*******************************************************************************
 * END RGB lighting on layer change
 ******************************************************************************/

/*******************************************************************************
 * RGB lighting on one shot mod change
 ******************************************************************************/
void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        rgblight_set_layer_state(4, true);
    }
    // other mods are MOD_MASK_CTRL  MOD_MASK_ALT MOD_MASK_GUI
    else {  // (!mods)
        rgblight_set_layer_state(4, false);
    }
}


void oneshot_locked_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        rgblight_set_layer_state(5, true);
    }
    else { // !mods
        rgblight_set_layer_state(5, false);
    }
}

/*******************************************************************************
 * END RGB lighting on one shot mod change
 ******************************************************************************/

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}


void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_COLEMAK:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_NUMPAD:
            oled_write_ln_P(PSTR("NUM PAD"), false);
            break;
        case L_SYMBOL:
            oled_write_ln_P(PSTR("SYMBOLS"), false);
            break;
        case L_MOTION:
        case L_MOTION|L_NUMPAD:
        case L_MOTION|L_SYMBOL:
        case L_MOTION|L_NUMPAD|L_SYMBOL:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

/*
void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}
void oled_render_layer_numpad(void) {
    static const char PROGMEM numpad_layer_logo[] = {
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0x01, 0x01,
0x01, 0x01, 0x01,
0x01, 0x01, 0x01,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0};
    oled_write_P(numpad_layer_logo, false);
}
*/
static void oled_render_layer_numpad(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


bool oled_task_user(void) {
    oled_render_layer_numpad();
    return false;
}

#endif // OLED_ENABLE
