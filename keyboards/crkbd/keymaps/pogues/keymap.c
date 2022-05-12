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
#include "features/compose.h"
#include "features/custom_shift_keys.h"
#include "features/layer_lock.h"

enum userspace_layers {
    LCMK = 0,
    LSYM = 1,
    LNUM = 2,
    LFUN = 3,
    LMOV = 4,
    LMSE = 5,
};

// the layer mask
#define L_COLEMAK LCMK
#define LMASK_SYM (1 << LSYM)
#define LMASK_NUM (1 << LNUM)
#define LMASK_FUN (1 << LFUN)
#define LMASK_MOV (1 << LMOV)
#define LMASK_MSE (1 << LMSE)

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)
#define MY_GBP KC_HASH      // just shift-3
#define ALT_TAB ALT_T(KC_TAB)

// one shot mod and layer keys to make the map shorter
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)

#define LNUM_SPC LT(LNUM, KC_SPC)
#define LSYM_BSP LT(LSYM, KC_BSPC)

#define SFT_SPC SFT_T(KC_SPC)
#define CTL_BSP CTL_T(KC_BSPC)

enum custom_keycodes {
    MY_LLCK = SAFE_RANGE,   // layer lock key
    MY_COMP,
};

// tap dance key enumaration
enum {
    TD_LNUM,
    TD_LSYM,
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT , KC_COLN}, // Shift . is :
    {KC_COMM, KC_SCLN}, // Shift , is ;
    {KC_SLSH, KC_QUOT}, // Shift / is '
    {KC_2, KC_DQUO},    // need shift 2 to be " for win+shift+2 to work in dwm
    {LSYM_BSP, KC_DEL}  // shift backspace is delete
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // colemak-dh
    [LCMK] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, MY_COMP, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
               KC_Q,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, MY_COMP,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           // KC_LCTL, KC_LSFT, LNUM_SPC,    LSYM_BSP, KC_RSFT, KC_RCTL
                                           // KC_LGUI, MO(LNUM), SFT_SPC,    CTL_BSP, MO(LSYM), KC_LALT
                                           // KC_LGUI, MO(LNUM), SFT_SPC,    LSYM_BSP, KC_LCTL, KC_LALT
                                              KC_LGUI, TD(TD_LNUM), SFT_SPC,    LSYM_BSP, KC_LCTL, KC_LALT
                                           // KC_LGUI, TD(TD_LNUM), SFT_SPC,    TD(TD_LSYM), KC_LCTL, KC_LALT
                                            //`--------------------------'  `--------------------------'
    ),
    [LSYM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX,  KC_ESC, KC_QUES, KC_LPRN, KC_RPRN, MY_PIPE,                      KC_EXLM, MY_PIPE, KC_UNDS,   MY_AT, KC_NUBS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             KC_TAB, XXXXXXX, KC_AMPR, KC_LBRC, KC_RBRC, MY_TILD,                      KC_NUHS, MY_DQUO, KC_QUOT, KC_SCLN, KC_COLN, KC_NUBS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, MY_LLCK,  MY_GBP, KC_LCBR, KC_RCBR,  KC_GRV,                      KC_AMPR,   KC_LT,   KC_GT,  KC_DLR, KC_CIRC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LNUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX,TO(LFUN), KC_PERC, KC_SLSH,                      KC_PLUS,    KC_7,    KC_8,    KC_9,  KC_DEL, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_ASTR,                      KC_MINS,    KC_4,    KC_5,    KC_6,  KC_ENT,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, MY_LLCK, XXXXXXX, KC_COMM,  KC_DOT, XXXXXXX,                       KC_EQL,    KC_1,    KC_2,    KC_3,  KC_TAB, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            // XXXXXXX, _______,  _______,     KC_0,  _______, XXXXXXX
                                              XXXXXXX, _______,  _______,     _______,  KC_0, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LFUN] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F10,   KC_F7,   KC_F8,   KC_F9,  KC_DEL, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, XXXXXXX,                       KC_F11,   KC_F4,   KC_F5,   KC_F6,  KC_ENT,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,TO(LCMK), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F12,   KC_F1,   KC_F2,   KC_F3,  KC_TAB, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            // XXXXXXX, TO(LCMK), _______,     KC_F10,  XXXXXXX, XXXXXXX
                                               XXXXXXX, TO(LCMK), _______,     XXXXXXX,  KC_F10, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOV] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, ALT_TAB, XXXXXXX,TO(LMSE), XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            ALT_TAB, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, XXXXXXX,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, MY_LLCK, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_TAB, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              XXXXXXX, _______, _______,     _______,  _______, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    ),
    [LMSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3,                      XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_BTN1,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,TO(LCMK), KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN2,                      KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            //  XXXXXXX,TO(LCMK), _______,   _______,  KC_BTN1, XXXXXXX
                                                XXXXXXX,TO(LCMK), _______,   KC_BTN1,  _______, XXXXXXX
                                            //`--------------------------'  `--------------------------'
    )
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_layer_lock(keycode, record, MY_LLCK)) {
        return false;
    }
    if (!process_compose(keycode, record, MY_COMP)) {
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


/******************************************************************************
 * combo keys
 ******************************************************************************/
enum combo_keys {
    COMBO_L_RM_T_ESC,
    COMBO_L_MI_B_TAB,
    //COMBO_R_RM_T_BSPC,
    //COMBO_R_RM_B_DEL,
    COMBO_R_RM_T_DEL,
    COMBO_R_MI_B_ENT,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// left hand, ring+middle finger, top row
const uint16_t PROGMEM lh_rm_t_combo[] = {KC_W, KC_F, COMBO_END};
// left hand, middle+index finger, bottom row
const uint16_t PROGMEM lh_mi_b_combo[] = {KC_C, KC_D, COMBO_END};
// right hand, ring+middle finger, top row
const uint16_t PROGMEM rh_rm_t_combo[] = {KC_U, KC_Y, COMBO_END};
// right hand, ring+middle finger, bottom row
//const uint16_t PROGMEM rh_rm_b_combo[] = {KC_COMM, KC_DOT, COMBO_END};
// right hand, middle+index finger, bottom row
const uint16_t PROGMEM rh_mi_b_combo[] = {KC_H, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    [COMBO_L_RM_T_ESC] = COMBO(lh_rm_t_combo, KC_ESC),
    [COMBO_L_MI_B_TAB] = COMBO(lh_mi_b_combo, KC_TAB),
    //[COMBO_R_RM_T_BSPC] = COMBO(rh_rm_t_combo, KC_BSPC),
    //[COMBO_R_RM_B_DEL] = COMBO(rh_rm_b_combo, KC_DEL),
    [COMBO_R_RM_T_DEL] = COMBO(rh_rm_t_combo, KC_DEL),
    [COMBO_R_MI_B_ENT] = COMBO(rh_mi_b_combo, KC_ENT),
};
 /******************************************************************************/

/******************************************************************************
 * compose key mapping function
 ******************************************************************************/
uint8_t compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // NOTE that the COMPOSE_MAPPING will return if there is a full or partial
    // match to the sequence.

    // c to enter caps word mode.
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_C),
        {   // toggle capsword
            caps_word_set(!caps_word_get());
        }
    )
    // q to quit dwm
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Q),
        { SEND_STRING(SS_LGUI(SS_LSFT("q"))); }
    )

    //  all copy  /  all cut ?
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_C),
        { SEND_STRING(SS_LCTL("ac")); }
    )
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_X),
        { SEND_STRING(SS_LCTL("ax")); }
    )
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_P),
        { SEND_STRING(SS_LCTL("v")); }
    )

    /**********************************************************************
     * qzdev
     *********************************************************************/
    // o to open a file
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL(SS_LSFT("o"))); }
    )

    // diff current
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("g"))); }
    )
    // diff approved
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_A),
        { SEND_STRING(SS_LCTL(SS_LSFT("v"))); }
    )
    // diff prod
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("p"))); }
    )
    // diff head
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_H),
        { SEND_STRING(SS_LCTL(SS_LSFT("e"))); }
    )
    // diff against version
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_V),
        { SEND_STRING(SS_LCTL(SS_LSFT("d"))); }
    )

    // test function
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_F),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F10))); }
    )
    // test class
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F10)))); }
    )
    // test script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_S),
        { SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_F10)))); }
    )

    // run script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_S),
        { tap_code(KC_F9); }
    )
    // run script with restart
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_R),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F9))); }
    )

    return COMPOSE_ERROR;
}

void compose_start(void) {
    rgblight_set_layer_state(8, true);
}

void compose_end(uint8_t state) {
    rgblight_set_layer_state(8, false);
    if (state == COMPOSE_ERROR) {
        rgblight_blink_layer(9, 900);
    } else if (state == COMPOSE_CANCELLED) {
        rgblight_blink_layer(10, 900);
    }
    // other state is OK.
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

void matrix_scan_user(void) {
#if CAPS_WORD_IDLE_TIMEOUT > 0
     caps_word_task();
#endif

}

/*******************************************************************************
* Tap Dance definitions
*******************************************************************************/
typedef struct {
    bool is_press_action;
    uint8_t step;
} td_tap_t;

static td_tap_t dance_state_lnum = {.is_press_action = true, .step = 0};
static td_tap_t dance_state_lsym = {.is_press_action = true, .step = 0};

// simplified dance steps to indicate held, one tap or two
enum {
    SINGLE_TAP = 1,
    DOUBLE_TAP,
    HELD,
};

uint8_t current_dance_step(qk_tap_dance_state_t *state) {
    if (state->pressed) {
        return HELD;
    }
    if (state->count == 1) {
        return SINGLE_TAP;
    } else {  // everything over one is taken as double
        return DOUBLE_TAP;
    }
}

void tapdance_lnum_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state_lnum.step = current_dance_step(state);
    switch (dance_state_lnum.step) {
        case SINGLE_TAP:
            // if we are in the layer, exit, otherwise toggle the one shot mod
            if (layer_state_is(LNUM)) {
                layer_off(LNUM);
            } else {
                set_oneshot_layer(LNUM, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            break;
        case DOUBLE_TAP:
        case HELD:
            layer_on(LNUM);
            break;
    }
}

void tapdance_lnum_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state_lnum.step) {
        case SINGLE_TAP:
        case DOUBLE_TAP:
            break;
        case HELD:
            layer_off(LNUM);
            break;
    }
    dance_state_lnum.step = 0;
}

void tapdance_lsym_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state_lsym.step = current_dance_step(state);
    switch (dance_state_lsym.step) {
        case SINGLE_TAP:
            // if we are in the layer, exit, otherwise toggle the one shot mod
            if (layer_state_is(LSYM)) {
                layer_off(LSYM);
            } else {
                set_oneshot_layer(LSYM, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            break;
        case DOUBLE_TAP:
        case HELD:
            layer_on(LSYM);
            break;
    }
}

void tapdance_lsym_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state_lsym.step) {
        case SINGLE_TAP:
        case DOUBLE_TAP:
            break;
        case HELD:
            layer_off(LSYM);
            break;
    }
    dance_state_lsym.step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LNUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_lnum_finished, tapdance_lnum_reset),
    [TD_LSYM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_lsym_finished, tapdance_lsym_reset)
};

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

const rgblight_segment_t PROGMEM layer_default_lights[] = THUMB_KEYS(OFF)
const rgblight_segment_t PROGMEM layer_numpad_lights[] = THUMB_KEYS(ORANGE)
const rgblight_segment_t PROGMEM layer_symbols_lights[] = THUMB_KEYS(GREEN)
const rgblight_segment_t PROGMEM layer_motion_lights[] = THUMB_KEYS(BLUE)
const rgblight_segment_t PROGMEM layer_functions_lights[] = THUMB_KEYS(PURPLE)
const rgblight_segment_t PROGMEM layer_mouse_lights[] = THUMB_KEYS(MAGENTA)

const rgblight_segment_t PROGMEM oneshot_ctrl_active[] = RGBLIGHT_LAYER_SEGMENTS({9, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM oneshot_shift_active[] = RGBLIGHT_LAYER_SEGMENTS({8, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM oneshot_gui_active[] = RGBLIGHT_LAYER_SEGMENTS({7, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM oneshot_alt_active[] = RGBLIGHT_LAYER_SEGMENTS({6, 1, HSV_PURPLE});

const rgblight_segment_t PROGMEM caps_word_lights[] = INNER_KEYS(GREEN)

const rgblight_segment_t PROGMEM compose_mode_lights[] = INNER_KEYS(ORANGE)
const rgblight_segment_t PROGMEM compose_fail_lights[] = INNER_KEYS(RED)
const rgblight_segment_t PROGMEM compose_cancel_lights[] = INNER_KEYS(BLUE)

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
    compose_fail_lights,
    compose_cancel_lights,
    oneshot_ctrl_active,
    oneshot_shift_active,
    oneshot_gui_active,
    oneshot_alt_active
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // check for the tristate layre
    state = update_tri_layer_state(state, LNUM, LSYM, LMOV);

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
    rgblight_set_layer_state(11, false);
    rgblight_set_layer_state(12, false);
    rgblight_set_layer_state(13, false);
    rgblight_set_layer_state(14, false);

    if (mods & MOD_MASK_SHIFT) {
        rgblight_set_layer_state(12, true);
    }
    if (mods & MOD_MASK_CTRL) {
        rgblight_set_layer_state(11, true);
    }
    if (mods & MOD_MASK_ALT) {
        rgblight_set_layer_state(14, true);
    }
    if (mods & MOD_MASK_GUI) {
        rgblight_set_layer_state(13, true);
    }
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

void oled_render_logo_left(void) {
    static const char PROGMEM deer_butt_logo[] = {
        // 'deer-butt-horizontal', 128x32px
        0x00, 0x7c, 0x3c, 0x3c, 0x1c, 0x1e, 0x1e, 0x0e, 0x0e, 0x0e, 0x0c, 0x1c, 0x1c, 0x1c, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x38, 0x38, 0x32, 0x72, 0xe2, 0x86, 0x0c, 0x18, 0x20, 0x60, 0xc0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0f, 0x1c, 0x70, 0xc0, 0x80,
        0x00, 0x01, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x84, 0x80, 0x80, 0xc0, 0xc0, 0xc0,
        0x60, 0x60, 0x60, 0x20, 0x30, 0x30, 0x30, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02,
        0x06, 0x0e, 0x3c, 0xfc, 0xfc, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x80, 0xa0, 0x80, 0xd0, 0x40, 0x48, 0x60,
        0x64, 0x30, 0x3a, 0x38, 0x19, 0x38, 0x38, 0x71, 0xe0, 0xc2, 0x86, 0x04, 0x04, 0x0c, 0x0d, 0x0f,
        0x0f, 0x0e, 0x0c, 0x0c, 0x06, 0x06, 0x06, 0x02, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x7c, 0x3e, 0x1e, 0x1e, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x06, 0x0c, 0x18, 0x18,
        0x10, 0x30, 0x30, 0x20, 0x20, 0x20, 0x60, 0x60, 0x20, 0x60, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(deer_butt_logo, sizeof(deer_butt_logo));
};

void oled_render_logo_right(void) {
    static const char PROGMEM deer_head_logo[] = {
        // 'deer-head-horizontal', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x02, 0x0c, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x30, 0x70, 0x70, 0x70, 0x70, 0x60, 0x60, 0x60,
        0x30, 0x30, 0x30, 0x30, 0x30, 0x10, 0x10, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x28,
        0x18, 0x18, 0x50, 0x70, 0x60, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
        0xc0, 0x60, 0x30, 0x18, 0x1c, 0x0e, 0x07, 0x87, 0xe7, 0x30, 0x00, 0x00, 0x00, 0x20, 0x20, 0x60,
        0x60, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x1f, 0x3e, 0x3c, 0x7c, 0x78,
        0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0x00,
        0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x26, 0x1a, 0x0f, 0x03, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3b, 0x1c, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x02, 0x02,
        0x06, 0x04, 0x0c, 0x18, 0x78, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x20, 0x20, 0xe0, 0xe1, 0x61, 0x61, 0x21, 0x21, 0x21, 0x21, 0x01, 0x01, 0x01, 0x11, 0x11, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
    };
    oled_write_raw_P(deer_head_logo, sizeof(deer_head_logo));
};

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_logo_left();
    } else {
        oled_render_logo_right();
    }
    return false;
}


#endif // OLED_ENABLE
