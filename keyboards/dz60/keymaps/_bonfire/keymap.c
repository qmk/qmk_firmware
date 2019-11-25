#include QMK_KEYBOARD_H

/*
 * Each layer gets a name for readability. Layer names don't all need to be of the same
 * length, and you can also skip them entirely and just use numbers.
 *
 * 
 * Based originally on `dz60/zvecr`
 */
#define BASE    0   // Layer: QWERTY / Base
#define NRMN    1   // Layer: Norman
#define GAME    2   // Layer: Game
#define FCTN    3   // Layer: Function
#define KEYB    4   // Layer: Keyboard

/*
 * 
 * LAYOUT__bonfire                                               Row Keys
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │  0e   │ 14
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │ 14
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │ 13
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │ 13
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │ 8
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 *
 * XXXXXXX = Key does nothing.
 * _______ = Key that allows the uppermost exposed key in a layer below it.
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /**
     * Layer 0
     *
     * QWERTY and basic modifiers.
     * Upper layers are toggled or accessed through the "HACK" key: last key on fourth row.
     */
    [BASE] = LAYOUT__bonfire(
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, FUNC(0), MO(FCTN),
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, FUNC(2), FUNC(1), FUNC(3)
    ),

    /**
     * Layer 1
     *
     * NORMAN Key layout.
     * All that's changed is the position of A-Z and a few punctuation keys.
     */
    [NRMN] = LAYOUT__bonfire(
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
    [GAME] = LAYOUT__bonfire(
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        func(held_esc), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______
    ),

    /**
     * Layer 3
     *
     * Function layer.
     * This layer is accessed when "HACK" is held down.
     * Modifiers and such to basic keys, but with basic key functions.
     */
    [FCTN] = LAYOUT__bonfire(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,  _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,  _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,
        _______, KC_SLEP, KC_WAKE, _______, _______, _______,  _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______,
        _______, _______, _______, _______, KC_ESC,  MO(KEYB), _______, _______
    ),

    /**
     * Layer 4
     * 
     * This is the KEYB/System layer.
     * Other keymaps call this a NAV layer, but it's more than just NAV-ing the board's layers.
     * This Layer currently handles RGB and puts the board into RESET for flashing.
     *
     * ~ key resets board to [BASE].
     * 1 key toggles [NRMN].
     * 2 key toggles [GAME].
     * BACKSPACE puts board into reset.
     */
    [KEYB] = LAYOUT__bonfire(
        TO(0),   TG(NRMN), TG(GAME), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET, 
        XXXXXXX, RGB_TOG,  RGB_MOD,  RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, BL_DEC,   BL_TOGG,  BL_INC,  BL_STEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

/**
 * Key Mods Function
 *
 * This turns 3d, 4b, 4d and 4e into arrow keys when tapped,
 * and RSFT, RCTL, RGUI and HYPR, respectively.
 *
 * @DEPRECATED -- view: https://docs.qmk.fm/#/custom_quantum_functions
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_HYPR, KC_RIGHT),
};

// check out
// https://github.com/DanDobrick/qmk_firmware/blob/danDobrick-v60r-layout/keyboards/v60_type_r/keymaps/danDobrick/keymap.c#L140
// for lighting effects based on layer in use

/* Helper Grouping:

[NAME] = LAYOUT__bonfire(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______
)

 */
