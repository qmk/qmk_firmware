#include "quantum.h"

enum {
    MIN,
    EQL,

    ESC,
    BSP,
    DEL,

    BSL,

    CUT,
    GRA,
};

const uint16_t PROGMEM min[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM eql[] = {KC_N, KC_M, COMBO_END};

const uint16_t PROGMEM esc[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM bsp[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM del[] = {KC_DOWN, KC_UP, COMBO_END};

const uint16_t PROGMEM bsl[] = {KC_I, KC_O, COMBO_END};

const uint16_t PROGMEM cut[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM gra[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [MIN] = COMBO(min, KC_MINS),
    [EQL] = COMBO(eql, KC_EQL),

    [ESC] = COMBO(esc, KC_ESC),
    [BSP] = COMBO(bsp, KC_BSPC),
    [DEL] = COMBO(del, KC_DEL),

    [BSL] = COMBO(bsl, KC_BSLS),

    [CUT] = COMBO(cut, KC_QUOT),
    [GRA] = COMBO(gra, KC_GRAVE),
};
