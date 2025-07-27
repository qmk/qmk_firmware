#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

enum dasbob_layers {
  DEF,
  SYM,
  NUM,
  NAV,
  FUN
};

enum {
    _TD_NAV
};

#define TD_NAV TD(_TD_NAV)

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_SYS,
    OS_SYM,
    OS_CNCL,

    SW_WIN,
    SW_LANG,
    SW_TAB,  // TODO

    CM_UNDO,
    CM_CUT,
    CM_COPY,
    CM_PSTE,
    CM_SELA,
    CM_SAVE,
    CM_FIND,
    CM_NEW,
    CM_T,
    CM_W,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┐                   ┌───┐
      *           │DEL├───┐           ┌───┤ESC│
      *           └───┤SPC├───┐   ┌───┤BSP├───┘
      *               └───│LOW│   │RSE├───┘
      *                   └───┘   └───┘
      */


    [DEF] = LAYOUT_split_3x5_3(
        KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
        KC_A,    KC_O,    KC_E,    KC_U,    KC_I,        KC_D,    KC_H,    KC_T,    KC_N,    KC_S,
        KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,        KC_B,    KC_B,    KC_W,    KC_V,    KC_Z,
                          OS_CTRL, OS_SHFT, OS_SYM,      TO(NAV), KC_SPC,  QK_AREP
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_PERC, KC_TILD, KC_DLR,  KC_QUES, KC_NO,       KC_NO,   KC_SLSH, KC_MINS, KC_UNDS, KC_EXLM,
        KC_AMPR, KC_LBRC, KC_LCBR, KC_LPRN, KC_RCBR,     KC_EQL,  KC_ASTR, KC_RPRN, KC_PLUS, KC_RBRC,
        KC_GRV,  KC_HASH, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_AT,   KC_CIRC, KC_BSLS, KC_PIPE,
                          _______, _______, _______,     TO(DEF), _______, _______
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_PSCR, XXXXXXX, KC_APP,  KC_CALC, KC_LNUM,     KC_SLSH, KC_1,    KC_2,    KC_3,    KC_MINS,
        CM_SELA, TO(FUN), XXXXXXX, XXXXXXX, CM_FIND,     KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS,
        CM_UNDO, CM_CUT,  CM_COPY, CM_PSTE, XXXXXXX,     KC_DOT,  KC_7,    KC_8,    KC_9,    KC_ENT,
                          _______, _______, _______,     _______, KC_0,    TO(FUN)
    ),

    [NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX,
        CM_SELA, TO(NUM), SW_TAB,  SW_WIN,  XXXXXXX,     KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        CM_UNDO, CM_CUT,  CM_COPY, CM_PSTE, XXXXXXX,     XXXXXXX, KC_HOME, KC_END,  XXXXXXX, KC_INS,
                          _______, _______, TO(DEF),     _______, _______, _______
    ),

    [FUN] = LAYOUT_split_3x5_3( // TODO AU_VOL
        AU_TOGG, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10,
        CK_TOGG, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,     XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,
        XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12,
                          _______, _______, _______,     _______, _______, _______
    ),

};

const uint16_t PROGMEM cmb_j_k[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cmb_q_j[] = {KC_Q, KC_J, COMBO_END};
const uint16_t PROGMEM cmb_k_x[] = {KC_K, KC_X, COMBO_END};
const uint16_t PROGMEM cmb_g_c[] = {KC_G, KC_C, COMBO_END};
const uint16_t PROGMEM cmb_comma_dot[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM cmb_m_w[] = {KC_M, KC_W, COMBO_END};
const uint16_t PROGMEM cmb_w_v[] = {KC_W, KC_V, COMBO_END};
combo_t key_combos[] = {
    COMBO(cmb_j_k, KC_ENT),
    COMBO(cmb_q_j, KC_BSPC),
    COMBO(cmb_k_x, OS_CMD),
    COMBO(cmb_g_c, KC_MINS),
    COMBO(cmb_comma_dot, KC_ESC),
    COMBO(cmb_m_w, KC_TAB),
    COMBO(cmb_w_v, LALT(KC_TAB)),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CNCL:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case TD_NAV:
    case TO(DEF):
    case TO(SYM):
    case TO(NAV):
    case TO(NUM):
    case TO(FUN):
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
    case OS_SYS:
    case OS_SYM:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
oneshot_state os_sys_state = os_up_unqueued;
oneshot_state os_sym_state = os_up_unqueued;

int with_ctrl(int keycode) {
    return C(keycode);
}
int with_cmd(int keycode) {
    return G(keycode);
}
int (*sys_mod)(int) = with_ctrl;
int sys_mod_kc = KC_LCTL;
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            sys_mod = with_cmd;
            sys_mod_kc = KC_LGUI;
            break;
        default:
            break;
    }
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );
    update_swapper(
        &sw_tab_active, KC_LCTL, KC_TAB, SW_TAB,
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
    update_oneshot(
        &os_cmd_state, sys_mod_kc, OS_SYS,
        keycode, record
    );
    update_oneshot_layer(
        &os_sym_state, SYM, OS_SYM,
        keycode, record
    );

    void (*reg_unreg)(uint16_t) = register_code16;
    if (!record->event.pressed) {
        reg_unreg = unregister_code16;
    }
    switch (keycode) {
    case CM_UNDO:
        reg_unreg(sys_mod(KC_Z));
        break;
    case CM_CUT:
        reg_unreg(sys_mod(KC_X));
        break;
    case CM_COPY:
        reg_unreg(sys_mod(KC_C));
        break;
    case CM_PSTE:
        reg_unreg(sys_mod(KC_V));
        break;
    case CM_SELA:
        reg_unreg(sys_mod(KC_A));
        break;
    case CM_SAVE:
        reg_unreg(sys_mod(KC_S));
        break;
    case CM_FIND:
        reg_unreg(sys_mod(KC_F));
        break;
    case CM_NEW:
        reg_unreg(sys_mod(KC_N));
        break;
    case CM_T:
        reg_unreg(sys_mod(KC_T));
        break;
    case CM_W:
        reg_unreg(sys_mod(KC_W));
        break;
    }

    return true;
}

void td_nav_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_on(NAV);
        return;
    }
    if (state->count == 3) {
        sw_win_active = false;
        sw_lang_active = false;
        os_shft_state = os_up_unqueued;
        os_ctrl_state = os_up_unqueued;
        os_alt_state = os_up_unqueued;
        os_cmd_state = os_up_unqueued;
        os_sys_state = os_up_unqueued;
        os_sym_state = os_up_unqueued;
        reset_tap_dance(state);
        clear_keyboard();
    }
    layer_clear();
}

tap_dance_action_t tap_dance_actions[] = {
    [_TD_NAV] = ACTION_TAP_DANCE_FN(td_nav_fn),
};


// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, SYM, NAV, NUM);
// }


