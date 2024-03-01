#pragma once

#include "quantum.h"

/* Indicator LEDs Config  */
// #define CAPSLOCK_LED_PIN A15

enum custom_keycodes {
#ifdef VIA_ENABLE
//    KC_USB = QK_USER,
    KC_USB = QK_KB_0,
#else
    KC_USB = SAFE_RANGE,
#endif
  KC_MAC,
  KC_WIN,
  KC_RESET,
  GU_TOG
};
