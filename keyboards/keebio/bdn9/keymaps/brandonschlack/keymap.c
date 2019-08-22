#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum bdn9_layers {
    __LR_NAV = KEYMAP_LAYERS,
    __LR_REVIEW,
    __LR_EDIT
};

enum bdn9_keycodes {
    TG_LNAV = KEYMAP_SAFE_RANGE,
    TG_REVW,
    TG_EDIT
};

// Tap Dances
enum bdn9_dances {
    TD_DTAP_LGHT = 0,
    TD_DTAP_MAGC
};
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_DTAP_LGHT] = ACTION_TAP_DANCE_TRIGGER_LAYER(DOUBLE_TAP, _LIGHT),
    [TD_DTAP_MAGC] = ACTION_TAP_DANCE_TRIGGER_LAYER(DOUBLE_TAP, _MAGIC),
};
// Tap Dance Aliases
#define DTP_LGT   TD(TD_DTAP_LGHT)
#define DTP_MGC   TD(TD_DTAP_MAGC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Navigation
        ┌───────────┐  ┌───────────┐
        │  Scroll   │  │    Tab    │
        │  Up   Dn  │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │ ReOTab │ CmdTab │ ClsTab │
        ├────────┼────────┼────────┤
        │  PgDn  │   Up   │  PgUp  │
        ├────────┼────────┼────────┤
        │  Left  │  Down  │  Rght  │
        └────────┴────────┴────────┘
     */
    [_NAVI] = LAYOUT(
        REO_TAB, CMD_TAB, CLS_TAB,
        KC_PGDN, KC_UP, DTP_LGT,
        KC_LEFT, KC_DOWN, DTP_MGC
    ),
    /*
        Layer: Reeder
        ┌───────────┐  ┌───────────┐
        │   Items   │  │    Subs   │
        │  Prv  Nxt │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │ VwBrsw │  Star  │  Sync  │
        ├────────┼────────┼────────┤
        │ CmdTab │ TgRead │  Clear │
        ├────────┼────────┼────────┤
        │ VwStard│ VwUnrd │  VwAll │
        └────────┴────────┴────────┘
     */
    [_REEDER] = LAYOUT(
        KC_H, KC_S, KC_R,
        CMD_TAB, KC_M, DTP_LGT,
        G(KC_1), G(KC_2), DTP_MGC
    ),
    /*
        Layer: Media
        ┌───────────┐  ┌───────────┐
        │    Vol    │  │   Track   │
        │  Prv  Nxt │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │  Mute  │ Player │  Sync  │
        ├────────┼────────┼────────┤
        │ YT<10s │ YT Ply │ YT>10s │
        ├────────┼────────┼────────┤
        │  Left  │  Spce  │  Rght  │
        └────────┴────────┴────────┘
     */
    [_MEDIA] = LAYOUT(
        KC_MUTE, MC_PLYR, KC_MPLY,
        KC_J, KC_K, DTP_LGT,
        KC_LEFT, KC_SPC, DTP_MGC
    ),
    /*
        Layer: Macro/Karabiner
        ┌───────────┐  ┌───────────┐
        │           │  │           │
        │   -    +  │  │   .    =  │
        ├────────┬──┴──┴──┬────────┤
        │    1   │    2   │    3   │
        ├────────┼────────┼────────┤
        │    4   │    5   │    6   │
        ├────────┼────────┼────────┤
        │    7   │    8   │    9   │
        └────────┴────────┴────────┘
     */
    [_MACRO] = LAYOUT(
        KC_P1, KC_P2, KC_P3,
        KC_P4, KC_P5, DTP_LGT,
        KC_P7, KC_P8, DTP_MGC
    ),
    /*
        Layer: Lightroom Navigation
        ┌───────────┐  ┌───────────┐
        │ Thumbnail │  │ Scrl Grid │
        │ Dec   Inc │  │ Up     Dn │
        ├────────┬──┴──┴──┬────────┤
        │ TgRevw │CylGrdVw│ TgEdit │
        ├────────┼────────┼────────┤
        │  Start │   Up   │  End   │
        ├────────┼────────┼────────┤
        │  Left  │  Down  │  Rght  │
        └────────┴────────┴────────┘
     */
    [__LR_NAV] = LAYOUT(
        TG_REVW, KC_J, TG_EDIT,
        KC_HOME, KC_UP, DTP_LGT,
        KC_LEFT, KC_DOWN, DTP_MGC
    ),
    /*
        Layer: Review/Rate
        ┌───────────┐  ┌───────────┐
        │   Stars   │  │   Flag    │
        │ Dec   Inc │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ TgLNav │ Yellow │ TgEdit │
        ├────────┼────────┼────────┤
        │ NoStar │  Green │ UnFlag │
        ├────────┼────────┼────────┤
        │  Left  │  Blue  │  Rght  │
        └────────┴────────┴────────┘
     */
    [__LR_REVIEW] = LAYOUT(
        TG_LNAV, KC_7, TG_EDIT,
        KC_0, KC_8, DTP_LGT,
        KC_LEFT, KC_6, DTP_MGC
    ),
    /*
        Layer: Edit/Develop
        ┌───────────┐  ┌───────────┐
        │  Sliders  │  │   Value   │
        │ Prv   Nxt │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ TgRevw │ Bf/Aft │ TgLNav │
        ├────────┼────────┼────────┤
        │ FlgRjt │  Undo  │ FlgPkd │
        ├────────┼────────┼────────┤
        │  Left  │  Redo  │  Rght  │
        └────────┴────────┴────────┘
     */
    [__LR_EDIT] = LAYOUT(
        TG_REVW, KC_BSLS, TG_LNAV,
        KC_X, MC_UNDO, DTP_LGT,
        KC_LEFT, MC_REDO, DTP_MGC
    ),
    /*
        Layer: Light
        ┌───────────┐  ┌───────────┐
        │  RGB Hue  │  │  RGB Sat  │
        │ Prv   Nxt │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ RGBTgl │  Val+  │ TgLNav │
        ├────────┼────────┼────────┤
        │  Mode- │  Val-  │  Mode+ │
        ├────────┼────────┼────────┤
        │ LyrTgl │ NxtThm │  XXXX  │
        └────────┴────────┴────────┘
     */
    [_LIGHT] = LAYOUT(
        RGB_TOG, RGB_VAI, TG_LGHT,
        RGB_RMOD,RGB_VAD, RGB_MOD,
        RGB_LYR, RGB_THM, XXXXXXX
    ),
    /*
        Layer: Magic
        ┌───────────┐  ┌───────────┐
        │    XXXX   │  │   XXXX    │
        │           │  │           │
        ├────────┬──┴──┴──┬────────┤
        │  MAKE  │  Navi  │  RESET │
        ├────────┼────────┼────────┤
        │ Reeder │  Media │ Keypad │
        ├────────┼────────┼────────┤
        │ LR Rvw │ LR Nav │ LR Edt │
        └────────┴────────┴────────┘
     */
    [_MAGIC] = LAYOUT(
        KC_MAKE, TG_NAVI, TG_LGHT,
        TG_REDR, TG_MEDA, TG_KYPD,
        TG_REVW, TG_LNAV, TG_EDIT
    ),
};

/**
 * Encoder
 */
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _NAVI:
                if (!clockwise) {
                    tap_code(MC_WH_D);
                } else {
                    tap_code(MC_WH_U);
                }
                break;
            case _REEDER:
                if (!clockwise) {
                    tap_code(KC_J);
                } else {
                    tap_code(KC_K);
                }
                break;
            case _MEDIA:
                if (!clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _MACRO:
                if (!clockwise) {
                    tap_code(KC_PPLS);
                } else {
                    tap_code(KC_PMNS);
                }
                break;
            case __LR_NAV:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case __LR_REVIEW:
                if (!clockwise) {
                    tap_code(KC_RBRC);
                } else {
                    tap_code(KC_LBRC);
                }
                break;
            case __LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_DOT);
                } else {
                    tap_code(KC_COMM);
                }
                break;
            case _LIGHT:
                if (!clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    }
    else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _NAVI:
                if (!clockwise) {
                    tap_code16(NXT_TAB);
                } else {
                    tap_code16(PRV_TAB);
                }
                break;
            case _REEDER:
                if (!clockwise) {
                    tap_code(KC_N);
                } else {
                    tap_code(KC_P);
                }
                break;
            case _MEDIA:
                if (!clockwise) {
                    tap_code(KC_MFFD);
                } else {
                    tap_code(KC_MRWD);
                }
                break;
            case _MACRO:
                if (!clockwise) {
                    tap_code(KC_PEQL);
                } else {
                    tap_code(KC_PDOT);
                }
                break;
            case __LR_NAV:
                if (!clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
                break;
            case __LR_REVIEW:
                if (!clockwise) {
                    tap_code16(G(KC_UP));
                } else {
                    tap_code16(G(KC_DOWN));
                }
                break;
            case __LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case _LIGHT:
                if (!clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
        }
    }
}

/**
 * Keycodes
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_LNAV:
            if (!record->event.pressed) {
                tap_code(KC_G);
                layer_move(__LR_NAV);
            }
            break;
        case TG_REVW:
            if (!record->event.pressed) {
                tap_code(KC_E);
                layer_move(__LR_REVIEW);
            }
            break;
        case TG_EDIT:
            if (!record->event.pressed) {
                tap_code(KC_D);
                layer_move(__LR_EDIT);
            }
            break;
    }
    return true;
}

/**
 * Layer Switch
 */
layer_state_t layer_state_set_keymap (layer_state_t state) {
    switch (get_highest_layer(state)) {
        case __LR_NAV:
            rgb_layer_helper(HSV_TEAL);
            break;
        case __LR_REVIEW:
            rgb_layer_helper(HSV_CYAN);
            break;
        case __LR_EDIT:
            rgb_layer_helper(HSV_AZURE);
            break;
    }
    return state;
}

/**
 * Tap Dances
 */
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer) {
    uint16_t keycode = 0;
    switch (toggle_layer) {
        case _LIGHT:
            switch (get_highest_layer(layer_state)) {
                case _NAVI:
                    keycode = KC_PGUP;
                    break;
                case _REEDER:
                case _MEDIA:
                    keycode = KC_L;
                    break;
                case _MACRO:
                    keycode = KC_P6;
                    break;
                case __LR_NAV:
                    keycode = KC_END;
                case __LR_REVIEW:
                    keycode = KC_U;
                case __LR_EDIT:
                    keycode = KC_P;
                    break;
            }
            break;
        case _MAGIC:
            switch (get_highest_layer(layer_state)) {
                case _NAVI:
                case _MEDIA:
                case __LR_NAV:
                case __LR_REVIEW:
                case __LR_EDIT:
                    keycode = KC_RGHT;
                    break;
                case _REEDER:
                    keycode = G(KC_3);
                    break;
                case _MACRO:
                    keycode = KC_P9;
                    break;
            }
            break;
    }
    if (!reset) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}
