#ifndef KC60_H
#define KC60_H

#include "matrix.h"
#include "keymap_common.h"
#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif
#include <avr/io.h>
#include <stddef.h>

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a multi-dimensional array
#define KEYMAP( \
    K00, K01, K02, K03, K04, \
    K10, K11, K12, K13, K14, \
    K20, K21, K22, K23, K24, \
    K30, K31, K32, K33, K34, \
    K40, K41, K42, K43, K44 \          
    ) { \
  { K00, K01, K02, K03, K04 }, \
  { K10, K11, K12, K13, K14 }, \
  { K20, K21, K22, K23, K24 }, \
  { K30, K31, K32, K33, K34 }, \
  { K40, K41, K42, K43, K44 }  \
}

void matrix_init_user(void);
void matrix_scan_user(void);
bool process_action_user(keyrecord_t *record);
void led_set_user(uint8_t usb_led);

#endif
