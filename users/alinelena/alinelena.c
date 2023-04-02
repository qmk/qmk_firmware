// Copyright 2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "alinelena.h"

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_lwr_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_CYAN});
const rgblight_segment_t PROGMEM my_rse_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});
const rgblight_segment_t PROGMEM my_adj_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_qwerty_layer, my_lwr_layer, my_rse_layer, my_adj_layer);

#endif

#ifdef OLED_ENABLE

static uint32_t           oled_logo_timer = 0;
static bool               clear_logo      = true;
static const char PROGMEM m65_logo[]      = {0x92, 0x92, 0x93, 0x94, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x92, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB2, 0x92, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0};

#endif

#ifdef RGBLIGHT_ENABLE

__attribute__((weak)) layer_state_t default_layer_state_set_user(layer_state_t state) {
    set_default_rgb_layers(state);
    return state;
}

void set_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LWR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));
}

__attribute__((weak)) void set_default_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
}

const rgblight_segment_t* const* my_rgb(void) {
    return my_rgb_layers;
}

void init_rgb_layers(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb();
}
#endif

#ifdef OLED_ENABLE

void user_oled_magic(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QW:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LWR:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RSE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
#    ifdef UNICODE_COMMON_ENABLE
    oled_write_P(PSTR("\nunicode: "), false);
    switch (get_unicode_input_mode()) {
      case UNICODE_MODE_LINUX:
        oled_write_P(PSTR("Linux"), false);
        break;
      case UNICODE_MODE_MACOS:
        oled_write_P(PSTR("apple"), false);
        break;
      case UNICODE_MODE_WINDOWS:
        oled_write_P(PSTR("windows"), false);
        break;
      case UNICODE_MODE_WINCOMPOSE:
        oled_write_P(PSTR("windows c"), false);
        break;
      case UNICODE_MODE_BSD:
        oled_write_P(PSTR("bsd"), false);
        break;
      case UNICODE_MODE_EMACS:
        oled_write_P(PSTR("emacs"), false);
        break;
      default:
        oled_write_ln_P(PSTR("not supported"), false);
    }
#    endif

#    ifdef WPM_ENABLE
    oled_write_P(PSTR("\nwpm: "), false);
    uint8_t wpm = get_current_wpm();
    oled_write_P(wpm != 0 ? get_u8_str(wpm, ' ') : PSTR("   "), false);
#    endif
}

void init_timer(void) {
    oled_logo_timer = timer_read32();
};

void render_logo(void) {
    oled_write_P(m65_logo, false);
}

void clear_screen(void) {
    if (clear_logo) {
        for (uint8_t i = 0; i < OLED_DISPLAY_HEIGHT; ++i) {
            for (uint8_t j = 0; j < OLED_DISPLAY_WIDTH; ++j) {
                oled_write_raw_byte(0x0, i * OLED_DISPLAY_WIDTH + j);
            }
        }
        clear_logo = false;
    }
}

__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

#    define SHOW_LOGO 5000
__attribute__((weak)) bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if ((timer_elapsed32(oled_logo_timer) < SHOW_LOGO)) {
        render_logo();
    } else {
        clear_screen();
        user_oled_magic();
    }
    return false;
}

#endif

#ifdef UNICODEMAP_ENABLE
const uint32_t PROGMEM unicode_map[] = {
    [la]   = 0x03B1,  // α
    [lA]   = 0x0307,  //
    [lb]   = 0x03B2,  // β
    [lB]   = 0x2229,  // ∩
    [lc]   = 0x03C7,  // χ
    [lC]   = 0x2282,  // ⊂
    [ld]   = 0x03B4,  // δ
    [lD]   = 0x2202,  // ∂
    [le]   = 0x03B5,  // ε
    [lE]   = 0x2107,  // ℇ
    [lf]   = 0x03C6,  // φ
    [lF]   = 0x03C8,  // ψ
    [lg]   = 0x03B3,  // γ
    [lG]   = 0x0393,  // Γ
    [lh]   = 0x210F,  // ℏ
    [lH]   = 0x1D4D7, // 𝓗
    [li]   = 0x222B,  // ∫
    [lI]   = 0x222E,  // ∮
    [lj]   = 0x2208,  // ∈
    [lJ]   = 0x2209,  // ∉
    [lk]   = 0x03F0,  // ϰ
    [lK]   = 0x2206,  // ∆
    [ll]   = 0x03BB,  // λ
    [lL]   = 0x039B,  // Λ
    [lm]   = 0x03BC,  // μ
    [lM]   = 0x2218,  // ∘
    [ln]   = 0x03B7,  // η
    [lN]   = 0x222A,  // ∪
    [lo]   = 0x221E,  // ∞
    [lO]   = 0x2297,  // ⊗
    [lp]   = 0x03C0,  // π
    [lP]   = 0x220F,  // ∏
    [lq]   = 0x03C3,  // σ
    [lQ]   = 0x03D5,  // ϕ
    [lr]   = 0x03C1,  // ρ
    [lR]   = 0x2207,  // ∇
    [ls]   = 0x2211,  // ∑
    [lS]   = 0x2A0B,  // ⨋
    [lt]   = 0x03D1,  // ϑ
    [lT]   = 0x03B8,  // θ
    [lu]   = 0x03C4,  // τ
    [lU]   = 0x2102,  // ℂ
    [lv]   = 0x03BD,  // χ
    [lV]   = 0x2283,  // ⊃
    [lw]   = 0x03C9,  // ω
    [lW]   = 0x03A9,  // Ω
    [lx]   = 0x03BE,  // ξ
    [lX]   = 0x039E,  // Ξ
    [ly]   = 0x211d,  // ℝ
    [lY]   = 0x2124,  // ℤ
    [lz]   = 0x03B6,  // ζ
    [lZ]   = 0x2221,  // ∡
    [lc1]  = 0x2248,  // ≈
    [lC1]  = 0x2249,  // ≉
    [lp1]  = 0x00B1,  // ±
    [lP1]  = 0x2213,  // ∓
    [lq1]  = 0x00D7,  // ×
    [lQ1]  = 0x22C5,  // ⋅
    [ll1]  = 0x1D53C, // 𝔼
    [lL1]  = 0x212b,  // Å
    [lk1]  = 0x221D,  // ∝
    [lK1]  = 0x2112,  // ℒ
    [lbo1] = 0x22DC,  // ⋜
    [lbo2] = 0x2260,  // ≠
    [lbc1] = 0x22DD,  // ⋝
    [lbc2] = 0x2245,  // ≅
    [ls1]  = 0x2261,  // ≡
    [ls2]  = 0x2262,  // ≢
    [ra]   = 0x0103,  // ă
    [rA]   = 0x0102,  // Ă
    [ra1]  = 0x00E2,  // â
    [rA1]  = 0x00C2,  // Â
    [rx]   = 0x00E7,  // ç
    [rX]   = 0x00C7,  // Ç
    [ri]   = 0x00EE,  // î
    [rI]   = 0x00CE,  // Î
    [rs]   = 0x0219,  // ș⊄
    [rS]   = 0x0218,  // Ș
    [rt]   = 0x021B,  // ț
    [rT]   = 0x021A,  // Ț
    [rc]   = 0x2284,  // ⊄
    [rC]   = 0x2286,  // ⊆
    [rv]   = 0x2285,  // ⊅
    [rV]   = 0x2287,  // ⊇
    [rb]   = 0x2227,  // ∧
    [rB]   = 0x22BC,  // ⊼
    [rn]   = 0x2228,  // ∨
    [rN]   = 0x22BB,  // ⊻
};

#endif
