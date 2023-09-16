/* Copyright 2020 Brandon Schlack
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "brandonschlack.h"

/**
 * Layer Names
 */
enum bdn9_layers {
    _REEDER = 0,
    _MEDIA,
    _NAVI,
    _KARABINER,
    LR_NAV,
    LR_REVIEW,
    LR_EDIT
};

#define _AUDIO   13
#define _LIGHT   14

/**
 * Keycodes & Macros
 */
#define DF_REDR   DF(_REEDER)          // Set Default Layer to Reeder shortcuts
#define DF_MEDA   DF(_MEDIA)           // Set Default Layer to Media controls
#define DF_NAVI   DF(_NAVI)            // Set Default Layer to Navigation shortcuts
#define DF_KBNR   DF(_KARABINER)       // Set Default Layer to Basic Macro keys

enum bdn9_keycodes {
    TG_LNAV = KEYMAP_SAFE_RANGE,
    TG_REVW,
    TG_EDIT
};

/**
 * Tap Dances
 *
 * Use tap dance for layer changes
 */
enum bdn9_dances {
    TD_DTAP_ADIO = 0,
    TD_DTAP_LGHT,
    TD_DTAP_ADJT
};
// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_DTAP_ADIO] = ACTION_TAP_DANCE_TRIGGER_LAYER(DOUBLE_TAP, _AUDIO),
    [TD_DTAP_LGHT] = ACTION_TAP_DANCE_TRIGGER_LAYER(DOUBLE_TAP, _LIGHT),
    [TD_DTAP_ADJT] = ACTION_TAP_DANCE_TRIGGER_LAYER(DOUBLE_TAP, _ADJUST),
};
// Tap Dance Aliases
#if defined(RGBLIGHT_ENABLE)
#define DTP_AVC   TD(TD_DTAP_LGHT)   //
#elif defined(AUDIO_ENABLE)
#define DTP_AVC   TD(TD_DTAP_ADIO)
#endif
#define DTP_ADJ   TD(TD_DTAP_ADJT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Reeder
        ┌───────────┐  ┌───────────┐
        │   Items   │  │    Subs   │
        │  Prv  Nxt │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │ VwBrsw │  Star  │  Sync  │
        ├────────┼────────┼────────┤
        │ CmdTab │ TgRead │  Clear │
        ├────────┼────────┼────────┤
        │ VwStard│ VwUnrd │  VwAll │
        └────────┴────────┴────────┘
     */
    [_REEDER] = LAYOUT(
        KC_H, KC_S, KC_R,
        CMD_TAB, KC_M, DTP_AVC,
        G(KC_1), G(KC_2), DTP_ADJ
    ),
    /*
        Layer: Media
        ┌───────────┐  ┌───────────┐
        │    Vol    │  │   Track   │
        │  Prv  Nxt │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │  Mute  │ Player │  Sync  │
        ├────────┼────────┼────────┤
        │ YT<10s │ YT Ply │ YT>10s │
        ├────────┼────────┼────────┤
        │  Left  │  Spce  │  Rght  │
        └────────┴────────┴────────┘
     */
    [_MEDIA] = LAYOUT(
        KC_MUTE, MC_PLYR, KC_MPLY,
        KC_J, KC_K, DTP_AVC,
        KC_LEFT, KC_SPC, DTP_ADJ
    ),
    /*
        Layer: Navigation
        ┌───────────┐  ┌───────────┐
        │  Scroll   │  │    Tab    │
        │  Up   Dn  │  │  Prv  Nxt │
        ├────────┬──┴──┴──┬────────┤
        │ ReOTab │ CmdTab │ ClsTab │
        ├────────┼────────┼────────┤
        │  PgDn  │   Up   │  PgUp  │
        ├────────┼────────┼────────┤
        │  Left  │  Down  │  Rght  │
        └────────┴────────┴────────┘
     */
    [_NAVI] = LAYOUT(
        REO_TAB, CMD_TAB, CLS_TAB,
        KC_PGDN, KC_UP, DTP_AVC,
        KC_LEFT, KC_DOWN, DTP_ADJ
    ),
    /*
        Layer: Macro/Karabiner
        ┌───────────┐  ┌───────────┐
        │           │  │           │
        │   -    +  │  │   .    =  │
        ├────────┬──┴──┴──┬────────┤
        │    1   │    2   │    3   │
        ├────────┼────────┼────────┤
        │    4   │    5   │    6   │
        ├────────┼────────┼────────┤
        │    7   │    8   │    9   │
        └────────┴────────┴────────┘
     */
    [_KARABINER] = LAYOUT(
        KC_P1, KC_P2, KC_P3,
        KC_P4, KC_P5, DTP_AVC,
        KC_P7, KC_P8, DTP_ADJ
    ),
    /*
        Layer: Lightroom Navigation
        ┌───────────┐  ┌───────────┐
        │ Thumbnail │  │ Scrl Grid │
        │ Dec   Inc │  │ Up     Dn │
        ├────────┬──┴──┴──┬────────┤
        │ TgRevw │CylGrdVw│ TgEdit │
        ├────────┼────────┼────────┤
        │  Start │   Up   │  End   │
        ├────────┼────────┼────────┤
        │  Left  │  Down  │  Rght  │
        └────────┴────────┴────────┘
     */
    [LR_NAV] = LAYOUT(
        TG_REVW, KC_J,    TG_EDIT,
        KC_HOME, KC_UP,   DTP_AVC,
        KC_LEFT, KC_DOWN, DTP_ADJ
    ),
    /*
        Layer: Review/Rate
        ┌───────────┐  ┌───────────┐
        │   Stars   │  │   Flag    │
        │ Dec   Inc │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ TgLNav │ Yellow │ TgEdit │
        ├────────┼────────┼────────┤
        │ NoStar │  Green │ UnFlag │
        ├────────┼────────┼────────┤
        │  Left  │  Blue  │  Rght  │
        └────────┴────────┴────────┘
     */
    [LR_REVIEW] = LAYOUT(
        TG_LNAV, KC_7,    TG_EDIT,
        KC_0,    KC_8,    DTP_AVC,
        KC_LEFT, KC_6,    DTP_ADJ
    ),
    /*
        Layer: Edit/Develop
        ┌───────────┐  ┌───────────┐
        │  Sliders  │  │   Value   │
        │ Prv   Nxt │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ TgRevw │ Bf/Aft │ TgLNav │
        ├────────┼────────┼────────┤
        │ FlgRjt │  Undo  │ FlgPkd │
        ├────────┼────────┼────────┤
        │  Left  │  Redo  │  Rght  │
        └────────┴────────┴────────┘
     */
    [LR_EDIT] = LAYOUT(
        TG_REVW, KC_BSLS, TG_LNAV,
        KC_X,    MC_UNDO, DTP_AVC,
        KC_LEFT, MC_REDO, DTP_ADJ
    ),
    /*
        Layer: Light
        ┌───────────┐  ┌───────────┐
        │  RGB Hue  │  │  RGB Sat  │
        │ Prv   Nxt │  │ Dec   Inc │
        ├────────┬──┴──┴──┬────────┤
        │ RGBTgl │  Val+  │ TgLNav │
        ├────────┼────────┼────────┤
        │  Mode- │  Val-  │  Mode+ │
        ├────────┼────────┼────────┤
        │ LyrTgl │ NxtThm │  XXXX  │
        └────────┴────────┴────────┘
     */
    [_LIGHT] = LAYOUT(
        RGB_TOG, RGB_VAI, TG_LGHT,
        RGB_RMOD,RGB_VAD, RGB_MOD,
        RGB_LYR, RGB_THM, XXXXXXX
    ),
    /*
        Layer: ADJUST
        ┌───────────┐  ┌───────────┐
        │    XXXX   │  │   XXXX    │
        │           │  │           │
        ├────────┬──┴──┴──┬────────┤
        │  MAKE  │ Reeder │  Light │
        ├────────┼────────┼────────┤
        │  Media │  Navi  │  Macro │
        ├────────┼────────┼────────┤
        │ LR Rvw │ LR Nav │ LR Edt │
        └────────┴────────┴────────┘
     */
    [_ADJUST] = LAYOUT(
        QM_MAKE, DF_REDR, TG_LGHT,
        DF_MEDA, DF_NAVI, DF_KBNR,
        TG_REVW, TG_LNAV, TG_EDIT
    ),
};

void keyboard_post_init_keymap(void){
    // Debug to Console by default
    debug_enable = true;
}

/**
 * Encoder
 */
const uint16_t PROGMEM encoders[][2][2] = {
    [_REEDER] = {{ KC_K, KC_J }, { KC_P, KC_N }},
    [_MEDIA] = {{ KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT }},
    [_NAVI] = {{ MC_WH_U, MC_WH_D }, { PRV_TAB, NXT_TAB }},
    [_KARABINER] = {{ KC_PMNS, KC_PPLS }, { KC_PDOT, KC_PEQL }},
    [LR_NAV] = {{ KC_MINS, KC_EQL }, { KC_PGDN, KC_PGUP }},
    [LR_REVIEW] = {{ KC_LBRC, KC_RBRC }, { G(KC_DOWN), G(KC_UP) }},
    [LR_EDIT] = {{ KC_COMM, KC_DOT }, { KC_MINS, KC_EQL }},
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case _AUDIO:
            #ifdef AUDIO_ENABLE
            #endif
            break;
        case _LIGHT:
            #ifdef RGBLIGHT_ENABLE
            switch (index) {
                case 0:
                    if (clockwise) {
                        rgblight_increase_hue();
                    } else {
                        rgblight_decrease_hue();
                    }
                    break;
                case 1:
                    if (clockwise) {
                        rgblight_increase_sat();
                    } else {
                        rgblight_decrease_sat();
                    }
                    break;
            }
            #endif
            break;
        default:
            tap_code16(pgm_read_word(&encoders[layer][index][clockwise]));
            break;
    }
    return true;
}

/**
 * Keycodes
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_LNAV:
            if (!record->event.pressed) {
                tap_code(KC_G);
                layer_move(LR_NAV);
            }
            break;
        case TG_REVW:
            if (!record->event.pressed) {
                tap_code(KC_E);
                layer_move(LR_REVIEW);
            }
            break;
        case TG_EDIT:
            if (!record->event.pressed) {
                tap_code(KC_D);
                layer_move(LR_EDIT);
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
        case LR_NAV:
        #if defined(RGBLIGHT_ENABLE)
            rgb_layer_helper(HSV_TEAL);
        #endif
            break;
        case LR_REVIEW:
        #if defined(RGBLIGHT_ENABLE)
            rgb_layer_helper(HSV_CYAN);
        #endif
            break;
        case LR_EDIT:
        #if defined(RGBLIGHT_ENABLE)
            rgb_layer_helper(HSV_AZURE);
        #endif
            break;
        default:
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
                case _REEDER:
                case _MEDIA:
                    keycode = KC_L;
                    break;
                case _NAVI:
                    keycode = KC_PGUP;
                    break;
                case _KARABINER:
                    keycode = KC_P6;
                    break;
                case LR_NAV:
                    keycode = KC_END;
                case LR_REVIEW:
                    keycode = KC_U;
                case LR_EDIT:
                    keycode = KC_P;
                    break;
            }
            break;
        case _ADJUST:
            switch (get_highest_layer(layer_state)) {
                case _REEDER:
                    keycode = G(KC_3);
                    break;
                case _KARABINER:
                    keycode = KC_P9;
                    break;
                case _MEDIA:
                case _NAVI:
                case LR_NAV:
                case LR_REVIEW:
                case LR_EDIT:
                    keycode = KC_RGHT;
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
