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

/*******************************************************************************
 * TODO.
 * look at the mods on the lower row - are any used?
 * sort out oled display
 * look at lag on keyboard..
 * consider a function key layer... ?
 *
 *******************************************************************************/
enum userspace_layers {
    LCMK = 0,
    LRAISE = 1,
    LLOWER = 2,
    LMOUSE = 3,
};

// the layer mask
#define L_COLEMAK LCMK
#define LMASK_RAISE (1 << LRAISE)
#define LMASK_LOWER (1 << LLOWER)
#define LMASK_MOUSE (1 << LMOUSE)

#define MY_CESC MT(MOD_LCTL, KC_ESC)
#define MY_CENT MT(MOD_LCTL, KC_ENT)
#define MY_S_SL MT(MOD_LSFT, KC_SLSH)
#define MY_S_Z  MT(MOD_LSFT, KC_Z)
#define MY_C_X  MT(MOD_LCTL, KC_X)
#define MY_TBUI MT(MOD_LGUI, KC_TAB)
#define MY_CLFT C(KC_LEFT)
#define MY_CRGT C(KC_RGHT)
#define MY_UNDO C(KC_U)
#define MY_REDO C(KC_Y)
#define MY_COPY C(KC_C)
#define MY_PSTE C(KC_V)

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
            MY_TBUI,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            MY_CESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, MY_CENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OSM(MOD_LSFT),  MY_S_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, MY_S_SL, KC_LALT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             KC_LGUI, TO(LRAISE), KC_SPC,     KC_BSPC, TO(LLOWER), KC_ENT
                                            //`--------------------------'  `--------------------------'
    ),
    [LRAISE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            _______,   MY_AT, KC_COLN, KC_LPRN, KC_RPRN, MY_PIPE,                      KC_PLUS, KC_7, KC_8, KC_9, KC_PERC, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, MY_DQUO, KC_QUOT, KC_LBRC, KC_RBRC, KC_UNDS,                      KC_MINS, KC_4, KC_5, KC_6, KC_ASTR, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR,  KC_DLR,                      KC_EQL, KC_1, KC_2, KC_3, KC_SLSH, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, TO(LCMK), _______,     _______,  TO(LLOWER), KC_0
                                            //`--------------------------'  `--------------------------'
    ),
    [LLOWER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           _______,   MY_GBP, MY_CRGT, KC_COLN, KC_SCLN, MY_CLFT,                      MY_COPY, MY_PSTE, MY_UNDO, MY_REDO, XXXXXXX, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,   MY_AT, KC_EXLM, KC_NUHS, MY_TILD, KC_CIRC,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,TO(LMOUSE),KC_GRV, KC_NUBS, KC_AMPR, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               _______, TO(LCMK), _______,     _______,  TO(LMOUSE), _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOUSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            _______, RESET,   XXXXXXX,  KC_MS_UP,    XXXXXXX, XXXXXXX,            KC_MS_BTN3,   KC_F7,   KC_F8,   KC_F9, XXXXXXX, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT, KC_WH_U,            KC_MS_BTN1,   KC_F4,   KC_F5,   KC_F6, XXXXXXX, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, XXXXXXX,KC_MS_BTN3,KC_MS_BTN2, KC_MS_BTN1, KC_WH_D,            KC_MS_BTN2,   KC_F1,   KC_F2,   KC_F3, XXXXXXX, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______, TO(LCMK),_______,    _______,  TO(LRAISE), KC_F10
                                            //`--------------------------'  `--------------------------'
    )
};


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
    {0, 54, HSV_BLUE}
);

const rgblight_segment_t PROGMEM layer_motion_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_RED}
);

const rgblight_segment_t PROGMEM oneshot_shift_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_GREEN},
    {27, 10, HSV_GREEN}
);

const rgblight_segment_t PROGMEM oneshot_shift_locked_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_RED},
    {27, 10, HSV_RED}
);

const rgblight_segment_t PROGMEM oneshot_ctrl_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_ORANGE},
    {27, 10, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM oneshot_ctrl_locked_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_GREEN},
    {27, 10, HSV_GREEN}
);

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_default_lights,
    layer_numpad_lights,
    layer_symbols_lights,
    layer_motion_lights,
    oneshot_shift_lights,
    oneshot_shift_locked_lights,
    oneshot_ctrl_lights,
    oneshot_ctrl_locked_lights
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_mode(10);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(1, layer_state_cmp(state, LRAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, LLOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, LMOUSE));
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
    else if (mods & MOD_MASK_CTRL) {
        rgblight_set_layer_state(6, true);
    }

    // other mods are MOD_MASK_ALT MOD_MASK_GUI
    else {  // (!mods)
        rgblight_set_layer_state(4, false);
        rgblight_set_layer_state(6, false);
    }
}


void oneshot_locked_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        rgblight_set_layer_state(5, true);
    }
    else if (mods & MOD_MASK_CTRL) {
        rgblight_set_layer_state(7, true);
    }
    else { // !mods
        rgblight_set_layer_state(5, false);
        rgblight_set_layer_state(7, false);
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
