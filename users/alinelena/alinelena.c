// Copyright 2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "alinelena.h"
#include "version.h"

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
static const char bdate[] = QMK_BUILDDATE;
static const char hash[] = QMK_GIT_HASH;

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
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case _LWR:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RSE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJ:
            oled_write_ln_P(PSTR("ADJ"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
#    ifdef UNICODE_COMMON_ENABLE
    oled_write_P(PSTR("unicode: "), false);
    switch (get_unicode_input_mode()) {
      case UNICODE_MODE_LINUX:
        oled_write_ln_P(PSTR("Linux"), false);
        break;
      case UNICODE_MODE_MACOS:
        oled_write_ln_P(PSTR("apple"), false);
        break;
      case UNICODE_MODE_WINDOWS:
        oled_write_ln_P(PSTR("windows"), false);
        break;
      case UNICODE_MODE_WINCOMPOSE:
        oled_write_ln_P(PSTR("windows c"), false);
        break;
      case UNICODE_MODE_BSD:
        oled_write_ln_P(PSTR("bsd"), false);
        break;
      case UNICODE_MODE_EMACS:
        oled_write_ln_P(PSTR("emacs"), false);
        break;
      default:
        oled_write_ln_P(PSTR("not supported"), false);
    }
#    endif
#    ifdef WPM_ENABLE
    oled_write_P(PSTR("wpm: "), false);
    uint8_t wpm = get_current_wpm();
    oled_write_ln_P(wpm != 0 ? get_u8_str(wpm, ' ') : PSTR("   "), false);
#    endif
    oled_write_P(PSTR(hash), false);
}

void init_timer(void) {
    oled_logo_timer = timer_read32();
};

void render_logo(void) {
    oled_write_raw_P(m65_logo, sizeof(m65_logo));
    oled_write_ln_P(PSTR(bdate), false);
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

