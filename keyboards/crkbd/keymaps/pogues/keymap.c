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

#include "pogues.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // colemak-dh
    [LCMK] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   CTL_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,   CTL_Y, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
               KC_Q,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, MY_COMP,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   SFT_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, SFT_SLS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_LGUI, MO(LNUM), MOV_SPC,    SFT_BSP, MO(LSYM), KC_LALT
                                            //`--------------------------'  `--------------------------'
    ),
    [LSYM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, KC_QUES, KC_LPRN, KC_RPRN, KC_PERC,                      KC_EXLM, MY_PIPE, KC_UNDS,   MY_AT, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, MY_TILD,  KC_GRV, KC_LBRC, KC_RBRC, KC_ASTR,                      KC_NUHS, MY_DQUO, KC_QUOT, KC_SCLN, KC_COLN, KC_NUBS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,  KC_EQL,  MY_GBP, KC_LCBR, KC_RCBR, KC_SLSH,                      KC_AMPR,   KC_LT,   KC_GT,  KC_DLR, KC_CIRC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, CTL_SPC,     _______,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LNUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   KC_NO, KC_UNDS,   KC_NO, KC_PERC,                      KC_PLUS,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_ASTR,                      KC_MINS,    KC_4,    KC_5,    KC_6, KC_ASTR, KC_PERC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   KC_NO,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH,                       KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______,  _______,     KC_0,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LFUN] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F10,   KC_F7,   KC_F8,   KC_F9, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                       KC_F11,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______,   KC_SPC,     _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOV] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, ALT_TAB, RGB_VAD, RGB_VAI, RGB_TOG,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT, KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                        KC_NO,  KC_TAB, KC_PGDN, KC_PGUP,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______,    KC_NO, _______,     _______,   KC_NO, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,  KC_ESC,  KC_TAB,   KC_NO,   KC_NO,                        KC_NO,   KC_NO, KC_MS_U,   KC_NO, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                      KC_WH_D,   KC_NO,   KC_NO,   KC_NO,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______,TO(LCMK),  KC_SPC,   KC_BTN1,  KC_BTN2, KC_BTN3
                                            //`--------------------------'  `--------------------------'
    ),
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/
void set_mods_lights(uint16_t keycode, bool active) {
    switch (keycode) {
        case KC_LSFT:
        case SFT_BSP:
        case SFT_Z:
        case SFT_SLS:
            rgblight_set_layer_state(12, active);
            break;
        case KC_LCTL:
        case CTL_Y:
        case CTL_W:
            rgblight_set_layer_state(11, active);
            break;
        case KC_LGUI:
            rgblight_set_layer_state(13, active);
            break;
        case KC_LALT:
            rgblight_set_layer_state(14, active);
            break;
    // we have to process the oneshot mod versions separately. this method is called from
    // process_record_user so is called for the key up event after the oneshot mod is tapped
    // and in that case we dont want to turn off the LEDs, though we do want lights for OSM
    // hold functions
        case OSM_SFT:
            if (!(get_oneshot_mods() & MOD_MASK_SHIFT)) {
                // only try and detect when the OSM is not active
                rgblight_set_layer_state(12, active);
            }
            break;
        case OSM_CTL:
            if (!(get_oneshot_mods() & MOD_MASK_CTRL)) {
                rgblight_set_layer_state(11, active);
            }
            break;
        case OSM_GUI:
            if (!(get_oneshot_mods() & MOD_MASK_GUI)) {
                rgblight_set_layer_state(13, active);
            }
            break;
        case OSM_ALT:
            if (!(get_oneshot_mods() & MOD_MASK_ALT)) {
                rgblight_set_layer_state(14, active);
            }
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_compose(keycode, record, MY_COMP)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    // set the mods lights the same as the one shots
    set_mods_lights(keycode, record->event.pressed);

    return true;
}


/******************************************************************************
 * compose key rgb lighting
 ******************************************************************************/
void compose_start(void) {
    rgblight_set_layer_state(8, true);
}


void compose_end(uint8_t state) {
    rgblight_set_layer_state(8, false);
    // show cancelled and error as the same state- we can only cancel by hitting the compose again
    if (state == COMPOSE_ERROR || state == COMPOSE_CANCELLED) {
        rgblight_blink_layer(9, 900);
    } else {
        // the compose action was activated
        rgblight_blink_layer(15, 900);
    }
}
/******************************************************************************
 * compose end
 ******************************************************************************/


/*******************************************************************************
 * case_mode rgb lighting
 *******************************************************************************/
void case_mode_set_user(bool active) {
    rgblight_set_layer_state(10, active);
}
/******************************************************************************
 * case_mode end
 ******************************************************************************/



/*******************************************************************************
 * RGB lighting on layer change
 * following are the LED numbers (in code it looks like we need to index one lower)
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
#define INNER_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {7, 3, HSV_ ##colour}, \
    {34, 3, HSV_ ##colour} \
);
#define INDEX_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {10, 3, HSV_ ##colour}, \
    {37, 3, HSV_ ##colour} \
);
#define MIDDLE_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {15, 3, HSV_ ##colour}, \
    {42, 3, HSV_ ##colour} \
);
#define RING_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {18, 3, HSV_ ##colour}, \
    {45, 3, HSV_ ##colour} \
);
#define PINKIE_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {21, 3, HSV_ ##colour}, \
    {48, 3, HSV_ ##colour} \
);

const rgblight_segment_t PROGMEM layer_default_lights[] = THUMB_KEYS(OFF)
const rgblight_segment_t PROGMEM layer_numpad_lights[] = THUMB_KEYS(ORANGE)
const rgblight_segment_t PROGMEM layer_symbols_lights[] = THUMB_KEYS(GREEN)
const rgblight_segment_t PROGMEM layer_motion_lights[] = THUMB_KEYS(BLUE)
const rgblight_segment_t PROGMEM layer_functions_lights[] = THUMB_KEYS(PURPLE)
const rgblight_segment_t PROGMEM layer_mouse_lights[] = THUMB_KEYS(RED)

const rgblight_segment_t PROGMEM oneshot_ctrl_active[] = MIDDLE_KEYS(BLUE)
const rgblight_segment_t PROGMEM oneshot_shift_active[] = INDEX_KEYS(GREEN)
const rgblight_segment_t PROGMEM oneshot_gui_active[] = RING_KEYS(RED)
const rgblight_segment_t PROGMEM oneshot_alt_active[] = PINKIE_KEYS(PURPLE)

// was INNER_KEYS(GREEN) but as this is similar to shift moved it to index.
const rgblight_segment_t PROGMEM caps_word_lights[] = INDEX_KEYS(GREEN)
const rgblight_segment_t PROGMEM snake_case_lights[] = INNER_KEYS(PURPLE)

const rgblight_segment_t PROGMEM compose_mode_lights[] = INNER_KEYS(ORANGE)
const rgblight_segment_t PROGMEM compose_cancel_lights[] = INNER_KEYS(RED)
const rgblight_segment_t PROGMEM compose_success_lights[] = INNER_KEYS(BLUE)

const rgblight_segment_t PROGMEM layer_no_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_OFF}
);

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_no_lights,
    layer_default_lights,
    layer_symbols_lights,
    layer_numpad_lights,
    layer_functions_lights,
    layer_motion_lights,
    layer_mouse_lights,
    caps_word_lights,
    compose_mode_lights,
    compose_cancel_lights,
    snake_case_lights,
    oneshot_ctrl_active,
    oneshot_shift_active,
    oneshot_gui_active,
    oneshot_alt_active,
    compose_success_lights
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // check the tristate layer and update
    state = update_tri_layer_state(state, LNUM, LSYM, LFUN);

    // set the led status to indicate layer
    rgblight_set_layer_state(1, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(2, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(3, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(4, layer_state_cmp(state, LFUN));
    rgblight_set_layer_state(5, layer_state_cmp(state, LMOV));
    rgblight_set_layer_state(6, layer_state_cmp(state, LMSE));
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(11, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(12, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(13, mods & MOD_MASK_GUI);
    rgblight_set_layer_state(14, mods & MOD_MASK_ALT);
}


void oneshot_locked_mods_changed_user(uint8_t mods) {
    rgblight_blink_layer(9, 5000);
    rgblight_set_layer_state(11, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(12, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(13, mods & MOD_MASK_GUI);
    rgblight_set_layer_state(14, mods & MOD_MASK_ALT);
}

/*******************************************************************************
 * END RGB lighting on layer change
 ******************************************************************************/

