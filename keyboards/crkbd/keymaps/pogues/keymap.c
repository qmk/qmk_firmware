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

/*******************************************************************************
 * TODO.
 * sort out oled display
 * fix the colours for the motion, function, symbol and mouse + leader
 *******************************************************************************/

enum userspace_layers {
    LCMK = 0,
    LNUM = 1,
    LMOV = 2,
    LSYM = 3,
    LFUN = 4,
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // colemak-dh
    [LCMK] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            MY_CESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, MY_CENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LEAD,  MY_S_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, MY_S_SL, KC_LEAD,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            //KC_LGUI, LT(LMOV, KC_TAB), LT(LNUM, KC_SPC),    LT(LSYM, KC_BSPC), LT(LFUN, KC_ENT), KC_LALT
            MT(MOD_LGUI, KC_ESC), LT(LMOV, KC_TAB), LT(LNUM, KC_SPC),            LT(LSYM, KC_BSPC), LT(LFUN, KC_ENT), MT(MOD_LALT, KC_DEL)
                                            //`--------------------------'  `--------------------------'
    ),
    [LNUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PLUS,    KC_7,    KC_8,    KC_9, KC_PERC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_COMM,                      KC_MINS,    KC_4,    KC_5,    KC_6, KC_ASTR, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_DOT, XXXXXXX,                       KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              XXXXXXX, XXXXXXX,  _______,     KC_BSPC,  KC_0, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOV] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       MY_CUT, MY_COPY, MY_PSTE, MY_REDO, MY_UNDO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              XXXXXXX, _______,  XXXXXXX,     KC_BSPC,  KC_ENT, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LSYM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, KC_SCLN, KC_COLN, KC_LPRN, KC_RPRN, MY_PIPE,                      KC_PLUS, KC_COLN, KC_SCLN, KC_QUES,  MY_GBP, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, MY_DQUO, KC_QUOT, KC_LBRC, KC_RBRC, KC_UNDS,                      KC_MINS, KC_NUHS,   MY_AT, KC_EXLM, KC_AMPR, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR,  KC_DLR,                       KC_EQL, MY_TILD, KC_CIRC,  KC_GRV, KC_NUBS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, KC_TAB,  KC_SPC,     _______,  XXXXXXX, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LFUN] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,TO(LMSE),   KC_F4,   KC_F5,   KC_F6,  KC_F11,                      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F12,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  _______, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LMSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, RESET,   XXXXXXX,  KC_MS_UP,    XXXXXXX, XXXXXXX,             KC_MS_BTN3,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT, KC_WH_U,            KC_MS_BTN1, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX,KC_MS_BTN3,KC_MS_BTN2, KC_MS_BTN1, KC_WH_D,            KC_MS_BTN2,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______, TO(LCMK),_______,    _______,  TO(LCMK), XXXXXXX
                                            //`--------------------------'  `--------------------------'
    )
};


/*******************************************************************************
 * caps word
 *******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_caps_word(keycode, record)) {
        return false;
    }

    return true;
}

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
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


void caps_word_set_user(bool active) {
    if (active) {
        // TODO set LED
        // Do something when Caps Word activates.
    } else {
        // Do something when Caps Word deactivates.
    }
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
        SEQ_ONE_KEY(KC_R) {
            tap_code(KC_F9);
        }
        SEQ_TWO_KEYS(KC_R, KC_R) {
            register_code(KC_LCTL);
            tap_code(KC_F10);
            unregister_code(KC_LCTL);
        }
        SEQ_ONE_KEY(KC_T) {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_F10);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
    }
}

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
 ******************************************************************************/

const rgblight_segment_t PROGMEM layer_default_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_OFF},
    {8, 1, HSV_YELLOW},   // comma
    {9, 2, HSV_OFF},
    {11, 1, HSV_BLUE},    // gui
    {12, 1, HSV_YELLOW},  // dot
    {13, 3, HSV_OFF},
    {16, 1, HSV_GREEN},   // alt
    {17, 2, HSV_OFF},
    {19, 1, HSV_ORANGE},  // ctrl
    {20, 2, HSV_OFF},
    {22, 1, HSV_RED},     // shift
    {23, 4, HSV_OFF},
    // right hand side
    {27, 7, HSV_OFF},
    {34, 7, HSV_ORANGE},
    {41, 1, HSV_OFF},
    {42, 12, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM layer_symbols_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_OFF},
    {6, 19, HSV_GREEN},
    {25, 1, HSV_OFF},
    {26, 1, HSV_GREEN},
    {27, 7, HSV_OFF},
    {34, 7, HSV_GREEN},
    {41, 2, HSV_OFF},
    {43, 9, HSV_GREEN},
    {52, 1, HSV_OFF},
    {53, 1, HSV_GREEN},
    {54, 1, HSV_OFF}
);

const rgblight_segment_t PROGMEM layer_motion_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 11, HSV_OFF},
    {11, 1, HSV_BLUE},    // gui
    {12, 4, HSV_OFF},
    {16, 1, HSV_GREEN},   // alt
    {17, 2, HSV_OFF},
    {19, 1, HSV_ORANGE},  // ctrl
    {20, 2, HSV_OFF},
    {22, 1, HSV_RED},     // shift
    {23, 4, HSV_OFF},
    // right hand side
    {27, 7, HSV_OFF},
    {34, 7, HSV_BLUE},
    {41, 1, HSV_OFF},
    {42, 12, HSV_BLUE}
);

const rgblight_segment_t PROGMEM layer_functions_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM layer_mouse_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_CYAN},
    {27, 10, HSV_CYAN}
);

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_default_lights,
    layer_numpad_lights,
    layer_motion_lights,
    layer_symbols_lights,
    layer_functions_lights,
    layer_mouse_lights
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_mode(10);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(1, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(2, layer_state_cmp(state, LMOV));
    rgblight_set_layer_state(3, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(4, layer_state_cmp(state, LFUN));
    rgblight_set_layer_state(5, layer_state_cmp(state, LMSE));
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
