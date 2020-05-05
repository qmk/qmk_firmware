/*
 * Good on you for modifying your layout, this is the most nonQMK layout you will come across
 *
 * http://docs.gboards.ca for how to modify your setup!
 * Your layout can be configured from dicts.def. This is
 * version 2, much different then version 1!
 *
 * http://docs.gboards.ca
 */

#include QMK_KEYBOARD_H
#include "keymap_steno.h"

#// Steno Engine Layers
#define FUNCT   (LSD | LK | LP | LH)
#define MEDIA   (LSD | LK | LW | LR)
#define MOVE    (ST1 | ST2)

// Generate Engine stuff
#include "g/keymap_engine.h"
#include "g/keymap_combo.h"

// QMK Layers
#define STENO_LAYER   0
#define TYPING        1 // Note if you move this layer, you must change config_engine.c!
#define GAMING        2
#define GAMING_2      3

/* Keyboard Layout
 * ,---------------------------------.    ,------------------------------.
 * | FN  | LSU | LFT | LP | LH | ST1 |    | ST3 | RF | RP | RL | RT | RD |
 * |-----+-----+-----+----+----|-----|    |-----|----+----+----+----+----|
 * | PWR | LSD | LK  | LW | LR | ST2 |    | ST4 | RR | BB | RG | RS | RZ |
 * `---------------------------------'    `------------------------------'
 *                   ,---------------,    .---------------.
 *                   | LNO | LA | LO |    | RE | RU | RNO |
 *                   `---------------'    `---------------'
 */

// "Layers"
// Steno layer should be first in your map.
// Note: If using NO_ACTION_TAPPING, LT will not work!
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Main layer - Steno
  [STENO_LAYER] = LAYOUT_georgi(
    STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,       STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
    STN_PWR, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,       STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
                               STN_N1,  STN_A,   STN_O,         STN_E,   STN_U,   STN_N7
  ),
  // Qwerty Emulation Layer (Hooked by Engine! DO NOT EDIT!)
  [TYPING] = LAYOUT_georgi(
    KC_LSFT, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,    KC_U, KC_I, KC_O, KC_P,    KC_BSPC,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H,    KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
                               KC_X, KC_C, KC_V,    KC_B, KC_N, KC_M
  ),
  // Gaming layer with Numpad, Very limited
  [GAMING] = LAYOUT_georgi(
    KC_LSFT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_DQUO,
                               KC_LALT, KC_SPC,  LT(GAMING_2, KC_ENT),       KC_DEL,  KC_ASTR, TO(STENO_LAYER)
  ),
  [GAMING_2] = LAYOUT_georgi(
    KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, KC_RSFT,
                               KC_LALT, KC_SPC,  KC_ENT,        KC_DEL,  KC_ASTR, TO(STENO_LAYER)
  )
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
