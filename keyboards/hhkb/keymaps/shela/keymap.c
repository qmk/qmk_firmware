/*
 * HHKB Pro 2 US Layout for shela
 */
#include QMK_KEYBOARD_H
#include "keymap_jis2us.h"
#include "action_pseudo_lut.h"

enum keymap_layout
{
    BASE = 0,
    PSEUDO_US,
    DVORAK,
    MOUSE,
    TENKEY,
    HHKB,
    SPACE_FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  `  | BSp |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |
     * |-----------------------------------------------------------------------------------------|
     * | Control  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |    Shift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  Shift  | Fn0 |
     * `-----------------------------------------------------------------------------------------'
     *           |LAlt |  LGui  |               SpaceFN             |  RGui  |RAlt |
     *           `-----------------------------------------------------------------'
     */
    [BASE] =
        LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC,
               KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
               KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
               OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_FN0,
               KC_LALT, KC_LGUI, KC_FN2, KC_RGUI, KC_RALT),

    /* Layer 1: Pseudo US Layout Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | BSp |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 |  Fn1   |
     * |-----------------------------------------------------------------------------------------|
     * | Control  | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |    Shift    | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 | Fn1 |  Shift  | Fn0 |
     * `-----------------------------------------------------------------------------------------'
     *           |LGui |  Fn3   |               SpaceFN             |  Fn4   |RGui |
     *           `-----------------------------------------------------------------'
     */
    [PSEUDO_US] =
        LAYOUT(KC_ESC, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_BSPC,
               KC_TAB, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1,
               KC_LCTL, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_ENT,
               KC_LSFT, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_FN1, KC_RSFT, KC_FN0,
               KC_LGUI, KC_FN3, KC_FN2, KC_FN4, KC_RGUI),

    /* Layer 2: Dvorak Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  [  |  ]  |  `  | BSp |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |  '  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |  /  |  =  |   \    |
     * |-----------------------------------------------------------------------------------------|
     * | Control  |  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |  -  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |    Shift    |  ;  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  |  Shift  | Fn0 |
     * `-----------------------------------------------------------------------------------------'
     *           |LAlt |  LGui  |              SpaceFN              |  RGui  |RAlt |
     *           `-----------------------------------------------------------------'
     */
    [DVORAK] =
        LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC, KC_GRV, KC_BSPC,
               KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_BSLS,
               KC_LCTL, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT,
               KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT, KC_FN0,
               KC_LALT, KC_LGUI, KC_FN2, KC_RGUI, KC_RALT),

    /* Layer 3: Mouse layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |     |     |
     * |-----------------------------------------------------------------------------------------|
     * |        |     |     |     |     |     | MwL | MwD | MwU | MwR |     |     |     |        |
     * |-----------------------------------------------------------------------------------------|
     * |          |     |     |     |     |     | McL | McD | McU | McR |     |     |            |
     * |-----------------------------------------------------------------------------------------|
     * |             |     |     |     |     |     | Mb1 | Mb2 | Mb3 |     |     |         | Fn0 |
     * `-----------------------------------------------------------------------------------------'
     *           |     |        |                Mb1                |        |     |
     *           `-----------------------------------------------------------------'
     */
    [MOUSE] =
        LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_TRNS,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO, KC_NO, KC_NO, KC_NO,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_NO, KC_TRNS,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO, KC_NO, KC_TRNS, KC_FN0,
               KC_TRNS, KC_TRNS, KC_BTN1, KC_TRNS, KC_TRNS),

    /* Layer 4: Tenkey layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |     |     |     |     |     |     |     |     |     |  /  |  *  |  -  |     | BSp |
     * |-----------------------------------------------------------------------------------------|
     * |        |     |     |     |     |     |     |     |     |  7  |  8  |  9  |  +  |        |
     * |-----------------------------------------------------------------------------------------|
     * |          |     |     |     |     |     |     |     |     |  4  |  5  |  6  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |             |     |     |     |     |     |     |     |  1  |  2  |  3  |    +    | Fn0 |
     * `-----------------------------------------------------------------------------------------'
     *           |     |        |              SpaceFN              |   0    |  .  |
     *           `-----------------------------------------------------------------'
     */
    [TENKEY] =
        LAYOUT(KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSLS, KC_PAST, KC_PMNS, KC_NO, KC_BSPC,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, KC_NO,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_KP_4, KC_KP_5, KC_KP_6, KC_PENT,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS, KC_FN0,
               KC_TRNS, KC_TRNS, KC_FN2, KC_KP_0, KC_PDOT),

    /* Layer 5: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------------------------------------.
     * | Pwr | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
     * |-----------------------------------------------------------------------------------------|
     * |  Caps  | Fn5 | Fn6 | Fn7 | Fn8 | Fn9 |     |     | Psc | Slk | Pus | Up  |     |  BSp   |
     * |-----------------------------------------------------------------------------------------|
     * |          | VoD | VoU | Mut |     |     |  *  |  /  | Hom | PgU | Lef | Rig |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |             |     |     |     |     |     |  +  |  -  | End | PgD | Dow |         |     |
     * `-----------------------------------------------------------------------------------------'
     *           |     |        |                                   |        |     |
     *           `-----------------------------------------------------------------'
     */
    [HHKB] =
        LAYOUT(KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
               KC_CAPS, KC_FN5, KC_FN6, KC_FN7, KC_FN8, KC_FN9, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
               KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* Layer 6: SpaceFN
     * ,-----------------------------------------------------------------------------------------.
     * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |     | Del |
     * |-----------------------------------------------------------------------------------------|
     * |        | Hom | Up  | End |     |     |     | Hom | End |     | Psc | Slk | Pau |  Ins   |
     * |-----------------------------------------------------------------------------------------|
     * |          | Lef | Dow | Rig | PgU |     | Lef | Dow | Up  | Rig |     |     |            |
     * |-----------------------------------------------------------------------------------------|
     * |             |     |     | PgD |     | Spc |     | PgD | PgU |     |     |         |     |
     * `-----------------------------------------------------------------------------------------'
     *           |     |        |                                   |        |     |
     *           `-----------------------------------------------------------------'
     */
    [SPACE_FN] =
        LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_DEL,
               KC_TRNS, KC_HOME, KC_UP, KC_END, KC_NO, KC_NO, KC_NO, KC_HOME, KC_END, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,
               KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_TRNS,
               KC_TRNS, KC_NO, KC_NO, KC_PGDN, KC_NO, KC_SPC, KC_NO, KC_PGDN, KC_PGUP, KC_NO, KC_NO, KC_TRNS, KC_NO,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

/*
 * user defined action function
 */
enum function_id
{
    PSEUDO_US_FUNCTION,
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{

    switch (id)
    {
    case PSEUDO_US_FUNCTION:
        action_pseudo_lut(record, BASE, keymap_jis2us);
        break;
    }
}

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(HHKB),
    [1] = ACTION_FUNCTION(PSEUDO_US_FUNCTION),
    [2] = ACTION_LAYER_TAP_KEY(SPACE_FN, KC_SPACE),
    [3] = ACTION_MODS_TAP_KEY(MOD_LALT, KC_MHEN),
    [4] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_KANA),
    [5] = ACTION_DEFAULT_LAYER_SET(BASE),
    [6] = ACTION_DEFAULT_LAYER_SET(PSEUDO_US),
    [7] = ACTION_DEFAULT_LAYER_SET(MOUSE),
    [8] = ACTION_DEFAULT_LAYER_SET(TENKEY),
    [9] = ACTION_DEFAULT_LAYER_SET(DVORAK),
};
