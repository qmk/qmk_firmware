// Copyright 2022 Namit Nathwani (@namsnath)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
// #include "../../../../users/callum/oneshot.h"
#include "../../../../users/callum/oneshot.c"
// #include "../../../../users/callum/swapper.h"
#include "../../../../users/callum/swapper.c"


// Defines names for use in layer keycodes and the keymap
enum layers {
    // Alphas
    L_BASE,
    // Navigation, Tab, Del, Enter
    L_NAV,
    // Symbols
    L_SYM,
    // Numbers, F-Keys
    L_NUM,
};

enum keycodes {
    // Callum oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
    // OS_CAPS, // for use as Globe on iPadOS, via remapping in Settings.app

    APP_SWITCH_FRWD, // cmd-tab but holds cmd between invocations
};

#define LR_BASE MO(L_BASE)
#define LR_NAV  MO(L_NAV)
#define LR_SYM  MO(L_SYM)
#define LR_NUM  MO(L_NUM)

#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**
     *  ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓                     ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓
     *  ┃    Q     │    W     │    E     │    R     │    T     ┃                     ┃    Y     │    U     │    I     │    O     │    P     ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────┨                     ┠──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃    A     │    S     │    D     │    F     │    G     ┃                     ┃    H     │    J     │    K     │    L     │   '  "   ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────╊━━━━━━━━━━┳━━━━━━━━━━╉──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃    Z     │    X     │    C     │    V     │    B     ┃   Mute   ┃   Play   ┃    N     │    M     │   ,  <   │   .  >   │   ;  :   ┃
     *  ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━╅──────────┼──────────╄━━━━━━━━━━╇━━━━━━━━━━╃──────────┼──────────╆━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     *                                   ┃   SYMB   │ OS Shift │   Bksp   │  Space   │ OS Ctrl  │   NAV    ┃
     *                                   ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     */
    [L_BASE] = LAYOUT_split_3x5_3_encoder(
        KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                            KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
        KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                            KC_H,      KC_J,      KC_K,      KC_L,      KC_QUOT,
        KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_MUTE,   KC_MPLY,   KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SCLN,
                                         LR_SYM,    OS_SHFT,   KC_BSPC,   KC_SPC,    OS_CTRL,   LR_NAV
    ),

    /**
     *  ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓                     ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓
     *  ┃   Tab    │          │          │          │          ┃                     ┃          │          │   Up     │          │  Delete  ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────┨                     ┠──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃ OS Shift │ OS Ctrl  │  OS Alt  │  OS GUI  │   Esc    ┃                     ┃          │   Left   │   Down   │   Right  │   Enter  ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────╊━━━━━━━━━━┳━━━━━━━━━━╉──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃   Undo   │   Cut    │   Copy   │  Paste   │   Redo   ┃    ▼     ┃    ▼     ┃          │          │          │          │          ┃
     *  ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━╅──────────┼──────────╄━━━━━━━━━━╇━━━━━━━━━━╃──────────┼──────────╆━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     *                                   ┃    ▼     │          │    ▼     │    ▼     │          │    ▼     ┃
     *                                   ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     */
    [L_NAV] = LAYOUT_split_3x5_3_encoder(
        KC_TAB,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                         XXXXXXX,   XXXXXXX,   KC_UP,     XXXXXXX,   KC_DEL,
        OS_SHFT,   OS_CTRL,   OS_ALT,    OS_GUI,    KC_ESC,                          XXXXXXX,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_ENT,
        KC_UNDO,   KC_CUT,    KC_COPY,   KC_PASTE,  KC_REDO,   _______,   _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                                         _______,   XXXXXXX,   _______,   _______,   XXXXXXX,   _______
    ),

    /**
     *  ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓                     ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓
     *  ┃    `     │    [     │    {     │    (     │    \     ┃                     ┃    /     │    )     │    }     │    ]     │          ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────┨                     ┠──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃          │    @     │    $     │    *     │    -     ┃                     ┃    +     │  OS GUI  │  OS Alt  │ OS Ctrl  │ OS Shift ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────╊━━━━━━━━━━┳━━━━━━━━━━╉──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃    ~     │    |     │    !     │    =     │    #     ┃    ▼     ┃    ▼     ┃    _     │    ^     │    %     │    &     │    ?     ┃
     *  ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━╅──────────┼──────────╄━━━━━━━━━━╇━━━━━━━━━━╃──────────┼──────────╆━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     *                                   ┃    ▼     │          │          │          │          │    ▼     ┃
     *                                   ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     */
    [L_SYM] = LAYOUT_split_3x5_3_encoder(
        KC_GRV,    KC_LBRC,   KC_LCBR,   KC_LPRN,   KC_BSLS,                         KC_SLSH,   KC_RPRN,   KC_RCBR,   KC_RBRC,   XXXXXXX,
        XXXXXXX,   KC_AT,     KC_DLR,    KC_ASTR,   KC_MINS,                         KC_PLUS,   OS_GUI,    OS_ALT,    OS_CTRL,   OS_SHFT,
        KC_TILD,   KC_PIPE,   KC_EXLM,   KC_EQL,    KC_HASH,   _______,   _______,   KC_UNDS,   KC_CIRC,   KC_PERC,   KC_AMPR,   KC_QUES,
                                         _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   _______
    ),

    /**
     *  ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓                     ┏━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┯━━━━━━━━━━┓
     *  ┃          │   F7     │   F8     │   F9     │   F12    ┃                     ┃          │   7  &   │   8  *   │   9  (   │          ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────┨                     ┠──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃          │   F4     │   F5     │   F6     │   F11    ┃                     ┃    .     │   4  $   │   5  %   │   6  ^   │          ┃
     *  ┠──────────┼──────────┼──────────┼──────────┼──────────╊━━━━━━━━━━┳━━━━━━━━━━╉──────────┼──────────┼──────────┼──────────┼──────────┨
     *  ┃          │   F1     │   F2     │   F3     │   F10    ┃    ▼     ┃    ▼     ┃   0  )   │   1  !   │   2  @   │   3  #   │          ┃
     *  ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━╅──────────┼──────────╄━━━━━━━━━━╇━━━━━━━━━━╃──────────┼──────────╆━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     *                                   ┃    ▼     │ OS Shift │  OS Alt  │  OS GUI  │ OS Ctrl  │    ▼     ┃
     *                                   ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┛
     */
    [L_NUM] = LAYOUT_split_3x5_3_encoder(
        XXXXXXX,   KC_F7,     KC_F8,     KC_F9,     KC_F12,                          XXXXXXX,   KC_7,      KC_8,      KC_9,      XXXXXXX,
        XXXXXXX,   KC_F4,     KC_F5,     KC_F6,     KC_F11,                          KC_DOT,    KC_4,      KC_5,      KC_6,      XXXXXXX,
        XXXXXXX,   KC_F1,     KC_F2,     KC_F3,     KC_F10,    _______,   _______,   KC_0,      KC_1,      KC_2,      KC_3,      XXXXXXX,
                                         _______,   OS_SHFT,   OS_ALT,    OS_GUI,    OS_CTRL,    _______
    )
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
    return true;
}

// ====================================================
// Callum One-Shot Modifiers
// ====================================================

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LR_SYM:
    case LR_NAV:
    // case LR_NUM:
    //case B_NUM:
    //case SPC_NAV:
    //case KC_ESC:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LR_SYM:
    case LR_NAV:
    // case LR_NUM:
    //case B_NUM:
    //case SPC_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
    // case OS_CAPS:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;
oneshot_state os_caps_state = os_up_unqueued;

bool app_switch_frwd_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // update_swapper(
    //     &app_switch_frwd_active, KC_LGUI, KC_TAB, APP_SWITCH_FRWD,
    //     keycode, record
    // );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );
    // update_oneshot(
    //     &os_caps_state, KC_CAPS, OS_CAPS,
    //     keycode, record
    // );

    return true;
}

// Change layer state with multiple layer keys
layer_state_t layer_state_set_user(layer_state_t state) {
    // Hold NAV and SYM to get NUM
    return update_tri_layer_state(state, L_NAV, L_SYM, L_NUM);
}
