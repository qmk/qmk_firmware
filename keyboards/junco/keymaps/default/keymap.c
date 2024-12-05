// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
// Layers enum
enum junco_layers { _QWERTY, _COLEMAK_DH, _SYMB, _EXT, _ADJUST };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
        Traditional QWERTY
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │               │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │Ent│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Esc│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │ ' │
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │Sft│ Z │ X │ C │ V │ B │Mut│       │XXX│ N │ M │ , │ . │ / │Sft│
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │Ctr│Win│Alt│Del│Spc│       │Sft│Bsp│Alt│Win│Ctr│
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
                For macOS - GUI (cmd) and Alt (opt) swapped
    */
    [_QWERTY] = LAYOUT_split4x6_r1(
        KC_GRAVE, KC_1, KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,               KC_7,    KC_8,    KC_9,   KC_0,         KC_MINUS,
        KC_TAB,   KC_Q, KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,               KC_U,    KC_I,    KC_O,   KC_P,         KC_ENTER,
        KC_ESC,   KC_A, KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,               KC_J,    KC_K,    KC_L,   KC_SEMICOLON, KC_QUOTE,
        KC_LSFT,  KC_Z, KC_X,    KC_C,    KC_V,    KC_B,             KC_MUTE,  KC_NO,   KC_N,               KC_M,    KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,
                        KC_LCTL, KC_LGUI, KC_LALT, LT(_EXT, KC_DEL), KC_SPC,   KC_RSFT, LT(_SYMB, KC_BSPC), KC_RALT, KC_RGUI, KC_RCTL
    ),

    /*
        Colemak-DH
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │               │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Tab│ Q │ W │ F │ P │ B │               │ J │ L │ U │ Y │ ; │Ent│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Esc│ A │ R │ S │ T │ G │               │ M │ N │ E │ I │ O │ ' │
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │Sft│ Z │ X │ C │ D │ V │Mut│       │XXX│ K │ H │ , │ . │ / │Sft│
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │Ctr│Win│Alt│Del│Spc│       │Sft│Bsp│Alt│Win│Ctr│
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
                For macOS - GUI (cmd) and Alt (opt) swapped
    */
    [_COLEMAK_DH] = LAYOUT_split4x6_r1(
        KC_GRAVE, KC_1, KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,               KC_7,    KC_8,    KC_9,   KC_0,         KC_MINUS,
        KC_TAB,   KC_Q, KC_W,    KC_F,    KC_P,    KC_B,                                KC_J,               KC_L,    KC_U,    KC_Y,   KC_SEMICOLON, KC_ENTER,
        KC_ESC,   KC_A, KC_R,    KC_S,    KC_T,    KC_G,                                KC_M,               KC_N,    KC_E,    KC_I,   KC_O,         KC_QUOTE,
        KC_LSFT,  KC_Z, KC_X,    KC_C,    KC_D,    KC_V,             KC_MUTE,  KC_NO,   KC_K,               KC_H,    KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,
                        KC_LCTL, KC_LGUI, KC_LALT, LT(_EXT, KC_DEL), KC_SPC,   KC_RSFT, LT(_SYMB, KC_BSPC), KC_RALT, KC_RGUI, KC_RCTL
    ),

    /*
        Symbols/Numpad Layer
        ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
        │F1 │F2 │F3 │F4 │F5 │F6 │               │F7 │F8 │F9 │F10│F11│F12│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │Tab│ ! │ @ │ # │ $ │ % │               │ * │ 7 │ 8 │ 9 │ + │Ent│
        ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
        │ \ │ _ │ [ │ { │ ( │ ^ │               │ = │ 4 │ 5 │ 6 │ 0 │NUM│
        ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
        │___│ | │ ] │ } │ ) │ & │___│       │___│ / │ 1 │ 2 │ 3 │ - │___│
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │___│___│___│___│___│       │___│___│___│___│___│
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */
    [_SYMB] = LAYOUT_split4x6_r1(
        KC_F1,    KC_F2,    KC_F3,   KC_F4,      KC_F5,    KC_F6,                           KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
        KC_TAB,   KC_EXLM,  KC_AT,   KC_HASH,    KC_DLR,   KC_PERC,                         KC_PAST,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_ENTER,
        KC_BSLS,  KC_UNDS,  KC_LBRC, KC_LCBR,    KC_LPRN,  KC_CIRC,                         KC_PEQL,  KC_P4,    KC_P5,    KC_P6,    KC_P0,    KC_NUM,
        _______,  KC_PIPE,  KC_RBRC, KC_RCBR,    KC_RPRN,  KC_AMPR,     _______,  _______,  KC_PSLS,  KC_P1,    KC_P2,    KC_P3,    KC_PMNS,  _______,
                            _______, _______,    _______,  MO(_ADJUST), _______,  _______,  _______,  _______,  _______,  _______
    ),

    /*
        Extension/Function Layer
        ┌────┬────┬────┬────┬────┬────┐               ┌────┬────┬────┬────┬────┬────┐
        │ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │               │ F7 │ F8 │ F9 │ F10│ F11│ F12│
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │ ⇤  │PGUP│End │ ↑  │Home│    │               │BRIU│ F7 │ F8 │ F9 │ F10│____│
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │Cps │PGDN│ ←  │ ↓  │ →  │    │               │BRID│ F4 │ F5 │ F6 │ F11│____│
        ├────┼────┼────┼────┼────┼────┼────┐     ┌────┼────┼────┼────┼────┼────┼────┤
        │____│    │    │    │    │    │____│     │ ▶⏸ │    │ F1 │ F2 │ F3 │ F12│____│
        └────┴────┴────┴────┴────┴────┴────┘     └────┴────┴────┴────┴────┴────┴────┘
                      ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                      │___│___│___│___│___│       │___│___│___│___│___│
                      └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */
    [_EXT] = LAYOUT_split4x6_r1(
        KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,       KC_F6,                       KC_F7,       KC_F8,    KC_F9,   KC_F10,  KC_F11,   KC_F12,
        S(KC_TAB), KC_PGUP,    KC_END,     KC_UP,      KC_HOME,     _______,                     KC_BRIU,     KC_F7,    KC_F8,   KC_F9,   KC_F10,   _______,
        KC_CAPS,   KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RIGHT,    _______,                     KC_BRID,     KC_F4,    KC_F5,   KC_F6,   KC_F11,   _______,
        _______,   _______,    _______,    _______,    _______,     _______, _______,  KC_MPLY,  _______,     KC_F1,    KC_F2,   KC_F3,   KC_F12,   _______,
                               _______,    _______,    _______,     _______, _______,  _______,  MO(_ADJUST), _______,  _______, _______
    ),

    /*
        Adjust Layer, Keyboard Settings
        ┌────┬────┬────┬────┬────┬────┐               ┌────┬────┬────┬────┬────┬────┐
        │    │    │    │    │    │    │               │    │    │    │    │    │    │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │SpdU│HueU│SatU│ValU│Rnxt│    │               │    │EClr│Rbt │DBUG│BOOT│    │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │SpdD│HueD│SatD│ValD│Rprv│RTgl│               │    │QWRT│COLE│    │    │    │
        ├────┼────┼────┼────┼────┼────┼────┐     ┌────┼────┼────┼────┼────┼────┼────┤
        │    │    │    │    │    │    │    │     │    │    │    │    │    │    │    │
        └────┴────┴────┴────┴────┴────┴────┘     └────┴────┴────┴────┴────┴────┴────┘
                       ┌───┬───┬───┬───┬───┐     ┌───┬───┬───┬───┬───┐
                       │___│___│___│___│___│     │___│___│___│___│___│
                       └───┴───┴───┴───┴───┘     └───┴───┴───┴───┴───┘
    */
    [_ADJUST] = LAYOUT_split4x6_r1(
        KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                       KC_NO,       KC_NO,         KC_NO,           KC_NO,   KC_NO,    KC_NO,
        RM_SPDU,   RM_HUEU,    RM_SATU,    RM_VALU,    RM_NEXT,    KC_NO,                       KC_NO,       EE_CLR,        QK_RBT,          DB_TOGG, QK_BOOT,  KC_NO,
        RM_SPDD,   RM_HUED,    RM_SATD,    RM_VALD,    RM_PREV,    RM_TOGG,                     KC_NO,       DF(_QWERTY),   DF(_COLEMAK_DH), KC_NO,   KC_NO,    KC_NO,
        KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,   KC_NO,    KC_NO,    KC_NO,       KC_NO,         KC_NO,           KC_NO,   KC_NO,    KC_NO,
                               _______,    _______,    _______,    _______, _______,  _______,  _______,     _______,       _______,         _______
    )
    // clang-format on
};

/*
    --- Rotary Encoder Mappings ---

    Encoder mappings go from leftmost encoder to rightmost encoder on the physical board.
    index 0 is the the optional leftmost encoder on the left half, index 1 is the right encoder
    on the left half (by the thumb keys), index 2 is the left encoder on the right half (by the
    thumb keys), and index 3 is the optional rightmost encoder on the right half.

    If you are only using the 2 required encoders by the thumb keys, you only need to worry about
    index 1 and index 2.

    Note that the keycode for counter-clockwise rotation (CCW) goes first and then the key for
    clockwise (CW) within ENCODER_CCW_CW.
*/
#ifdef ENCODER_MAP_ENABLE
// clang-format off

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Base layer encoder mappings:
    //                index 0: mouse wheel up (CCW)/down (CW)     index 1: volume down/up           index 2: mouse wheel up/down                index 3: mouse wheel left/right
    [_QWERTY] =     { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
    [_COLEMAK_DH] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },

    // Passes through to base layers
    [_SYMB] =       { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    // On the extension layer, the right side's left encoder by the thumb keys (mouse wheel up/down) is traded for media previous/next
    [_EXT] =        { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    // Passes through
    [_ADJUST] =     { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    // clang-format on
};

#endif
