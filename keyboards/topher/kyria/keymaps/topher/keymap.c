#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LOW,
    _LOWER,
    _LOWEST,
};
enum tophactyl_keycodes {
    QW = SAFE_RANGE,
    XCOPY, XPASTE,
    TabLeft, TabRight,
    STabLeft, STabRight,
    TTY1,
    TTY2,
    TTY3,
};

enum tap_dance_keycodes {
    Q_TAB,
    Z_CAP,
    M_QUOT,
    H_LEFT,
    J_DOWN,
    K_UP,
    L_RGHT,
    P_PSCR,
    _1_WS1,
    _2_WS2,
    _3_WS3,
    EXLM_MWS1,
    AT_MWS3,
    HASH_MWS3,
    BTN1_BTN2,
};

#define LOW      MO(_LOW)
#define LOWER      MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
    XXXXXXX, TD(Q_TAB), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, TD(P_PSCR), XXXXXXX,
    XXXXXXX, LGUI_T(KC_A), KC_S, KC_D, RCTL_T(KC_F), KC_G, TD(H_LEFT), TD(J_DOWN), TD(K_UP),TD(L_RGHT), KC_BSPC, XXXXXXX,
    XXXXXXX, RALT_T(KC_Z), KC_X, KC_C, KC_V, LSFT_T(KC_B), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, XXXXXXX, 
    XXXXXXX,  XXXXXXX,  LOWER, LSFT_T(KC_ENT), _______, KC_INS, LCTL_T(KC_SPC), LOW, XXXXXXX,  XXXXXXX 
    // QK_BOOT, QK_BOOT, QK_BOOT, QK_BOOT, QK_BOOT, QK_BOOT
    ),

    [_LOW] = LAYOUT(
    XXXXXXX, TD(_1_WS1), TD(_2_WS2), TD(_3_WS3), KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, XXXXXXX, 
    XXXXXXX, QW, _______, KC_LCBR, KC_RCBR, KC_COLN, KC_GRV, KC_MINS, KC_PLUS, KC_PIPE, KC_DEL, XXXXXXX, 
    XXXXXXX, _______, _______, XCOPY, XPASTE, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_QUOT, _______, _______, KC_BSLS, XXXXXXX, 
    XXXXXXX,  XXXXXXX,  _______, _______, _______, _______, _______, _______, XXXXXXX,  XXXXXXX  
    ),

    [_LOWER] = LAYOUT(
    XXXXXXX, TD(EXLM_MWS1), TD(AT_MWS3), TD(HASH_MWS3), KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX, 
    XXXXXXX, KC_ESC, _______, KC_LBRC, KC_RBRC, KC_SCLN, _______, KC_UNDS, KC_EQL, _______, _______, XXXXXXX, 
    XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TabLeft, KC_PGDN, KC_PGUP, TabRight, _______, XXXXXXX, 
    XXXXXXX,  XXXXXXX,  _______, _______, _______, _______, _______, _______, XXXXXXX,  XXXXXXX 
    ),

    [_LOWEST] = LAYOUT(
    XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, XXXXXXX, 
    XXXXXXX, KC_F11, KC_F12, TTY1, TTY2, TTY3, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, XXXXXXX, 
    XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, STabLeft, _______, _______, STabRight, _______, XXXXXXX, 
    XXXXXXX,  XXXXXXX,  _______, QK_RBT, QK_BOOT, _______, _______, _______, XXXXXXX,  XXXXXXX 
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOW, _LOWER, _LOWEST);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(H_LEFT): return 160;
        case TD(J_DOWN): return 150;
        case TD(K_UP): return 160;
        case TD(L_RGHT): return 115;
        case TD(M_QUOT): return 140;
        case TD(Z_CAP): return 190;
        case TD(Q_TAB): return 210;
        case TD(P_PSCR): return 130;
        case TD(_1_WS1): return 160;
        case TD(_2_WS2): return 160;
        case TD(_3_WS3): return 160;
        case LGUI_T(KC_A): return 300;  
        case LCTL_T(_______): return 210;
        case LSFT_T(KC_ENT): return 150;
        case LALT(KC_SPC): return 190;
        default:
            return TAPPING_TERM;
    }
}

void dance_1_ws1_finished(tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code(KC_1);
    }
    else {
        register_code(KC_LGUI);
        tap_code(KC_1);
        unregister_code(KC_LGUI);
    }
}
void dance_2_ws2_finished(tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code(KC_2);
    }
    else {
        register_code(KC_LGUI);
        tap_code(KC_2);
        unregister_code(KC_LGUI);
    }
}
void dance_3_ws3_finished(tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code(KC_3);
    }
    else {
        register_code(KC_LGUI);
        tap_code(KC_3);
        unregister_code(KC_LGUI);
    }
}
void dance_exlm_mws1_finished(tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code16(KC_EXLM);
    }
    else {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}
void dance_at_mws2_finished(tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code16(KC_AT);
    }
    else {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_2);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}
void dance_hash_mws3_finished(tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code16(KC_HASH);
    }
    else {
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        tap_code(KC_3);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),
    [Z_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_CAPS),
    [H_LEFT] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_LEFT),
    [J_DOWN] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_DOWN),
    [K_UP] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_UP),
    [L_RGHT] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_RGHT),
    [M_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_QUOT),
    [P_PSCR] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_PSCR),
    [BTN1_BTN2] = ACTION_TAP_DANCE_DOUBLE(KC_BTN1, KC_BTN2),
    [_1_WS1] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_1_ws1_finished, NULL),
    [_2_WS2] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_2_ws2_finished, NULL),
    [_3_WS3] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_3_ws3_finished, NULL),
    [EXLM_MWS1] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_exlm_mws1_finished, NULL),
    [AT_MWS3] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_at_mws2_finished, NULL),
    [HASH_MWS3] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_hash_mws3_finished, NULL)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {         
        case QW:
        if (record->event.pressed)
        {
            register_code(KC_LGUI);
            register_code(KC_LSFT);
            tap_code(KC_Q);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
        }
        break;      
        case XCOPY:
        if (record->event.pressed)
        {
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
        }
        break;
        case XPASTE:
        if (record->event.pressed)
        {
            register_code(KC_LSFT);
            tap_code(KC_INS);
            unregister_code(KC_LSFT);
        }
        break;
        case TabLeft:
        if (record->event.pressed)
        {
            register_code(KC_LCTL);
            tap_code(KC_PGUP);
            unregister_code(KC_LCTL);
        }
        break;
        case TabRight:
        if (record->event.pressed)
        {
            register_code(KC_LCTL);
            tap_code(KC_PGDN);
            unregister_code(KC_LCTL);
        }
        break;
        case STabLeft:
        if (record->event.pressed)
        {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            tap_code(KC_PGUP);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        break;
        case STabRight:
        if (record->event.pressed)
        {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            tap_code(KC_PGDN);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        break;
        case TTY1:
        if (record->event.pressed)
        {
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_F1);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
        break;
        case TTY2:
        if (record->event.pressed)
        {
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_F2);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
        break;
        case TTY3:
        if (record->event.pressed)
        {
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_F3);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTL);
        }
        break;
        }
  return true;
  }