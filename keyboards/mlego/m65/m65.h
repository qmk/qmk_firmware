// Copyright 2020-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#if defined(UNICODEMAP_ENABLE)
enum unicode_names { la = 0, lA, lb, lB, lc, lC, ld, lD, le, lE, lf, lF, lg, lG, lh, lH, li, lI, lj, lJ, lk, lK, ll, lL, lm, lM, ln, lN, lo, lO, lp, lP, lq, lQ, lr, lR, ls, lS, lt, lT, lu, lU, lv, lV, lw, lW, lx, lX, ly, lY, lz, lZ, lc1, lC1, lp1, lP1, lq1, lQ1, ll1, lL1, lk1, lK1, lbo1, lbo2, lbc1, lbc2, ls1, ls2, ra, rA, ra1, rA1, rc, rC, ri, rI, rs, rS, rt, rT, ro, rO, ra2, rA2, ra3, rA3, rx, rX, rv, rV, rb, rB, rn, rN };
#endif

enum layer_names { _QW = 0, _LWR, _RSE, _ADJ };


#ifdef OLED_ENABLE
void user_oled_magic(void);
void render_logo(void);
void clear_screen(void);
void init_timer(void);
#endif

#ifdef RGBLIGHT_ENABLE
void                             set_rgb_layers(layer_state_t);
const rgblight_segment_t* const* my_rgb(void);
void                             set_default_rgb_layers(layer_state_t);
#endif

void toggle_leds(void);
void set_led_toggle(const uint8_t, const bool);

static inline void init_lwr_rse_led(const bool toggle_lwr, const bool toggle_rse) {
#ifdef LED_LWR_PIN
    setPinOutput(LED_LWR_PIN);
    writePin(LED_LWR_PIN, toggle_lwr);
    wait_ms(30);
#endif

#ifdef LED_RSE_PIN
    setPinOutput(LED_RSE_PIN);
    writePin(LED_RSE_PIN, toggle_rse);
    wait_ms(30);
#endif
}

static inline void led_lwr(const bool on) {
#ifdef LED_LWR_PIN
    writePin(LED_LWR_PIN, on);
#endif
}

static inline void led_rse(const bool on) {
#ifdef LED_RSE_PIN
    writePin(LED_RSE_PIN, on);
#endif
}
static inline void led_caps(const bool on) {
#ifdef LED_CAPS_LOCK_PIN
/*
  if (((PRODUCT_ID == 0x6061) || (PRODUCT_ID == 0x6063) ||  (PRODUCT_ID == 0x6062)) && (DEVICE_VER == 0x0002)) {
  writePin(LED_CAPS_LOCK_PIN, on);
} else {
 */
        writePin(LED_CAPS_LOCK_PIN, !on);
/*
    }
 */
#endif
}
