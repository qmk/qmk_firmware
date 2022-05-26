// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef ENCODER_DEBUG_PIN
#  define DEBUG_PIN_ON()    writePinHigh(ENCODER_DEBUG_PIN)
#  define DEBUG_PIN_OFF()   writePinLow(ENCODER_DEBUG_PIN)
#  define DEBUG_PIN_WAIT(n) wait_cpuclock(n);
#else
#  define DEBUG_PIN_ON()
#  define DEBUG_PIN_OFF()
#  define DEBUG_PIN_WAIT(n)
#endif

#include QMK_KEYBOARD_H

#define TAP_CODE(x) if (is_keyboard_master()) { tap_code(x); }

/* weak reference */ __attribute__((weak))
int get_encoder_over_count(void);

bool encoder_update_user(uint8_t index, bool clockwise) {
#ifdef AVR_UART_TX
    static bool debug_log_init = false;
    if (!debug_log_init) {
        DEBUG_UART_LOG_INIT(0);
        debug_log_init = true;
    }
#endif
    DEBUG_PIN_ON();
#ifndef ENCODER_DETECT_OVER_SPEED
    switch (index) {
    /* Left side encoder */
    case 0: TAP_CODE(clockwise ? KC_LEFT : KC_RGHT); break;
    /* Right side encoder */
    case 1: TAP_CODE(clockwise ? KC_DOWN : KC_UP); break;
    }
#else
    // Is there a get_encoder_over_count() in quantum/encoder.c
    if (get_encoder_over_count != NULL) {
#    ifdef AVR_UART_TX
        int enc_over = get_encoder_over_count();
        if (enc_over != 0) {
            DEBUG_UART_LOG(0x80); DEBUG_UART_LOG(enc_over);
        }
#    endif
    }
    switch (index) {
    case 0: TAP_CODE(clockwise ? KC_A : KC_B); break;
    case 1: TAP_CODE(clockwise ? KC_C : KC_D); break;
    case 2: TAP_CODE(clockwise ? KC_E : KC_F); break;
    case 3: TAP_CODE(clockwise ? KC_G : KC_H); break;
    }
#endif
    DEBUG_PIN_OFF();
    return true;
}
