#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"


enum layers {
DEF,
SYM,
NAV,
NUM,
FKEYS
};

enum keycodes {
// Custom oneshot mod implementation with no timers.
OS_SHFT = SAFE_RANGE,
OS_CTRL,
OS_ALT,
OS_CMD,

AE,      // æ
OE,      // ø
AA,      // å

SW_WIN,  // Switch to next window         (cmd-tab)
SW_LANG, // Switch to next input language (ctl-spc)
};

enum {
    TD_NUMPAD_FKEYS = 0,
    TD_NAV_NUM,
    TD_SYM_FKEYS,
};

enum combo_events {
    ESC_COMBO,
    // TAB_COMBO,
    // DEL_COMBO,
    // BSPC_COMBO,
    // ENT_COMBO,
};


// Define which keys trigger each combo
const uint16_t PROGMEM esc_combo[]  = {KC_W, KC_F, COMBO_END};
// const uint16_t PROGMEM tab_combo[]  = {KC_R, KC_S, COMBO_END};
// const uint16_t PROGMEM del_combo[]  = {KC_U, KC_Y, COMBO_END};
// const uint16_t PROGMEM bspc_combo[] = {KC_E, KC_I, COMBO_END};
// const uint16_t PROGMEM ent_combo[]  = {KC_COMM, KC_DOT, COMBO_END};

// Keep track of what we did
int td_layer_action = 0;
int td_nav_num_action = 0;
int td_sym_fkeys_action = 0;


void dance_nav_num_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            layer_on(NAV);       // single hold → NAV
            td_nav_num_action = 1;
        } else {
            td_nav_num_action = 0; // single tap placeholder
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            layer_on(NUM);       // double tap hold → NUM
            td_nav_num_action = 2;
        } else {
            td_nav_num_action = 0; // double tap placeholder
        }
    }
}

void dance_nav_num_reset(tap_dance_state_t *state, void *user_data) {
    if (td_nav_num_action == 1) {
        layer_off(NAV);
    } else if (td_nav_num_action == 2) {
        layer_off(NUM);
    }
    td_nav_num_action = 0;
}

void dance_sym_fkeys_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            layer_on(SYM);       // single hold → SYM
            td_sym_fkeys_action = 1;
        } else {
            td_sym_fkeys_action = 0; // single tap placeholder
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            layer_on(FKEYS);     // double tap hold → FKEYS
            td_sym_fkeys_action = 2;
        } else {
            td_sym_fkeys_action = 0; // double tap placeholder
        }
    }
}

void dance_sym_fkeys_reset(tap_dance_state_t *state, void *user_data) {
    if (td_sym_fkeys_action == 1) {
        layer_off(SYM);
    } else if (td_sym_fkeys_action == 2) {
        layer_off(FKEYS);
    }
    td_sym_fkeys_action = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_NAV_NUM]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_nav_num_finished, dance_nav_num_reset),
    [TD_SYM_FKEYS]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sym_fkeys_finished, dance_sym_fkeys_reset),
};

combo_t key_combos[] = {
    [ESC_COMBO]  = COMBO(esc_combo,  KC_ESC),
    // [TAB_COMBO]  = COMBO(tab_combo,  KC_TAB),
    // [DEL_COMBO]  = COMBO(del_combo,  KC_DEL),
    // [BSPC_COMBO] = COMBO(bspc_combo, KC_BSPC),
    // [ENT_COMBO]  = COMBO(ent_combo,  KC_ENT),
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT_callum(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN,
                                KC_SPC, TD(TD_NAV_NUM), TD(TD_SYM_FKEYS), OS_SHFT
),


[SYM] = LAYOUT_callum(
    KC_EXLM,  KC_AT, KC_HASH, KC_DLR, KC_PERC,   KC_ASTR,  KC_LPRN, KC_RPRN, KC_MINS,  KC_EQL,
    OS_SHFT, OS_CTRL, OS_ALT, OS_CMD, KC_GRV,    KC_AMPR,  KC_LBRC, KC_RBRC, KC_UNDS,  KC_PLUS,
    KC_ESC, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_CIRC,  KC_LCBR, KC_RCBR, KC_BSLS,  KC_SLSH,
                                _______, _______, _______, _______
),

[NAV] = LAYOUT_callum(
    KC_TAB,  SW_WIN,  TAB_L,   TAB_R,   KC_VOLU, QK_BOOT,   HOME,    KC_UP,   END,     KC_DEL,
    OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
    UNDO, REDO, BACK,    FWD,     KC_MPLY, XXXXXXX, KC_PGDN, KC_PGUP, SW_LANG, KC_ENT,
                                _______, _______, _______, _______
),

[NUM] = LAYOUT_callum(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX,
    OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  XXXXXXX,  XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,
                                _______, _______, _______, KC_0
),

[FKEYS] = LAYOUT_callum(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  XXXXXXX,  XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,
                                _______, _______, _______, _______
),

};

bool is_oneshot_cancel_key(uint16_t keycode) {
switch (keycode) {
case TD(TD_SYM_FKEYS):
case TD(TD_NAV_NUM):
    return true;
default:
    return false;
}
}

bool is_oneshot_ignored_key(uint16_t keycode) {
switch (keycode) {
case TD(TD_SYM_FKEYS):
case TD(TD_NAV_NUM):
case OS_SHFT:
case OS_CTRL:
case OS_ALT:
case OS_CMD:
    return true;
default:
    return false;
}
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case AE:
                tap_code16(A(KC_QUOT)); // Alt+'
                return false;
            case OE:
                tap_code16(A(KC_O));    // Alt+O
                return false;
            case AA:
                tap_code16(A(KC_A));    // Alt+A
                return false;
        }
    }

    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

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
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}
