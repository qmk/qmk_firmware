// Copyright 2023 Travis Reed (@dancxjo)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer {
    _ENGRAM = 0,
    _QWERTY,
    _ENGRAM_SHIFT,
    _FUNCTION,
    _MEDIA
};

/* Combines the compose key (right super) and the AltGr */
#define KC_COMP MT(MOD_RALT, KC_RGUI)
#define KC_SCMP MT(MOD_RSFT | MOD_RALT, KC_RGUI)

#define KC_STAB MT(MOD_LSFT, KC_TAB)

/* Use a fake shift layer since Engram switches level 2 assignments */
#define KC_PSFT MO(_ENGRAM_SHIFT)

#define KC_FUNC TT(_FUNCTION)
#define KC_MEDI TT(_MEDIA)

/* Easily switch between MacOS & other OSes*/
#define KC_HLM1 LM(1, MOD_LCTL)
#define KC_HLM2 LM(1, MOD_LGUI)
#define KC_SHM1 LM(1, MOD_LCTL | MOD_LSFT)
#define KC_SHM2 LM(1, MOD_LGUI | MOD_LSFT)
#define KC_STRN RSFT(KC_TRNS)

#define KC_FORW LGUI(KC_TAB)
#define KC_BACK LGUI(LSFT(KC_TAB))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Differs slightly from official Engram in that {} are the level 1 and [] are the level 2 */
        [_ENGRAM] = LAYOUT_ergodox_pretty(
            KC_LCBR, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    CG_NORM, KC_PAUSE, KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_RCBR,
            KC_TAB,  KC_B,    KC_Y,    KC_O,    KC_U,    KC_QUOT, KC_AT,   KC_HASH,  KC_DQUO, KC_L,    KC_D,    KC_W,   KC_V,    KC_Z,
            KC_CAPS, KC_C,    KC_I,    KC_E,    KC_A,    KC_COMM,                    KC_DOT,  KC_H,    KC_T,    KC_S,   KC_N,    KC_Q,
            KC_PSFT, KC_G,    KC_X,    KC_J,    KC_K,    KC_MINS, KC_SLSH, KC_PSCR,  KC_QUES, KC_R,    KC_M,    KC_F,   KC_P,    KC_PSFT,
            KC_HLM1, KC_FUNC, KC_MEDI, KC_LALT, KC_HLM2,                             KC_RGUI, KC_RALT, KC_MEDI, KC_FUNC,KC_HLM1,
                                       KC_INS,  KC_HOME,                             KC_END,  KC_DEL,
                                                KC_PGUP,                             KC_PGDN,
                                       KC_ENT,  KC_ESC,  KC_LSFT,                    KC_RSFT, KC_BSPC, KC_SPC
        ),
        [_ENGRAM_SHIFT] = LAYOUT_ergodox_pretty(
            KC_LBRC, KC_PIPE,    KC_EQL,     KC_TILD,    KC_PLUS,    KC_LT,   CG_SWAP, KC_STRN, KC_GT,   KC_CIRC,    KC_AMPR,    KC_PERC,    KC_ASTR,    KC_RBRC,
            KC_STRN, RSFT(KC_B), RSFT(KC_Y), RSFT(KC_O), RSFT(KC_U), KC_LPRN, KC_GRV,  KC_DLR,  KC_RPRN, RSFT(KC_L), RSFT(KC_D), RSFT(KC_W), RSFT(KC_V), RSFT(KC_Z),
            KC_STRN, RSFT(KC_C), RSFT(KC_I), RSFT(KC_E), RSFT(KC_A), KC_SCLN,                   KC_COLN, RSFT(KC_H), RSFT(KC_T), RSFT(KC_S), RSFT(KC_N), RSFT(KC_Q),
            KC_TRNS, RSFT(KC_G), RSFT(KC_X), RSFT(KC_J), RSFT(KC_K), KC_UNDS, KC_BSLS, KC_STRN, KC_EXLM, RSFT(KC_R), RSFT(KC_M), RSFT(KC_F), RSFT(KC_P), KC_TRNS,
            KC_SHM1, KC_STRN,    KC_STRN,    KC_STRN,    KC_SHM2,                               KC_STRN, KC_STRN,    KC_STRN,    KC_STRN,    KC_SHM1,
                                             KC_STRN,    KC_STRN,                               KC_HYPR, KC_STRN,
                                                         KC_STRN,                               KC_STRN,
                                             KC_SHM1,    KC_STRN,    KC_STRN,                   KC_SHM2, KC_STRN, KC_STRN
        ),
        [_QWERTY] = LAYOUT_ergodox_pretty(
            KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
            KC_TRNS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
            KC_TRNS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_EQL, KC_TRNS,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                       KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,
                                                KC_TRNS,                            KC_TRNS,
                                       KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
        ),
        [_FUNCTION] = LAYOUT_ergodox_pretty(
            KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_BRID, KC_BRIU, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10, KC_PWR,
            KC_APP,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  TG(1),   TG(1),   KC_F16,  KC_F17,  KC_F18,  KC_F19,   KC_F20, KC_SLEP,
            KC_SCRL, KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_WAKE,
            KC_PAUS, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_NO,   CG_SWAP, CG_NORM, KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  QK_BOOT,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,                                   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,
                                       RGB_SAD, RGB_HUD,                                     RGB_HUI, RGB_SAI,
                                                RGB_RMOD,                                     RGB_MOD,
                                       RGB_SPD, RGB_VAD, KC_TRNS,                  KC_TRNS, RGB_VAI, RGB_SPI
        ),
        [_MEDIA] = LAYOUT_ergodox_pretty(
            KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_WREF, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,
            KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_WREF, KC_NO,   KC_NO, KC_NO, KC_NO,   KC_PGUP, KC_UP,   KC_PGDN, KC_MSEL, KC_NO,
            KC_NO,   KC_NO, KC_WSTP, KC_MYCM, KC_WSCH, KC_FIND,               KC_WHOM, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,   KC_NO,
            KC_LSFT, KC_NO, KC_NO,   KC_CALC, KC_NO,   KC_WFAV, KC_NO, KC_NO, KC_NO,   KC_HOME, KC_MAIL, KC_END, KC_NO,   KC_NO,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,                                   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,
                                   KC_MUTE, KC_EJCT,                                 KC_MSTP, KC_MPLY,
                                            KC_MPRV,                                 KC_MNXT,
                                   KC_MRWD, KC_VOLD, KC_TRNS,                        KC_TRNS, KC_VOLU, KC_MFFD
        )
};

char* get_layer_name(uint8_t layer, bool capitalized) {
    char *layer_name = "Unknown ";

    switch (layer) {
        case _ENGRAM:
        case _ENGRAM_SHIFT:
            if (capitalized) {
                layer_name = "ENGRAM  ";
            } else {
                layer_name = "engram  ";
            }
            break;
        case _QWERTY:
            if (capitalized) {
                layer_name = "QWERTY  ";
            } else {
                layer_name = "qwerty  ";
            }
            break;
        case _MEDIA:
            layer_name = "Media+  ";
            break;
        case _FUNCTION:
            layer_name = "Function";
            break;
    }
    return layer_name;
}

void render_locks(led_t led_state) {
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

void render_mods(uint8_t modifiers, uint8_t layer) {
    oled_write_P(modifiers & MOD_MASK_GUI ? PSTR("Super") : PSTR("     "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(modifiers & MOD_MASK_ALT ? PSTR("Alt") : PSTR("   "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(modifiers & MOD_MASK_CTRL ? PSTR("Ctl") : PSTR("   "), false);
    oled_write_P(PSTR(" "), false);

    if (layer == _ENGRAM_SHIFT) {
        oled_write_P(PSTR("Pseudo"), false);
    } else {
        oled_write_P(modifiers & MOD_MASK_SHIFT ? PSTR("Shift ") : PSTR("      "), false);
    }
}

char* get_helm_key(void) {
    if (keymap_config.swap_lctl_lgui) {
        return "Super";
    } else {
        return "Control";
    }
}

bool oled_task_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t modifiers = get_mods()|get_oneshot_mods();
    led_t led_state = host_keyboard_led_state();

    bool real_shifted = modifiers & MOD_MASK_SHIFT;
    bool pseudo_shifted = layer == _ENGRAM_SHIFT;
    bool shifted = real_shifted || pseudo_shifted;
    bool caps = led_state.caps_lock;
    bool capitalized = (caps && !shifted) || (!caps && shifted);

    oled_write_P(PSTR("Layer: "), false);
    oled_write(get_layer_name(layer, capitalized), false);
    oled_write_P(PSTR("\n"), false);

    // Only the master knows if we've swapped the gui and ctl key
    if (is_keyboard_master()) {
        oled_write_P(PSTR(" Helm: "), false);
        oled_write(get_helm_key(), false);
    }

    oled_write_P(PSTR("\n"), false);

    render_mods(modifiers, layer);
    oled_write_P(PSTR("\n"), false);

    render_locks(led_state);

    return false;
}
