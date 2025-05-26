// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/achordion.h"

enum layers { BASE, SYM, NAV, NUM, MOUSE };

enum custom_keycodes {
    XC_LFT_SPLT = SAFE_RANGE,
    XC_RGT_SPLT,
    DBL_QUOT,
    VIWPYIW,
    DELETE_LINE,
    LEFT_WORD,
    RIGHT_WORD,
    CLOSE_PAIR
};

// Left-hand home row mods
#define HOME_N LCTL_T(KC_N)
#define HOME_R LGUI_T(KC_R)
#define HOME_T LSFT_T(KC_T)
#define HOME_S LALT_T(KC_S)

// Right-hand home row mods
#define HOME_H RALT_T(KC_H)
#define HOME_A RSFT_T(KC_A)
#define HOME_E LGUI_T(KC_E)
#define HOME_I RCTL_T(KC_I)

#define SCRNSHOT LGUI(LCTL(LSFT(KC_4)))
#define BACK G(KC_LEFT)
#define FORWARD G(KC_RIGHT)
#define ARC_SPLIT_CLOSE HYPR(KC_N)
#define CLOSE_WIN G(KC_W)
#define XCODE_SPLIT HYPR(KC_U)
#define ARC_SPLIT HYPR(KC_H)
#define ARC_LFT_SPLT C(S(KC_P))
#define HMRW_SCROLL HYPR(KC_J)
#define HMRW_CLICK HYPR(KC_K)
#define ARC_RGHT_SPLT C(S(KC_E))
#define XC_CONSOLE LSG(KC_Y) 
#define XC_PREVIEW LAG(KC_ENT)
#define ARC_WS_1 C(KC_1)
#define ARC_WS_2 C(KC_2)
#define TAB_L LSG(KC_LBRC)
#define TAB_R LSG(KC_RBRC)
#define XC_SEARCH LSG(KC_O)
#define XC_SHOW LSG(KC_J)
#define XC_SIDEBAR G(KC_0)
#define ZOOM_IN G(KC_PLUS)
#define ZOOM_OUT G(KC_MINS)

#define HYPR_SPC MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI,KC_SPC)

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

static uint16_t last_keycode = KC_NO;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        LT(MOUSE, KC_ESC), KC_B,  KC_L,   KC_D,  KC_C,    KC_V,                    KC_J,    KC_Y,    KC_O,   KC_U,    KC_COMM, KC_TAB,
        OSM(MOD_LGUI), HOME_N, HOME_R, KC_T, HOME_S, KC_G,                         KC_P,    HOME_H,  KC_A,   HOME_E,  HOME_I, KC_ENT,
        OSM(MOD_LSFT), KC_X,   KC_Q, KC_M, KC_W, KC_Z,                             KC_K,    KC_F,    KC_QUOT,KC_SCLN, KC_DOT, KC_SLSH,
                                            TT(NAV), HYPR_SPC,                     KC_BSPC, MO(SYM)
    ),
    [SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        VIWPYIW, KC_TILD, KC_LT,   KC_GT, KC_LCBR,  KC_RCBR,                       KC_DEL,  KC_PSCR, KC_EXLM, KC_HASH, KC_BSLS, _______,
        _______, KC_AT, KC_LPRN, KC_LBRC, KC_RPRN, KC_RBRC,                        KC_CIRC, KC_EQL,  KC_PLUS, KC_MINS, KC_PIPE, _______,
        _______, _______, KC_GRV, KC_AMPR, KC_UNDS, DBL_QUOT,                      KC_ASTR, CLOSE_PAIR, KC_DLR,  KC_PERC, SCRNSHOT, LCA(KC_G),
                                                     _______, _______,    _______, _______
    ),
    [NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        BACK,    FORWARD, XC_LFT_SPLT, KC_UP, XC_RGT_SPLT, KC_HOME,                OSM(MOD_LALT), LEFT_WORD, DELETE_LINE, RIGHT_WORD,  XCODE_SPLIT, ARC_SPLIT,
        ARC_SPLIT_CLOSE,CLOSE_WIN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,              ARC_LFT_SPLT, HMRW_SCROLL, HMRW_CLICK, ARC_RGHT_SPLT, XC_CONSOLE, XC_PREVIEW,
        _______, ZOOM_OUT, ARC_WS_1, ARC_WS_2, TAB_L, TAB_R,                       _______, XC_SIDEBAR, XC_SEARCH, XC_SHOW, ZOOM_IN, _______,
                                                     _______, _______,    _______, _______
    ),
    [NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_F11,                       KC_F12,  _______, _______, _______, _______, _______,
        _______, KC_9,    KC_5,    KC_0,    KC_3,    KC_7,                         KC_6,    KC_2,    KC_1,    KC_4,    KC_8,    _______,
        _______, KC_F9,   KC_F5,   KC_F10,  KC_F3,   KC_F7,                        KC_F6,   KC_F2,   KC_F1,   KC_F4,   KC_F8,    _______,
                                                     _______, _______,    _______, _______
    ),
    [MOUSE] = LAYOUT(
        _______, _______, MS_WHLD, MS_WHLU, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, MS_ACL1, KC_MS_BTN1, KC_MS_BTN1, _______, _______,                _______, _______, KC_MS_UP, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                      _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
                                                     _______, _______,    _______, _______
    ),
};




void housekeeping_task_user(void) {
    achordion_task();
}

void handle_opening_pair(uint16_t keycode) {
    last_keycode = keycode;
    tap_code16(keycode);
}

bool handle_closing_pair(void) {
    switch (last_keycode) {
        case KC_LPRN: tap_code16(KC_RPRN); break;  // (
        case KC_LBRC: tap_code16(KC_RBRC); break;  // [
        case KC_LCBR: tap_code16(KC_RCBR); break;  // {
        case KC_LABK: tap_code16(KC_RABK); break;  // <
        case KC_QUOT: tap_code16(KC_QUOT); break;  // '
        case KC_DQUO: tap_code16(KC_DQUO); break;  // "
        case KC_GRV:  tap_code16(KC_GRV);  break;  // `
        default: return false;
    }
    tap_code(KC_LEFT);
    last_keycode = KC_NO;
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case KC_ESC:
                if (get_oneshot_mods()) {
                    clear_oneshot_mods();
                    return false;
                }
                return true;

            case XC_LFT_SPLT:
                tap_code16(LGUI(KC_J));
                wait_ms(4);
                tap_code(KC_LEFT);
                wait_ms(4);
                tap_code(KC_ENT);
                return false;

            case XC_RGT_SPLT:
                tap_code16(LGUI(KC_J));
                wait_ms(4);
                tap_code(KC_RGHT);
                wait_ms(4);
                tap_code(KC_ENT);
                return false;

            case DBL_QUOT:
                SEND_STRING("\"\"");
                tap_code(KC_LEFT);
                return false;

            case VIWPYIW:
                SEND_STRING("viwpyiw");
                return false;

            case DELETE_LINE:
                SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
                SEND_STRING(SS_LGUI(SS_TAP(X_BSPC)));
                return false;

            case LEFT_WORD:
                register_code(KC_LSFT);
                tap_code16(LALT(KC_LEFT));
                unregister_code(KC_LSFT); 
                return false;

            case RIGHT_WORD:
                register_code(KC_LSFT);
                tap_code16(LALT(KC_RGHT));
                unregister_code(KC_LSFT); 
                return false;

            case KC_LPRN: case KC_LBRC: case KC_LCBR: case KC_LABK: case KC_QUOT: case KC_DQUO: case KC_GRV:
                handle_opening_pair(keycode);
                return false;

            case CLOSE_PAIR:
                return handle_closing_pair();
        }
    }
    return true;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case HOME_N:
    case HOME_E:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
}

