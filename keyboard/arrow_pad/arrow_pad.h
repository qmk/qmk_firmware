#ifndef ARROW_PAD_H
#define ARROW_PAD_H

#include "matrix.h"
#include "keymap_common.h"
#ifdef BACKLIGHT_ENABLE
	#include "backlight.h"
#endif
#include <avr/io.h>
#include <stddef.h>

#define KEYMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42,      \
    K50, K51, K52, K53  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03  }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13  }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23  }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33  }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_NO     }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53  }  \
}


void matrix_init_user(void);
void matrix_scan_user(void);
bool process_action_user(keyrecord_t *record);
void led_set_user(uint8_t usb_led);

#endif
