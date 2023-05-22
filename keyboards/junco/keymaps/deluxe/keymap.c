// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layers enum
enum junco_layers { _QWERTY, _COLEMAK_DH, _SYMB, _EXT, _ADJUST };

// Custom keycodes
enum custom_keycodes {
    // Keycode for toggling between macOS and Windows key mappings
    // Actually just an alias to the GUI and Alt swap Magic keycode
    KC_OS = MAGIC_TOGGLE_ALT_GUI,
    // Keycode for swapping the base layer between QWERTY and Colemak-DH
    KC_TOGGLE_BASE = SAFE_RANGE,
    // Keycode for redo action (Ctrl + Y on windows, Ctrl + Shift + Z on macOS)
    KC_REDO,
    // Keycodes for next/previous word
    KC_WNXT,
    KC_WPRV,
    // Keycode for sticking/unsticking the adjust layer
    KC_ADJST
};

/* LED indicators */
bool is_caps_lock_enabled(void) { // Caps lock
    return (host_keyboard_led_state().caps_lock);
}
bool is_num_lock_enabled(void) { // Num lock
    return (host_keyboard_led_state().num_lock);
}
bool is_adjust_layer_sticky(layer_state_t state) { // Adjust layer sticky
    // Checks if the state is equal to just the adjust layer being active.
    // Doing it this way can leverage SPLIT_LAYER_STATE_ENABLE
    return (state == (1UL << _ADJUST)) ? true : false;
}
// Indicator color based on the RGB Matrix mode
RGB indicator_color(void) {
    RGB rgb;
    // Normally the indicator color is white to stand out in the RGB rainbow.
    // When using the custom RGB mode that already is white, the indicator color
    // is green to stand out.
    if (rgb_matrix_config.mode == RGB_MATRIX_CUSTOM_WHITE_UNDERGLOW_CYCLE) {
        // Green
        rgb.r = 0;
        rgb.g = 255;
        rgb.b = 0;
    } else {
        // White
        rgb.r = 255;
        rgb.g = 255;
        rgb.b = 255;
    }
    return rgb;
}

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
        │Sft│ Z │ X │ C │ V │ B │Mut│       │▶⏸ │ N │ M │ , │ . │ / │Sft│
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
        KC_LSFT,  KC_Z, KC_X,    KC_C,    KC_V,    KC_B,             KC_MUTE,  KC_MPLY, KC_N,               KC_M,    KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,
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
        │Sft│ Z │ X │ C │ D │ V │Mut│       │▶⏸ │ K │ H │ , │ . │ / │Sft│
        └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                │Ctr│Win│Alt│Del│Spc│       │Sft│Bsp│Alt│Win│Ctr│
                └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
                For macOS - GUI/Win (cmd) and Alt (opt) swapped
    */
    [_COLEMAK_DH] = LAYOUT_split4x6_r1(
        KC_GRAVE, KC_1, KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,               KC_7,    KC_8,    KC_9,   KC_0,         KC_MINUS,
        KC_TAB,   KC_Q, KC_W,    KC_F,    KC_P,    KC_B,                                KC_J,               KC_L,    KC_U,    KC_Y,   KC_SEMICOLON, KC_ENTER,
        KC_ESC,   KC_A, KC_R,    KC_S,    KC_T,    KC_G,                                KC_M,               KC_N,    KC_E,    KC_I,   KC_O,         KC_QUOTE,
        KC_LSFT,  KC_Z, KC_X,    KC_C,    KC_D,    KC_V,             KC_MUTE,  KC_MPLY, KC_K,               KC_H,    KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,
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
        KC_F1,    KC_F2,    KC_F3,   KC_F4,      KC_F5,    KC_F6,                       KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
        KC_TAB,   KC_EXLM,  KC_AT,   KC_HASH,    KC_DLR,   KC_PERC,                     KC_PAST,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_ENTER,
        KC_BSLS,  KC_UNDS,  KC_LBRC, KC_LCBR,    KC_LPRN,  KC_CIRC,                     KC_PEQL,  KC_P4,    KC_P5,    KC_P6,    KC_P0,    KC_NUM,
        _______,  KC_PIPE,  KC_RBRC, KC_RCBR,    KC_RPRN,  KC_AMPR, _______,  _______,  KC_PSLS,  KC_P1,    KC_P2,    KC_P3,    KC_PMNS,  _______,
                            _______, _______,    _______,  _______, _______,  _______,  _______,  _______,  _______,  _______
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
        │____│    │    │    │    │    │____│     │____│    │ F1 │ F2 │ F3 │ F12│____│
        └────┴────┴────┴────┴────┴────┴────┘     └────┴────┴────┴────┴────┴────┴────┘
                      ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
                      │___│___│___│___│___│       │___│___│___│___│___│
                      └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
    */
    [_EXT] = LAYOUT_split4x6_r1(
        KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,       KC_F6,                       KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,   KC_F12,
        S(KC_TAB), KC_PGUP,    KC_END,     KC_UP,      KC_HOME,     _______,                     KC_BRIU, KC_F7,    KC_F8,   KC_F9,   KC_F10,   _______,
        KC_CAPS,   KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RIGHT,    _______,                     KC_BRID, KC_F4,    KC_F5,   KC_F6,   KC_F11,   _______,
        _______,   _______,    _______,    _______,    _______,     _______, _______,  _______,  _______, KC_F1,    KC_F2,   KC_F3,   KC_F12,   _______,
                               _______,    _______,    _______,     _______, _______,  _______,  _______, _______,  _______, _______
    ),

    /*
        Adjust Layer, Keyboard Settings
        ┌────┬────┬────┬────┬────┬────┐               ┌────┬────┬────┬────┬────┬────┐
        │    │    │    │    │    │    │               │    │    │    │    │    │    │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │SpdU│HueU│SatU│ValU│Rnxt│Stck│               │    │EClr│Rbt │DBUG│BOOT│    │
        ├────┼────┼────┼────┼────┼────┤               ├────┼────┼────┼────┼────┼────┤
        │SpdD│HueD│SatD│ValD│Rprv│RTgl│               │    │LOUT│ OS │    │    │    │
        ├────┼────┼────┼────┼────┼────┼────┐     ┌────┼────┼────┼────┼────┼────┼────┤
        │    │    │    │    │    │    │RTgl│     │    │    │    │    │    │    │    │
        └────┴────┴────┴────┴────┴────┴────┘     └────┴────┴────┴────┴────┴────┴────┘
                       ┌───┬───┬───┬───┬───┐     ┌───┬───┬───┬───┬───┐
                       │___│___│___│___│___│     │___│___│___│___│___│
                       └───┴───┴───┴───┴───┘     └───┴───┴───┴───┴───┘
    */
    [_ADJUST] = LAYOUT_split4x6_r1(
        KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                       KC_NO,       KC_NO,          KC_NO,   KC_NO,      KC_NO,    KC_NO,
        RGB_SPI,   RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_MOD,    KC_ADJST,                    KC_NO,       EE_CLR,         QK_RBT,  DB_TOGG,    QK_BOOT,  KC_NO,
        RGB_SPD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_RMOD,   RGB_TOG,                     KC_NO,       KC_TOGGLE_BASE, KC_OS,   KC_NO,      KC_NO, KC_NO,
        KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,   RGB_TOG,  KC_NO,    KC_NO,       KC_NO,          KC_NO,   KC_NO,      KC_NO,    KC_NO,
                               _______,    _______,    _______,    _______, _______,  _______,  _______,     _______,        _______, _______
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

    Note that the key to be sent for counter-clockwise rotation (CCW) goes first and then the key for
    clockwise (CW) within ENCODER_CCW_CW.
*/
#ifdef ENCODER_MAP_ENABLE
// clang-format off

// Base layer encoder mappings:
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    // Base layers
    //                index 0: mouse wheel up (CCW)/down (CW)     index 1: volume up/down           index 2: media prev/next          index 3: mouse wheel left/right
    [_QWERTY] =     { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
    [_COLEMAK_DH] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },

    // Passes through to base layer
    [_SYMB] =       { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    //                                                                                    undo/redo                         previous word/next word
    [_EXT] =        { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_UNDO, KC_REDO), ENCODER_CCW_CW(KC_WPRV, KC_WNXT) },
    //                RGB Speed down/up                 RGB previous mode/next mode        RGB brightness down/up
    [_ADJUST] =     { ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    // clang-format on
};

#endif

// Called whenever a layer is changed
layer_state_t layer_state_set_user(layer_state_t state) {
    // Make sure the adjust layer isn't sticky
    if (is_adjust_layer_sticky(state)) return state;

    // When both the symbol and extension layer keys are held, the Adjust layer is active.
    return update_tri_layer_state(state, _SYMB, _EXT, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Toggle base layer
        case KC_TOGGLE_BASE:
            if (record->event.pressed) {
                // Toggle swapping base layers between Colemak-DH and QWERTY.
                // When base layer is QWERTY, swap to Colemak-DH and vice-versa
                if (get_highest_layer(default_layer_state) == _QWERTY) {
                    default_layer_set(1UL << _COLEMAK_DH);
                } else {
                    default_layer_set(1UL << _QWERTY);
                }
            }
            return false;

        // Override undo in favor of the more modern undo action
        case KC_UNDO:
            if (record->event.pressed) {
                // Use the correct modifier for macOS or Windows
                uint16_t mod = keymap_config.swap_lalt_lgui ? KC_LGUI : KC_LCTL;
                // Send Ctrl+Z/Cmd+Z
                register_code(mod);
                tap_code_delay(KC_Z, 10);
                unregister_code(mod);
            }
            return false;

        //  Redo action
        case KC_REDO:
            if (record->event.pressed) {
                // Whether or not macOS mapping is enabled
                if (keymap_config.swap_lalt_lgui) {
                    // macOS - Send Cmd+Shift+Z
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code_delay(KC_Z, 10);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_LGUI);
                } else {
                    // Windows - Send Ctrl+Y
                    register_code(KC_LCTL);
                    tap_code_delay(KC_Y, 10);
                    unregister_code(KC_LCTL);
                }
            }
            return false;

        // Next word
        case KC_WNXT:
            if (record->event.pressed) {
                // Use the correct modifier for macOS or Windows
                uint16_t mod = keymap_config.swap_lalt_lgui ? KC_LALT : KC_LCTL;
                // Send Ctrl+Right/Option+Right
                register_code(mod);
                tap_code_delay(KC_RGHT, 10);
                unregister_code(mod);
            }
            return false;

        // Previous word
        case KC_WPRV:
            if (record->event.pressed) {
                // Use the correct modifier for macOS or Windows
                uint16_t mod = keymap_config.swap_lalt_lgui ? KC_LALT : KC_LCTL;
                // Send Ctrl+Left/Option+Left
                register_code(mod);
                tap_code_delay(KC_LEFT, 10);
                unregister_code(mod);
            }
            return false;

        // Stick / Unstick the adjust layer
        case KC_ADJST:
            if (record->event.pressed) {
                // If currently not sticky, we want only the adjust layer to be active to make it stick.
                // Otherwise we want the default layer, un-stick.
                is_adjust_layer_sticky(layer_state) ? layer_state_set(default_layer_state) : layer_move(_ADJUST);
                dprintf("Adjust layer is now %s\n", is_adjust_layer_sticky(layer_state) ? "stuck" : "un-stuck");
            }
            return false;
        default:
            return true;
    }
}

/* Indicators (Caps Lock / Num Lock / Adjust Layer Sticky) */
bool rgb_matrix_indicators_user(void) {
    layer_state_t curr_layer_state = layer_state;
    layer_state_t layer            = get_highest_layer(curr_layer_state);
    RGB           rgb              = indicator_color();

    /* Only show the indicator on their respective layers */
    // Caps Lock is only on the extension layer
    if (is_caps_lock_enabled() && layer == _EXT) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, rgb.r, rgb.g, rgb.b);
    }

    // Num Lock is only on the symbol layer
    if (is_num_lock_enabled() && layer == _SYMB) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, rgb.r, rgb.g, rgb.b);
    }

    // If the adjust layer is stuck/sticky, light it up. Don't need to care about
    // checking the layer since it can only be active on the adjust layer anyway
    if (is_adjust_layer_sticky(curr_layer_state)) rgb_matrix_set_color(ADJST_LED_INDEX, rgb.r, rgb.g, rgb.b);

    return false;
}
