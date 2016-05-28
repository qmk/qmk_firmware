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
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D \
    ) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D } \
}

void matrix_init_user(void);
void matrix_scan_user(void);
bool process_action_user(keyrecord_t *record);
void led_set_user(uint8_t usb_led);

#endif
