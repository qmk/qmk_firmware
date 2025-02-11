// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "lib/achordion.h"
#include "lib/crosses.h"

/*
 * Keycodes, combos, and layers! oh my!
 */

enum CROSSES_LAYERS {
    _BASE,
    _NUM,
    _NAV,
    _MEDIA,
    _FUNC,
    _MOUS,
};

enum my_keycodes {
    VIMS = SAFE_RANGE,
    LARR,
    FARR,
    EPIP,
    LVBC,
    RVBC,
    BARR,
    MSE_INC,
    MSE_DEC,
    DRAG_SCROLL,
    MSE_TOGG,
};

enum combos {
    WY_TAB,
    DH_CAPS,
    HCOMA_MINS,
    WSPC_VIM,
    FU_QUOTE,
    PL_DQUOTE,
    CCOM_LARR,
    XDOT_FARR,
    GM_EPIP,
    COMD_UNDERS,
    ZDOT_BARR,
};

const uint16_t PROGMEM wy_combo[]     = {KC_W, KC_Y, COMBO_END};
const uint16_t PROGMEM dh_combo[]     = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM hcomma_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM wspc_combo[]   = {KC_W, KC_SPC, COMBO_END};
const uint16_t PROGMEM fu_combo[]     = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM pl_combo[]     = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM ccom_combo[]   = {KC_C, KC_COMM, COMBO_END};
const uint16_t PROGMEM xdot_combo[]   = {KC_X, KC_DOT, COMBO_END};
const uint16_t PROGMEM gm_combo[]     = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM comd_combo[]   = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM zdot_combo[]   = {KC_Z, KC_DOT, COMBO_END};

// clang-format off
//
combo_t key_combos[] = {
    [WY_TAB] = COMBO(wy_combo, KC_TAB),
    [DH_CAPS] = COMBO(dh_combo, CW_TOGG),
    [HCOMA_MINS] = COMBO(hcomma_combo, KC_MINS),
    [WSPC_VIM] = COMBO(wspc_combo, VIMS),
    [FU_QUOTE] = COMBO(fu_combo, KC_QUOT),
    [PL_DQUOTE] = COMBO(pl_combo, S(KC_QUOT)),
    [CCOM_LARR] = COMBO(ccom_combo, LARR),
    [XDOT_FARR] = COMBO(xdot_combo, FARR),
    [GM_EPIP] = COMBO(gm_combo, EPIP),
    [COMD_UNDERS] = COMBO(comd_combo, S(KC_MINS)),
    [ZDOT_BARR] = COMBO(zdot_combo, BARR),
};

/*
 * Keymaps!
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────┬───────────┬───────────┬───────────┬────────────┐                      ┌──────┬────────────┬───────────┬───────────┬───────────┐
//    │     q     │     w     │     f     │     p     │     b      │                      │  j   │     l      │     u     │     y     │     ;     │
//    ├───────────┼───────────┼───────────┼───────────┼────────────┤                      ├──────┼────────────┼───────────┼───────────┼───────────┤
//    │ LGUI_T(a) │ LALT_T(r) │ LCTL_T(s) │ LSFT_T(t) │     g      │                      │  m   │ RSFT_T(n)  │ RCTL_T(e) │ RALT_T(i) │ RGUI_T(o) │
//    ├───────────┼───────────┼───────────┼───────────┼────────────┤                      ├──────┼────────────┼───────────┼───────────┼───────────┤
//    │     z     │     x     │     c     │     d     │     v      │                      │  k   │     h      │     ,     │     .     │ LT(3, /)  │
//    └───────────┴───────────┴───────────┼───────────┼────────────┼─────┐   ┌────────────┼──────┼────────────┼───────────┴───────────┴───────────┘
//                                        │   MO(5)   │ LT(2, esc) │ spc │   │ LT(1, ent) │ bspc │ LT(4, del) │
//                                        └───────────┴────────────┴─────┘   └────────────┴──────┴────────────┘
[_BASE] = LAYOUT_default(
  KC_Q         , KC_W         , KC_F         , KC_P         , KC_B          ,                               KC_J          , KC_L          , KC_U         , KC_Y         , KC_SCLN       ,
  LGUI_T(KC_A) , LALT_T(KC_R) , LCTL_T(KC_S) , LSFT_T(KC_T) , KC_G          ,                               KC_M          , RSFT_T(KC_N)  , RCTL_T(KC_E) , RALT_T(KC_I) , RGUI_T(KC_O)  ,
  KC_Z         , KC_X         , KC_C         , KC_D         , KC_V          ,                               KC_K          , KC_H          , KC_COMM      , KC_DOT       , LT(3, KC_SLSH),
                                               MO(5)        , LT(2, KC_ESC) , KC_SPC ,      LT(1, KC_ENT) , KC_BSPC       , LT(4, KC_DEL)
),

//    ┌──────┬───┬───┬───────────┬──────┐               ┌──────┬───────────┬───────────┬──────┬─────┐
//    │ S(8) │ 7 │ 8 │     9     │  /   │               │  \   │   S(9)    │   S(0)    │ S(\) │     │
//    ├──────┼───┼───┼───────────┼──────┤               ├──────┼───────────┼───────────┼──────┼─────┤
//    │  -   │ 4 │ 5 │ LSFT_T(6) │ S(=) │               │ S(5) │ RSFT_T([) │ RCTL_T(]) │ S(;) │  ;  │
//    ├──────┼───┼───┼───────────┼──────┤               ├──────┼───────────┼───────────┼──────┼─────┤
//    │  `   │ 1 │ 2 │     3     │  =   │               │  [   │     ]     │           │      │     │
//    └──────┴───┴───┼───────────┼──────┼─────┐   ┌─────┼──────┼───────────┼───────────┴──────┴─────┘
//                   │           │  0   │     │   │     │      │           │
//                   └───────────┴──────┴─────┘   └─────┴──────┴───────────┘
[_NUM] = LAYOUT_default(
  S(KC_8) , KC_7 , KC_8 , KC_9         , KC_SLSH   ,                         KC_BSLS , S(KC_9)         , S(KC_0)         , S(KC_BSLS) , KC_TRNS,
  KC_MINS , KC_4 , KC_5 , LSFT_T(KC_6) , S(KC_EQL) ,                         S(KC_5) , RSFT_T(KC_LBRC) , RCTL_T(KC_RBRC) , S(KC_SCLN) , KC_SCLN,
  KC_GRV  , KC_1 , KC_2 , KC_3         , KC_EQL    ,                         KC_LBRC , KC_RBRC         , KC_TRNS         , KC_TRNS    , KC_TRNS,
                          KC_TRNS      , KC_0      , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌──────┬──────┬──────┬───────┬────┐             ┌────┬──────┬──────┬──────┬──────┐
//    │  no  │  no  │  no  │  no   │ no │             │ no │  no  │  no  │  no  │  no  │
//    ├──────┼──────┼──────┼───────┼────┤             ├────┼──────┼──────┼──────┼──────┤
//    │ lgui │ lalt │ lctl │ lsft  │ no │             │ no │ left │ down │  up  │ rght │
//    ├──────┼──────┼──────┼───────┼────┤             ├────┼──────┼──────┼──────┼──────┤
//    │  no  │  no  │ copy │ paste │ no │             │ no │ home │ end  │ pgdn │ pgup │
//    └──────┴──────┴──────┼───────┼────┼────┐   ┌────┼────┼──────┼──────┴──────┴──────┘
//                         │  no   │ no │ no │   │ no │ no │  no  │
//                         └───────┴────┴────┘   └────┴────┴──────┘
[_NAV] = LAYOUT_default(
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO ,                     KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO  ,
  KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , KC_NO ,                     KC_NO , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT,
  KC_NO   , KC_NO   , KC_COPY , KC_PSTE , KC_NO ,                     KC_NO , KC_HOME , KC_END  , KC_PGDN , KC_PGUP,
                                KC_NO   , KC_NO , KC_NO ,     KC_NO , KC_NO , KC_NO
),

//    ┌──────┬──────┬──────┬──────┬──────┐             ┌────┬────┬────┬────┬────┐
//    │  no  │  no  │  no  │  no  │  no  │             │ no │ no │ no │ no │ no │
//    ├──────┼──────┼──────┼──────┼──────┤             ├────┼────┼────┼────┼────┤
//    │ mprv │ vold │ mply │ volu │ mnxt │             │ no │ no │ no │ no │ no │
//    ├──────┼──────┼──────┼──────┼──────┤             ├────┼────┼────┼────┼────┤
//    │  no  │  no  │  no  │  no  │  no  │             │ no │ no │ no │ no │ no │
//    └──────┴──────┴──────┼──────┼──────┼────┐   ┌────┼────┼────┼────┴────┴────┘
//                         │  no  │  no  │ no │   │ no │ no │ no │
//                         └──────┴──────┴────┘   └────┴────┴────┘
[_MEDIA] = LAYOUT_default(
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,                     KC_NO , KC_NO , KC_NO , KC_NO , KC_NO,
  KC_MPRV , KC_VOLD , KC_MPLY , KC_VOLU , KC_MNXT ,                     KC_NO , KC_NO , KC_NO , KC_NO , KC_NO,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,                     KC_NO , KC_NO , KC_NO , KC_NO , KC_NO,
                                KC_NO   , KC_NO   , KC_NO ,     KC_NO , KC_NO , KC_NO
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌─────┬──────┬──────┬──────┬──────┐
//    │ f11 │ f12 │ f13 │ f14 │ f15 │               │     │      │      │      │      │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────┼──────┼──────┼──────┼──────┤
//    │ f6  │ f7  │ f8  │ f9  │ f10 │               │     │ rsft │ rctl │ ralt │ rgui │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────┼──────┼──────┼──────┼──────┤
//    │ f1  │ f2  │ f3  │ f4  │ f5  │               │     │      │      │      │      │
//    └─────┴─────┴─────┼─────┼─────┼─────┐   ┌─────┼─────┼──────┼──────┴──────┴──────┘
//                      │     │     │     │   │     │     │      │
//                      └─────┴─────┴─────┘   └─────┴─────┴──────┘
[_FUNC] = LAYOUT_default(
  KC_F11 , KC_F12 , KC_F13 , KC_F14  , KC_F15  ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_F6  , KC_F7  , KC_F8  , KC_F9   , KC_F10  ,                         KC_TRNS , KC_RSFT , KC_RCTL , KC_RALT , KC_RGUI,
  KC_F1  , KC_F2  , KC_F3  , KC_F4   , KC_F5   ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                             KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌──────┬─────────┬─────────┬─────────────┬────┐             ┌────────┬─────────┬─────────┬──────────┬─────────┐
//    │ lsft │  lalt   │   no    │     no      │ no │             │ EE_CLR │ MSE_INC │ MSE_DEC │    no    │   no    │
//    ├──────┼─────────┼─────────┼─────────────┼────┤             ├────────┼─────────┼─────────┼──────────┼─────────┤
//    │ lctl │ MS_BTN3 │ MS_BTN2 │   MS_BTN1   │ no │             │   no   │  rsft   │  rctl   │   ralt   │  rgui   │
//    ├──────┼─────────┼─────────┼─────────────┼────┤             ├────────┼─────────┼─────────┼──────────┼─────────┤
//    │ lgui │   no    │   no    │ DRAG_SCROLL │ no │             │   no   │   no    │   no    │ MSE_TOGG │ DB_TOGG │
//    └──────┴─────────┴─────────┼─────────────┼────┼────┐   ┌────┼────────┼─────────┼─────────┴──────────┴─────────┘
//                               │             │ no │ no │   │ no │   no   │   no    │
//                               └─────────────┴────┴────┘   └────┴────────┴─────────┘
[_MOUS] = LAYOUT_default(
  KC_NO   , KC_NO , KC_NO   , KC_NO       , KC_NO ,                     EE_CLR , MSE_INC , MSE_DEC , KC_NO    , KC_NO  ,
  KC_NO   , MS_BTN3 , MS_BTN2 , MS_BTN1     , KC_NO ,                     KC_NO  , KC_RSFT , KC_RCTL , KC_RALT  , KC_RGUI,
  KC_NO   , KC_NO   , KC_NO   , DRAG_SCROLL , KC_NO ,                     KC_NO  , KC_NO   , KC_NO   , MSE_TOGG , DB_TOGG,
                                KC_TRNS     , KC_NO , KC_NO ,     KC_NO , KC_NO  , KC_NO
)
};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case RSFT_T(KC_LBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(S(KC_LBRC));
                return false;
            }
            break;

        case RCTL_T(KC_RBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(S(KC_RBRC));
                return false;
            }
            break;

        case VIMS:
            if (record->event.pressed) {
                tap_code16(KC_ESC);
                SEND_STRING(":w\n");

                return false;
            }
            break;

        case EPIP:
            if (record->event.pressed) {
                SEND_STRING("|> ");

                return false;
            }
            break;

        case LARR:
            if (record->event.pressed) {
                SEND_STRING("-> ");

                return false;
            }
            break;

        case FARR:
            if (record->event.pressed) {
                SEND_STRING("=> ");

                return false;
            }
            break;

        case BARR:
            if (record->event.pressed) {
                SEND_STRING("<- ");

                return false;
            }
            break;
        case MSE_INC:
            if (record->event.pressed) {
#if defined(POINTING_DEVICE_COMBINED) || defined(POINTING_DEVICE_RIGHT) || defined(POINGINT_DEVICE_LEFT)
                change_pointer_dpi(&global_user_config, true);
#endif /* ifdef POINTING_DEVICE */
                debug_config_to_console(&global_user_config);

                return false;
            }
            break;
        case MSE_DEC:
            if (record->event.pressed) {
                change_pointer_dpi(&global_user_config, false);
                debug_config_to_console(&global_user_config);

                return false;
            }
            break;
        case MSE_TOGG:
            if (record->event.pressed) {
#if defined(POINTING_DEVICE_COMBINED) || defined(POINTING_DEVICE_RIGHT) || defined(POINGINT_DEVICE_LEFT)
                bool current_state = get_auto_mouse_enable();
                set_auto_mouse_enable(!current_state);
#endif /* ifdef POINTING_DEVICE */

                return false;
            }
            break;
        case DRAG_SCROLL:
            set_scrolling = record->event.pressed;
            break;
    }

    return true;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    switch (tap_hold_keycode) {
        case 0x4128:
            return true;
            break;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

void matrix_scan_user(void) {
    achordion_task();
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }

    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();

    // clang-format off
    const char* layer_names[] = {
        [_BASE]  = "BASE  CPI: ",
        [_NUM]   = "PROG  CPI: ",
        [_NAV]   = "NAVI  CPI: ",
        [_MEDIA] = "MEDIA CPI: ",
        [_FUNC]  = "FUNC  CPI: ",
        [_MOUS]  = "MOUSE CPI: ",
    };
    // clang-format on

    char     cpi_str[6];
    uint16_t current_dpi = get_pointer_dpi(&global_user_config);

    snprintf(cpi_str, sizeof(cpi_str), "%u", (unsigned int)current_dpi);

    oled_write(PSTR(layer_names[get_highest_layer(layer_state)]), false);
    oled_write(cpi_str, false);

    return false;
}
#endif /* ifdef OLED_ENABLE */

#if defined(POINTING_DEVICE_COMBINED) || defined(POINTING_DEVICE_RIGHT) || defined(POINGINT_DEVICE_LEFT)
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUS);
    set_auto_mouse_enable(false);
}
#endif /* ifdef POINTING_DEVICE */
