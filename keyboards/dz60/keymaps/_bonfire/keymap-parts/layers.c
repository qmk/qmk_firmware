#pragma once
#include "quantum.h"

/*
 * LAYOUT_bonfire                                                Row Keys
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │  0e   │ 14
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │ 14
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │ 13
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │ 13
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │40  │41  │43  │           46           │4a  │4b  │4d  │4e  │ 8
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 *
*/
#define LAYOUT_bonfire( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
    k40, k41,      k43,           k46,                k4a, k4b,      k4d, k4e \
) { \
    { k00, k01,   k02,   k03, k04,   k05,   k06, k07,   k08,   k09,   k0a, k0b, k0c,   KC_NO, k0e   }, \
    { k10, KC_NO, k12,   k13, k14,   k15,   k16, k17,   k18,   k19,   k1a, k1b, k1c,   k1d,   k1e   }, \
    { k20, KC_NO, k22,   k23, k24,   k25,   k26, k27,   k28,   k29,   k2a, k2b, k2c,   k2d,   KC_NO }, \
    { k30, KC_NO, k32,   k33, k34,   k35,   k36, k37,   k38,   k39,   k3a, k3b, KC_NO, k3d,   k3e   }, \
    { k40, k41,   KC_NO, k43, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4a, k4b, KC_NO, k4d,   k4e   }  \
}

/**
 * XXXXXXX = Key does nothing.
 * _______ = Key that allows the uppermost exposed key in a layer below it.
 * 
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /**
     * Layer 0
     *
     * QWERTY and basic modifiers.
     * Upper layers are toggled or accessed through the "HACK" key: last key on fourth row.
     */
    [BASE] = LAYOUT_bonfire(
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,   KC_F,    KC_G,   KC_H,   KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, MOD_UP, MO(FCTN),
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MOD_LT, MOD_DN, MOD_RT
    ),

    /**
     * Layer 1
     *
     * NORMAN Key layout.
     * All that's changed is the position of A-Z and a few punctuation keys.
     */
    [NRMN] = LAYOUT_bonfire(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_Q,    KC_W,    KC_D,    KC_F,    KC_K,    KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN, _______, _______, _______,
        _______, KC_A,    KC_S,    KC_E,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_I,    KC_O,    KC_H,    _______, _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_P,    KC_M,    _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /**
     * Layer 2
     *
     * Moves the escape key from the left to the right side of the keyboard for gaming.
     */
    [GAME] = LAYOUT_bonfire(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        HLD_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /**
     * Layer 3
     *
     * Function layer.
     * This layer is accessed when "HACK" is held down.
     * Modifiers and such to basic keys, but with basic key functions.
     */
    [FCTN] = LAYOUT_bonfire(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,  _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______,
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,  _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,
        _______, KC_SLEP, KC_WAKE, _______, _______, _______,  _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______,
        _______, _______, _______, _______, _______, MO(KEYB), _______, _______
    ),

    /**
     * Layer 4
     * 
     * This is the KEYB/System layer.
     * Other keymaps call this a NAV layer, but it's more than just NAV-ing the board's layers.
     * This Layer currently handles RGB and puts the board into QK_BOOT for flashing.
     *
     * ~ key resets board to [BASE].
     * 1 key toggles [NRMN].
     * 2 key toggles [GAME].
     * BACKSPACE puts board into reset.
     */
    [KEYB] = LAYOUT_bonfire(
        TO(BASE), TG(NRMN), TO(GAME), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, 
        XXXXXXX,  RGB_TOG,  RGB_MOD,  RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  BL_DOWN,  BL_TOGG,  BL_UP,   BL_STEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
    )
};
