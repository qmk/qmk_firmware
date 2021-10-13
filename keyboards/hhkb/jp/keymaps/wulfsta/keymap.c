#include QMK_KEYBOARD_H


#define MOD_MASK_NONE 0

#define BASE_LAYER (1 << 0)
#define NUMROW_LAYER (1 << 1)
#define CMDKEY_LAYER (1 << 2)
#define NUMPAD_LAYER (1 << 3)
#define ALL_LAYERS ~0


enum custom_keycodes {
    O_ESC = SAFE_RANGE,
    O_MINS,
    O_PLUS,
    O_EQL,
    O_LCBR,
    O_RCBR,
    O_LPRN,
    O_RPRN,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_JP(
        O_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_RSFT,
        MO(1), MO(2), KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_RGUI, KC_ENT, KC_RALT, MO(3), KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT_JP(
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [2] = LAYOUT_JP(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_END, KC_PGDN, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),


    [3] = LAYOUT_JP(
        KC_GRV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, _______,
        KC_TAB, _______, _______, O_MINS, O_PLUS, O_EQL, _______, KC_1, KC_2, KC_3, KC_P, _______, _______,
        _______, O_LCBR, O_RCBR, O_LPRN, O_RPRN, _______, _______, KC_4, KC_5, KC_6, _______, _______, _______, _______,
        KC_LSFT, _______, _______, _______, _______, _______, KC_DOT, KC_7, KC_8, KC_9, _______, KC_RSFT, _______, KC_RSFT,
        _______, _______, _______, _______, _______, _______, KC_0, _______, _______, _______, _______, _______, _______),
};


const key_override_t o_esc_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_ESC, KC_ESC, ALL_LAYERS, MOD_MASK_SHIFT); 
const key_override_t l0_o_esc_override = ko_make_with_layers(MOD_MASK_SHIFT, O_ESC, KC_TILD, BASE_LAYER); // In case Shift + Esc is needed, only do this on layer 0.

const key_override_t l3_o_mins_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_MINS, KC_MINS, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_mins_override = ko_make_with_layers(MOD_MASK_SHIFT, O_MINS, KC_SLSH, NUMPAD_LAYER);

const key_override_t l3_o_plus_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_PLUS, KC_PLUS, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_plus_override = ko_make_with_layers(MOD_MASK_SHIFT, O_PLUS, KC_ASTR, NUMPAD_LAYER);

const key_override_t l3_o_eql_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_EQL, KC_EQL, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_eql_override = ko_make_with_layers(MOD_MASK_SHIFT, O_EQL, KC_CIRC, NUMPAD_LAYER);

const key_override_t l3_o_lcbr_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_LCBR, KC_LCBR, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_lcbr_override = ko_make_with_layers(MOD_MASK_SHIFT, O_LCBR, KC_LT, NUMPAD_LAYER);

const key_override_t l3_o_rcbr_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_RCBR, KC_RCBR, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_rcbr_override = ko_make_with_layers(MOD_MASK_SHIFT, O_RCBR, KC_GT, NUMPAD_LAYER);

const key_override_t l3_o_lprn_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_LPRN, KC_LPRN, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_lprn_override = ko_make_with_layers(MOD_MASK_SHIFT, O_LPRN, KC_LBRC, NUMPAD_LAYER);

const key_override_t l3_o_rprn_default = ko_make_with_layers_and_negmods(MOD_MASK_NONE, O_RPRN, KC_RPRN, NUMPAD_LAYER, MOD_MASK_SHIFT);
const key_override_t l3_o_rprn_override = ko_make_with_layers(MOD_MASK_SHIFT, O_RPRN, KC_RBRC, NUMPAD_LAYER);


// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &o_esc_default,
    &l0_o_esc_override,
    &l3_o_mins_default,
    &l3_o_mins_override,
    &l3_o_plus_default,
    &l3_o_plus_override,
    &l3_o_eql_default,
    &l3_o_eql_override,
    &l3_o_lcbr_default,
    &l3_o_lcbr_override,
    &l3_o_rcbr_default,
    &l3_o_rcbr_override,
    &l3_o_lprn_default,
    &l3_o_lprn_override,
    &l3_o_rprn_default,
    &l3_o_rprn_override,
    NULL // Null terminate the array of overrides!
};

