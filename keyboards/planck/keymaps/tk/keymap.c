#include QMK_KEYBOARD_H
#include "muse.h"


/*
    ██████╗ ███████╗███████╗██╗███╗   ██╗██╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
    ██╔══██╗██╔════╝██╔════╝██║████╗  ██║██║╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
    ██║  ██║█████╗  █████╗  ██║██╔██╗ ██║██║   ██║   ██║██║   ██║██╔██╗ ██║███████╗
    ██║  ██║██╔══╝  ██╔══╝  ██║██║╚██╗██║██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║
    ██████╔╝███████╗██║     ██║██║ ╚████║██║   ██║   ██║╚██████╔╝██║ ╚████║███████║
    ╚═════╝ ╚══════╝╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/


enum planck_layers {
    _BASE,
    _OSM,
    _HYPER,
    _LOWER1,
    _RAISE1,
    _LOWER2,
    _RAISE2,
};

#define GO_BASE TO(_BASE)

#define RAISE OSL(_RAISE1)
#define LOWER OSL(_LOWER1)

// Custom Keycodes

enum keycodes {
    ROTARY = SAFE_RANGE,
    PANIC,                  // backspace on tap, delete on tap with any modifier
    BK_P, BK_S, BK_C, BK_A, // (), [], {}, <> respectively

    // macros
    DOTFILE,    // dotfiles
    GT_ADD,     // git add
    GT_STAT,    // git status
    GT_CMT,     // git commit
    GT_PULL,    // git pull
    GT_PUSH,    // git push
    VIM_WQ      // [ESC]:wq
};

#define MOD1 MOD_HYPR // column 0
#define MOD2 MOD_LGUI // column 1
#define MOD3 MOD_LALT // column 2
#define MOD4 MOD_LCTL // column 3

#define MT_BK_P MT(MOD4, BK_P)
#define MT_BK_S MT(MOD3, BK_S)
#define MT_BK_C MT(MOD2, BK_C)
#define MT_BK_A MT(MOD1, BK_A)

#define MT_TAB  MT(MOD_LSFT, KC_TAB)
#define MT_GESC MT(MOD_LSFT, KC_GESC)

// Rotary Encoder states

enum encoder_states {
    VOLUME,
    MEDIA,      // media next/previous, play/pause
    BRIGHTNESS,
    SCROLL_V,   // scroll up/down, middle click
    SCROLL_H,   // scroll right/left, middle click
};

enum encoder_states rotary_state = VOLUME;


/*
    ██╗  ██╗███████╗██╗   ██╗███╗   ███╗ █████╗ ██████╗ ███████╗
    ██║ ██╔╝██╔════╝╚██╗ ██╔╝████╗ ████║██╔══██╗██╔══██╗██╔════╝
    █████╔╝ █████╗   ╚████╔╝ ██╔████╔██║███████║██████╔╝███████╗
    ██╔═██╗ ██╔══╝    ╚██╔╝  ██║╚██╔╝██║██╔══██║██╔═══╝ ╚════██║
    ██║  ██╗███████╗   ██║   ██║ ╚═╝ ██║██║  ██║██║     ███████║
    ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝     ╚══════╝
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer

    Tap Keycodes:

    |-----------------------------------------------------------------------------------------------|
    | Rotary|   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Panic |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |  Esc  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   | Enter |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |  Tab  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |   '   |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |  < >  |  { }  |  [ ]  |  ( )  | LOWER |     Space     | RAISE |   Lt  |   Dn  |   Up  |   Rt  |
    |-----------------------------------------------------------------------------------------------|

    Modifiers:

    |-----------------------------------------------------------------------------------------------|
    |       |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    | Shift |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    | HYPER |  Ctrl |  Meta | Super |       |               |       |       |       |       |       |
    |-----------------------------------------------------------------------------------------------|

    *
    * ' key: ' on tap, RSHIFT on hold
    * PANIC key: backspace on tap, delete on tap with SHIFT or CTRL modifier
    *
    * ESC key: esc on tap, ` on tap with SHIFT or CTRL modifier
    * BRACKET keys: open on tap, close on tap with SHIFT modifier
    *

*/

[_BASE] = LAYOUT_planck_grid(
    ROTARY,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,     KC_Y,     KC_U,  KC_I,    KC_O,    KC_P,    PANIC,
    KC_GESC, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,     KC_H,     KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,
    MT_TAB,  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,     KC_N,     KC_M,  KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_QUOT),
    MT_BK_A, MT_BK_C, MT_BK_S, MT_BK_P, LOWER, KC_SPACE, KC_SPACE, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
),

[_OSM] = LAYOUT_planck_grid(
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
    OSM(MOD_LSFT), _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
    OSM(MOD1), OSM(MOD2), OSM(MOD3), OSM(MOD4), _______, _______, _______, _______, _______, _______, _______, _______
),

/* Hyper layer

    |-----------------------------------------------------------------------------------------------|
    | Audio |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |  Caps |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    | Reset |       |       |       | Latch |      BASE     |Unlatch|       |       |       |       |
    |-----------------------------------------------------------------------------------------------|

    *
    * Only layer with inactive left-side modifiers
    * Right above base layer
    *
    * Latch key: latches modifiers
    * Unlatch key: unlatches modifiers
    *
    * Audio key: change hardware audio volume and toggle mute
    * Empty keys: left for software implementation
    *

*/
[_HYPER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise I - symbols

    |-----------------------------------------------------------------------------------------------|
    |       |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |   \   |   |   |   `   |   ~   |   '   |   "   |   _   |   -   |   +   |   =   |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |     Space     |       |       |       |       |       |
    |-----------------------------------------------------------------------------------------------|

    *
    * Each non-layer keypress moves to BASE (exception: rotary, arrow keys, enter, panic, numbers?)
    *

*/
[_RAISE1] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_BSLS, KC_PIPE, KC_GRV,  KC_TILD, KC_QUOT, KC_DQUO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  _______,
    _______, _______, _______, _______, _______, GO_BASE, GO_BASE, _______, _______, _______, _______, _______
),

/* Lower I - command snippets

    |-----------------------------------------------------------------------------------------------|
    | Rotary| wq vim|       |       |       |       |       |       |       |       | g push|       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       | g add | g stat|dotfile|       |       |       |       |       | g pull|       | Enter |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       | g cmt |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       | LOWER |      BASE     | RAISE |   Lt  |   Dn  |   Up  |   Rt  |
    |-----------------------------------------------------------------------------------------------|

    *
    * DO NOT INCLUDE DESTRUCTIVE COMMANDS
    * Stand-alone non-destructive commands are executed instantly (e.g. git status)
    * Each non-layer keypress moves to BASE (exception: rotary, arrow keys, enter)
    * Held modifiers temporarily move to BASE
    *

*/
[_LOWER1] = LAYOUT_planck_grid(
    _______, VIM_WQ,  _______, _______, _______, _______, _______, _______, _______, _______, GT_PUSH, _______,
    _______, GT_ADD,  GT_STAT, DOTFILE, _______, _______, _______, _______, _______, GT_PULL, _______, _______,
    _______, _______, _______,  GT_CMT, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, GO_BASE, GO_BASE, _______, _______, _______, _______, _______
),

/* Lower II - navigation

    |-----------------------------------------------------------------------------------------------|
    | Rotary| L Ck  |  M up |  R ck |       |       |       |       | Ctrl- | S up  | Ctrl+ |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |  M lt |  M dn |  M rt |       |       |       |       | S lt  | S dn  | S rt  |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       | LOWER |      BASE     | RAISE |   Lt  |   Dn  |   Up  |   Rt  |
    |-----------------------------------------------------------------------------------------------|

    *
    *
    *

*/
[_LOWER2] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise II - functions and dynamic macros

    |-----------------------------------------------------------------------------------------------|
    | Rotary|  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |  Esc  |  F11  |  F12  |  F13  |  F14  |  F15  |  F16  |  F17  |  F18  |  F19  |  F20  |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    |       |       |       |       | LOWER |      BASE     | RAISE |       |       |       |       |
    |-----------------------------------------------------------------------------------------------|

    *
    * Each non-layer keypress moves to BASE (exception: rotary)
    *
    * TODO: Add dynamic macro to this layer
    *

*/
[_RAISE2] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};


/*
     ██████╗██╗   ██╗███████╗████████╗ ██████╗ ███╗   ███╗    ██╗  ██╗███████╗██╗   ██╗ ██████╗ ██████╗ ██████╗ ███████╗███████╗
    ██╔════╝██║   ██║██╔════╝╚══██╔══╝██╔═══██╗████╗ ████║    ██║ ██╔╝██╔════╝╚██╗ ██╔╝██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔════╝
    ██║     ██║   ██║███████╗   ██║   ██║   ██║██╔████╔██║    █████╔╝ █████╗   ╚████╔╝ ██║     ██║   ██║██║  ██║█████╗  ███████╗
    ██║     ██║   ██║╚════██║   ██║   ██║   ██║██║╚██╔╝██║    ██╔═██╗ ██╔══╝    ╚██╔╝  ██║     ██║   ██║██║  ██║██╔══╝  ╚════██║
    ╚██████╗╚██████╔╝███████║   ██║   ╚██████╔╝██║ ╚═╝ ██║    ██║  ██╗███████╗   ██║   ╚██████╗╚██████╔╝██████╔╝███████╗███████║
     ╚═════╝ ╚═════╝ ╚══════╝   ╚═╝    ╚═════╝ ╚═╝     ╚═╝    ╚═╝  ╚═╝╚══════╝   ╚═╝    ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝
*/


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // state variables
    static bool del_active = false;  // true if DELETE is active

    // custom keycode logic
    switch (keycode) {
        case ROTARY:
            if (record->event.pressed) {
                if (rotary_state == VOLUME) {
                    tap_code(KC_MUTE);  // toggle mute
                }
                else if (rotary_state == MEDIA) {
                    tap_code(KC_MPLY);  // play/pause media
                }
                else if (rotary_state == SCROLL_V || rotary_state == SCROLL_H) {
                    tap_code(KC_BTN3);  // middle mouse button
                }
            }
            return false;
        case PANIC:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_HYPR)) {
                    tap_code(KC_A);
                    tap_code16(RESET);
                }
                else if (get_mods() & (MOD_BIT(KC_LSFT))) {
                    unregister_code(KC_LSFT);
                    register_code(KC_DEL);
                    del_active = true;
                }
                else {
                    register_code(KC_BSPACE);
                }
            }
            else {
                if (del_active) {
                    register_code(KC_LSFT);
                    unregister_code(KC_DEL);
                    del_active = false;
                }
                else {
                    unregister_code(KC_BSPACE);
                }
            }
            return false;

        case DOTFILE:
            if (record->event.pressed) {
                SEND_STRING("dotfiles ");
            }
            break;
        case GT_ADD:
            if (record->event.pressed) {
                SEND_STRING("git add ");
            }
            break;
        case GT_STAT:
            if (record->event.pressed) {
                SEND_STRING("git status ");
            }
            break;
        case GT_CMT:
            if (record->event.pressed) {
                SEND_STRING("git commit ");
            }
            break;
        case GT_PULL:
            if (record->event.pressed) {
                SEND_STRING("git pull ");
            }
            break;
        case GT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push ");
            }
            break;
        case VIM_WQ:
            if (record->event.pressed) {
                tap_code(KC_ESC);
                SEND_STRING(":wq");
            }
            break;
    }

    return true;
}


/*
    ██████╗  ██████╗ ████████╗ █████╗ ██████╗ ██╗   ██╗    ███████╗███╗   ██╗ ██████╗ ██████╗ ██████╗ ███████╗██████╗
    ██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔══██╗
    ██████╔╝██║   ██║   ██║   ███████║██████╔╝ ╚████╔╝     █████╗  ██╔██╗ ██║██║     ██║   ██║██║  ██║█████╗  ██████╔╝
    ██╔══██╗██║   ██║   ██║   ██╔══██║██╔══██╗  ╚██╔╝      ██╔══╝  ██║╚██╗██║██║     ██║   ██║██║  ██║██╔══╝  ██╔══██╗
    ██║  ██║╚██████╔╝   ██║   ██║  ██║██║  ██║   ██║       ███████╗██║ ╚████║╚██████╗╚██████╔╝██████╔╝███████╗██║  ██║
    ╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
*/


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    switch (rotary_state) {
        case VOLUME:
            if (clockwise) {
                tap_code(KC_VOLU);
            }
            else {
                tap_code(KC_VOLD);
            }
            break;
        case MEDIA:
            if (clockwise) {
                tap_code(KC_MNXT);
            }
            else {
                tap_code(KC_MPRV);
            }
            break;
        case BRIGHTNESS:
            if (clockwise) {
                tap_code(KC_BRIU);
            }
            else {
                tap_code(KC_BRID);
            }
            break;
        case SCROLL_V:
            if (clockwise) {
                tap_code(KC_WH_U);
            }
            else {
                tap_code(KC_WH_D);
            }
            break;
        case SCROLL_H:
            if (clockwise) {
                tap_code(KC_WH_R);
            }
            else {
                tap_code(KC_WH_L);
            }
            break;
    }
}
#endif
