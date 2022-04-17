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
#include "features/caps_word.h"
#include "features/custom_shift_keys.h"
#include "features/layer_lock.h"

/*******************************************************************************
 * TODO.
 * add tristate layer to the motion layer... 
 *      should alt be added on the outer right thumb key?
 * add tab, esc, ctl, del, enter, leader to the keymap to simulate a 36 key 
 * sort out oled display
 *******************************************************************************/

enum userspace_layers {
    LCMK = 0,
    LNUM = 1,
    LFUN = 2,
    LMOV = 3,
    LSYM = 4,
    LMSE = 5,
};

// the layer mask
#define L_COLEMAK LCMK
#define LMASK_NUM (1 << LNUM)
#define LMASK_MOV (1 << LMOV)
#define LMASK_SYM (1 << LSYM)
#define LMASK_FUN (1 << LFUN)
#define LMASK_MSE (1 << LMSE)

#define MY_CESC MT(MOD_LCTL, KC_ESC)
#define MY_CENT MT(MOD_LCTL, KC_ENT)
#define MY_S_SL MT(MOD_LSFT, KC_SLSH)
#define MY_S_Z  MT(MOD_LSFT, KC_Z)
#define MY_UNDO C(KC_Z)
#define MY_REDO C(KC_Y)
#define MY_COPY C(KC_C)
#define MY_PSTE C(KC_V)
#define MY_CUT  C(KC_X)

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)
#define MY_GBP KC_HASH      // just shift-3
#define ALT_TAB ALT_T(KC_TAB)

#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)

enum custom_keycodes {
    LLOCK = SAFE_RANGE,
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT , KC_COLN}, // Shift . is :
    {KC_COMM, KC_SCLN}, // Shift , is ;
    {KC_2, KC_DQUO}     // need shift 2 to be " for win+shift+2 to work in dwm
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // colemak-dh
    [LCMK] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            MY_CESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, MY_CENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LEAD,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_LEAD,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       OSM_GUI, OSL(LNUM), SFT_T(KC_SPC),    SFT_T(KC_BSPC), OSL(LSYM), OSL(LMOV)
                                            //`--------------------------'  `--------------------------'
    ),
    [LNUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX,TO(LFUN), XXXXXXX, XXXXXXX,                      KC_PLUS,    KC_7,    KC_8,    KC_9, KC_PERC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_COMM,                      KC_MINS,    KC_4,    KC_5,    KC_6, KC_ASTR,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,TO(LFUN), XXXXXXX, XXXXXXX,  KC_DOT, XXXXXXX,                       KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TO(LFUN), TO(LCMK),  _______,    KC_BSPC,  KC_0, LLOCK
                                            //`--------------------------'  `--------------------------'
    ),
    [LFUN] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F10,   KC_F7,   KC_F8,   KC_F9,  KC_DEL, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, XXXXXXX,                       KC_F11,   KC_F4,   KC_F5,   KC_F6,  KC_ENT, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F12,   KC_F1,   KC_F2,   KC_F3,  KC_TAB, XXXXXXX, 
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               XXXXXXX,TO(LCMK), XXXXXXX,    XXXXXXX,  KC_F10, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOV] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            ALT_TAB, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX,                       MY_CUT, MY_COPY, MY_PSTE, MY_REDO, MY_UNDO, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,                      XXXXXXX, OSM_SFT, OSM_CTL, OSM_GUI, OSM_ALT, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              LLOCK, TO(LCMK),  TO(LMSE),     KC_BSPC,  XXXXXXX, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LSYM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            _______, XXXXXXX, KC_QUES, KC_LPRN, KC_RPRN, MY_PIPE,                      KC_EXLM, MY_PIPE, MY_TILD,   MY_AT, KC_NUBS, _______,                       
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, KC_AMPR, KC_UNDS, KC_LBRC, KC_RBRC, KC_UNDS,                      KC_NUHS, MY_DQUO, KC_QUOT, KC_SCLN, KC_COLN,  _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX,  MY_GBP, KC_LCBR, KC_RCBR,  KC_GRV,                      KC_AMPR,   KC_LT,   KC_GT,  KC_DLR, KC_CIRC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                 LLOCK, TO(LCMK), KC_SPC,    KC_BSPC,  _______, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LMSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, RESET,   XXXXXXX,  KC_MS_UP,    XXXXXXX, XXXXXXX,             KC_MS_BTN3,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT, KC_WH_U,            KC_MS_BTN1, OSM_SFT, OSM_CTL, OSM_GUI, OSM_ALT, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX,KC_MS_BTN3,KC_MS_BTN2, KC_MS_BTN1, KC_WH_D,            KC_MS_BTN2,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______, TO(LCMK),_______,    _______,  TO(LCMK), XXXXXXX
                                            //`--------------------------'  `--------------------------'
    )
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_layer_lock(keycode, record, LLOCK)) {
        return false;
    }
    if (!process_caps_word(keycode, record)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }

    return true;
}

/*******************************************************************************
 * caps word
 *******************************************************************************/
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_DOT:
        case KC_MINS:
        case MY_PIPE:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


void caps_word_set_user(bool active) {
    rgblight_set_layer_state(7, active);
}

/*******************************************************************************
 * leader key
 *******************************************************************************/
LEADER_EXTERNS();

void matrix_scan_user(void) {
#if CAPS_WORD_IDLE_TIMEOUT > 0
     caps_word_task();
#endif

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_C) {
            // toggle capsword
            caps_word_set(!caps_word_get());
        }
        SEQ_ONE_KEY(KC_O) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_O);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }

        /**********************************************************************
        // qzdev 
        **********************************************************************/
        // diff current
        SEQ_TWO_KEYS(KC_D, KC_C) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_G);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        // diff approved
        SEQ_TWO_KEYS(KC_D, KC_A) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_V);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        // diff prod
        SEQ_TWO_KEYS(KC_D, KC_P) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_P);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        // diff head
        SEQ_TWO_KEYS(KC_D, KC_H) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_E);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        // diff against version
        SEQ_TWO_KEYS(KC_D, KC_V) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_V);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }

        // test function
        SEQ_TWO_KEYS(KC_T, KC_F) {
            register_code(KC_LCTL);
            tap_code(KC_F10);
            unregister_code(KC_LCTL);
        }
        // test class
        SEQ_TWO_KEYS(KC_T, KC_C) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_F10);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        // test script
        SEQ_TWO_KEYS(KC_T, KC_S) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            tap_code(KC_F10);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }

        // run script
        SEQ_TWO_KEYS(KC_R, KC_S) {
            tap_code(KC_F9);
        }
        // run script with restart
        SEQ_TWO_KEYS(KC_R, KC_R) {
            register_code(KC_LCTL);
            tap_code(KC_F9);
            unregister_code(KC_LCTL);
        }

        // save with black
        SEQ_TWO_KEYS(KC_S, KC_B) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_S);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        //  all copy  /  all cut ?
    }
}

// with the below you can create a global is_leader and test it in the rgb code to signal leader
// void leader_start(void) {is_leader = true;}
// void leader_end(void) {is_leader = false;}

/*******************************************************************************
 * RGB lighting on layer change
 * following are the LED numbers
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 * |  25  |  24  |  19  |  18  |  11  |  10  |            |      |      |      |      |      |
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 * |  26  |  23  |  20  |  17  |  12  |  9   |            |      |      |      |      |      |
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 * |  27  |  22  |  21  |  16  |  13  |  8   |            |      |      |      |      |      |
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 *                      |  15  |  14  |  7   |            |      |      |
 *                      |------|------|------|            |------|------|
 *
 * reverse
 *      |------|------|------|
 *      |   1  |   2  |   3  |
 *      |------|------|------|
 *      |   4  |   5  |   6  |
 *      |------|------|------|
 *
 * to set colours on the modifier keys use the below.  RHS is 38, 43, 46, 49 for the numbers
    //{11, 1, HSV_BLUE},    // gui
    //{16, 1, HSV_GREEN},   // alt
    //{19, 1, HSV_ORANGE},  // ctrl
    //{22, 1, HSV_RED},     // shift
 ******************************************************************************/

#define THUMB_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    { 6, 1, HSV_ ##colour}, \
    {13, 2, HSV_ ##colour}, \
    {33, 1, HSV_ ##colour}, \
    {40, 2, HSV_ ##colour} \
);
const rgblight_segment_t PROGMEM layer_default_lights[] = THUMB_KEYS(OFF)

const rgblight_segment_t PROGMEM layer_numpad_lights[] = THUMB_KEYS(ORANGE)

const rgblight_segment_t PROGMEM layer_symbols_lights[] = THUMB_KEYS(GREEN)

const rgblight_segment_t PROGMEM layer_motion_lights[] = THUMB_KEYS(BLUE)

const rgblight_segment_t PROGMEM layer_functions_lights[] = THUMB_KEYS(PURPLE)

const rgblight_segment_t PROGMEM layer_mouse_lights[] = THUMB_KEYS(MAGENTA)

const rgblight_segment_t PROGMEM caps_word_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 3, HSV_RED},
    {34, 3, HSV_RED}
);

const rgblight_segment_t PROGMEM layer_no_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_OFF}
);

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_no_lights,
    layer_default_lights,
    layer_numpad_lights,
    layer_motion_lights,
    layer_symbols_lights,
    layer_functions_lights,
    layer_mouse_lights,
    caps_word_lights
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    //rgblight_mode(10);
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(2, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, LMOV));
    rgblight_set_layer_state(4, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(5, layer_state_cmp(state, LFUN));
    rgblight_set_layer_state(6, layer_state_cmp(state, LMSE));
    return state;
}
/*******************************************************************************
 * END RGB lighting on layer change
 ******************************************************************************/


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

#if 0
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
#endif
/*
void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_COLEMAK:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case LMASK_RAISE:
            oled_write_ln_P(PSTR("NUM PAD"), false);
            break;
        case LMASK_LOWER:
            oled_write_ln_P(PSTR("SYMBOLS"), false);
            break;
        case LMASK_MOUSE:
        case LMASK_MOUSE|LMASK_RAISE:
        case LMASK_MOUSE|LMASK_LOWER:
        case LMASK_MOUSE|LMASK_RAISE|LMASK_LOWER:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}
*/
static void oled_render_layer_numpad(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


bool oled_task_user(void) {
    oled_render_layer_numpad();
    return false;
}

#endif // OLED_ENABLE
