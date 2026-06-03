// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Implementation of keycode_label() — see keycode_label.h for the public API.

#include QMK_KEYBOARD_H
#include "keycode_label.h"

/* ---- Small helpers used by the dispatcher below ---- */

// Convert a 4-bit nibble to its hex character.
static inline char nibble_to_hex(uint8_t n) {
    return (n < 10) ? ('0' + n) : ('A' + n - 10);
}

// Append `src` to `dst`, advancing `*dst` and stopping at `end`.
static void append_str(char **dst, char *end, const char *src) {
    while (*src && *dst < end) {
        **dst = *src;
        (*dst)++;
        src++;
    }
}

// Append the decimal representation of a small unsigned integer (0..19).
static void append_small_uint(char **dst, char *end, uint8_t n) {
    if (n >= 10 && *dst < end) { *(*dst)++ = '1'; n -= 10; }
    if (*dst < end) { *(*dst)++ = '0' + n; }
}

// Append the standard mod prefix corresponding to the bits in `mods`
// (bit 0 = Ctrl, 1 = Shift, 2 = Alt, 3 = GUI). Always uses the L names.
static void append_mod_prefix(char **dst, char *end, uint8_t mods) {
    if ((mods & 0x01) && *dst + 2 <= end) { *(*dst)++ = 'C'; *(*dst)++ = '+'; }
    if ((mods & 0x02) && *dst + 2 <= end) { *(*dst)++ = 'S'; *(*dst)++ = '+'; }
    if ((mods & 0x04) && *dst + 2 <= end) { *(*dst)++ = 'A'; *(*dst)++ = '+'; }
    if ((mods & 0x08) && *dst + 2 <= end) { *(*dst)++ = 'G'; *(*dst)++ = '+'; }
}

/* ---- Basic keycodes (0x0000..0x00FF) — the big switch ---- */

static const char *keycode_label_basic(uint16_t kc) {
    switch (kc) {
        // Internal
        case KC_NO:           return "---";
        case KC_TRNS:         return "trns";

        // Modifiers (used as standalone keys, not as wrappers)
        case KC_LCTL:         return "LCtl";
        case KC_LSFT:         return "LSft";
        case KC_LALT:         return "LAlt";
        case KC_LGUI:         return "LGui";
        case KC_RCTL:         return "RCtl";
        case KC_RSFT:         return "RSft";
        case KC_RALT:         return "RAlt";
        case KC_RGUI:         return "RGui";
        case KC_CAPS:         return "Caps";

        // Editing / control
        case KC_ENTER:        return "Entr";
        case KC_SPACE:        return "Spc";
        case KC_TAB:          return "Tab";
        case KC_ESCAPE:       return "Esc";
        case KC_BSPC:         return "Bspc";
        case KC_DELETE:       return "Del";
        case KC_INSERT:       return "Ins";

        // Navigation
        case KC_PGUP:         return "PgUp";
        case KC_PGDN:         return "PgDn";
        case KC_HOME:         return "Home";
        case KC_END:          return "End";
        case KC_UP:           return "Up";
        case KC_DOWN:         return "Down";
        case KC_LEFT:         return "Left";
        case KC_RIGHT:        return "Rght";

        // Punctuation (US layout)
        case KC_MINUS:        return "-";
        case KC_EQUAL:        return "=";
        case KC_LBRC:         return "[";
        case KC_RBRC:         return "]";
        case KC_BSLS:         return "\\";
        case KC_SCLN:         return ";";
        case KC_QUOT:         return "'";
        case KC_GRAVE:        return "`";
        case KC_COMM:         return ",";
        case KC_DOT:          return ".";
        case KC_SLSH:         return "/";

        // Media / consumer
        case KC_MUTE:         return "Mute";
        case KC_VOLU:         return "Vol+";
        case KC_VOLD:         return "Vol-";
        case KC_MPLY:         return "Play";
        case KC_MPRV:         return "Prev";
        case KC_MNXT:         return "Next";
        case KC_MSTP:         return "Stop";

        // Mouse buttons + wheel + cursor (QMK >= 0.27 names; old KC_BTN*,
        // KC_WH_*, KC_MS_* were removed.)
        case MS_BTN1:         return "Btn1";
        case MS_BTN2:         return "Btn2";
        case MS_BTN3:         return "Btn3";
        case MS_BTN4:         return "Btn4";
        case MS_BTN5:         return "Btn5";
        case MS_WHLU:         return "WhUp";
        case MS_WHLD:         return "WhDn";
        case MS_WHLL:         return "WhL";
        case MS_WHLR:         return "WhR";
        case MS_UP:           return "MsUp";
        case MS_DOWN:         return "MsDn";
        case MS_LEFT:         return "MsL";
        case MS_RGHT:         return "MsR";

        // System
        case KC_SYSTEM_POWER: return "Pwr";
        case KC_SYSTEM_SLEEP: return "Slp";
        case KC_SYSTEM_WAKE:  return "Wake";
    }

    // Letters A..Z
    if (kc >= KC_A && kc <= KC_Z) {
        static char buf[2];
        buf[0] = 'A' + (kc - KC_A);
        buf[1] = 0;
        return buf;
    }
    // Digits (KC_1..KC_9, KC_0)
    if (kc >= KC_1 && kc <= KC_0) {
        static char buf[2];
        buf[0] = (kc == KC_0) ? '0' : ('1' + (kc - KC_1));
        buf[1] = 0;
        return buf;
    }
    // Function keys F1..F24
    if (kc >= KC_F1 && kc <= KC_F12) {
        static char buf[4];
        uint8_t n = 1 + (kc - KC_F1);
        buf[0] = 'F';
        if (n < 10) { buf[1] = '0' + n; buf[2] = 0; }
        else        { buf[1] = '1'; buf[2] = '0' + (n - 10); buf[3] = 0; }
        return buf;
    }
    if (kc >= KC_F13 && kc <= KC_F24) {
        static char buf[4];
        uint8_t n = 13 + (kc - KC_F13);
        buf[0] = 'F';
        buf[1] = (n < 20) ? '1' : '2';
        buf[2] = '0' + (n % 10);
        buf[3] = 0;
        return buf;
    }
    return NULL;
}

/* ---- Weak hook for custom (user) keycodes — keymap can override ---- */

__attribute__((weak)) const char *keycode_label_user(uint16_t kc) {
    (void)kc;
    return NULL;
}

/* ---- Public dispatcher ---- */

const char *keycode_label(uint16_t kc) {
    static char buf[12];
    char *p   = buf;
    char *end = buf + sizeof(buf) - 1;

    // Keymap hook for custom keycodes wins if it returns a label.
    const char *user = keycode_label_user(kc);
    if (user) return user;

    // Modifier-wrapped (LCTL(KC_C) -> "C+C", LCTL(LSFT(KC_X)) -> "C+S+X", ...)
    if (kc >= QK_LCTL && kc <= QK_LCTL + 0x0FFF) {
        uint8_t mods = (kc >> 8) & 0x0F;
        append_mod_prefix(&p, end, mods);
        const char *base = keycode_label_basic(kc & 0xFF);
        append_str(&p, end, base ? base : "?");
        *p = '\0';
        return buf;
    }

    // Mod-tap (hold = mods in upper byte, tap = base in lower)
    if (kc >= QK_MOD_TAP && kc <= QK_MOD_TAP_MAX) {
        uint8_t mods = (kc >> 8) & 0x1F;
        append_mod_prefix(&p, end, mods);
        if (p < end) *p++ = '/';
        const char *base = keycode_label_basic(kc & 0xFF);
        append_str(&p, end, base ? base : "?");
        *p = '\0';
        return buf;
    }

    // Layer-tap (LT(2, KC_X) -> "L2/X")
    if (kc >= QK_LAYER_TAP && kc <= QK_LAYER_TAP_MAX) {
        uint8_t layer = (kc >> 8) & 0x0F;
        if (p < end) *p++ = 'L';
        append_small_uint(&p, end, layer);
        if (p < end) *p++ = '/';
        const char *base = keycode_label_basic(kc & 0xFF);
        append_str(&p, end, base ? base : "?");
        *p = '\0';
        return buf;
    }

    // Pure layer keycodes (MO/TO/TG/TT/DF/OSL)
    if (kc >= QK_MOMENTARY && kc <= QK_MOMENTARY_MAX) {
        append_str(&p, end, "MO"); append_small_uint(&p, end, kc & 0x1F);
        *p = '\0'; return buf;
    }
    if (kc >= QK_TO && kc <= QK_TO_MAX) {
        append_str(&p, end, "TO"); append_small_uint(&p, end, kc & 0x1F);
        *p = '\0'; return buf;
    }
    if (kc >= QK_TOGGLE_LAYER && kc <= QK_TOGGLE_LAYER_MAX) {
        append_str(&p, end, "TG"); append_small_uint(&p, end, kc & 0x1F);
        *p = '\0'; return buf;
    }
    if (kc >= QK_LAYER_TAP_TOGGLE && kc <= QK_LAYER_TAP_TOGGLE_MAX) {
        append_str(&p, end, "TT"); append_small_uint(&p, end, kc & 0x1F);
        *p = '\0'; return buf;
    }
    if (kc >= QK_DEF_LAYER && kc <= QK_DEF_LAYER_MAX) {
        append_str(&p, end, "DF"); append_small_uint(&p, end, kc & 0x1F);
        *p = '\0'; return buf;
    }
    if (kc >= QK_ONE_SHOT_LAYER && kc <= QK_ONE_SHOT_LAYER_MAX) {
        append_str(&p, end, "OSL"); append_small_uint(&p, end, kc & 0x1F);
        *p = '\0'; return buf;
    }

    // One-shot modifier (OSM)
    if (kc >= QK_ONE_SHOT_MOD && kc <= QK_ONE_SHOT_MOD_MAX) {
        append_str(&p, end, "OS");
        uint8_t mods = kc & 0x1F;
        if      (mods & MOD_MASK_CTRL)  append_str(&p, end, "C");
        else if (mods & MOD_MASK_SHIFT) append_str(&p, end, "S");
        else if (mods & MOD_MASK_ALT)   append_str(&p, end, "A");
        else if (mods & MOD_MASK_GUI)   append_str(&p, end, "G");
        *p = '\0';
        return buf;
    }

    // Plain basic keycode (0x0000..0x00FF)
    if (kc <= 0x00FF) {
        const char *base = keycode_label_basic(kc);
        if (base) return base;
    }

    // Fallback: 4-digit hex so the user can still identify the key
    buf[0] = '0';
    buf[1] = 'x';
    buf[2] = nibble_to_hex((kc >> 12) & 0x0F);
    buf[3] = nibble_to_hex((kc >>  8) & 0x0F);
    buf[4] = nibble_to_hex((kc >>  4) & 0x0F);
    buf[5] = nibble_to_hex( kc        & 0x0F);
    buf[6] = '\0';
    return buf;
}
