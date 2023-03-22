// Copyright 2022 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

enum layer_names {
    _QW = 0,
    _LWR,
    _RSE,
    _ADJ
};

#ifdef OLED_ENABLE
void user_oled_magic(void);
void render_logo(void);
void clear_screen(void);
void init_timer(void);
#endif

#ifdef RGBLIGHT_ENABLE
void set_rgb_layers(layer_state_t);
const rgblight_segment_t * const*  my_rgb(void);
void set_default_rgb_layers(layer_state_t);
#endif


void toggle_leds(void);
void set_led_toggle(const uint8_t, const bool);

static inline void led_lwr(const bool on) {
#ifdef LED_NUM_LOCK_PIN
    writePin(LED_NUM_LOCK_PIN, !on);
#endif
}

static inline void led_rse(const bool on) {
#ifdef LED_SCROLL_LOCK_PIN
    writePin(LED_SCROLL_LOCK_PIN, !on);
#endif
}
static inline void led_caps(const bool on) {
#ifdef LED_CAPS_LOCK_PIN
    if (((PRODUCT_ID == 0x6061) || (PRODUCT_ID == 0x6063)) && (DEVICE_VER == 0x0002)) {
        writePin(LED_CAPS_LOCK_PIN, on);
    } else {
        writePin(LED_CAPS_LOCK_PIN, !on);
    }
#endif
}
