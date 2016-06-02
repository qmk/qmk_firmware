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
    KM_ESC, KM_TAB, KM_BSL, KM_ARR, \
    KM_NUM, KM_FSL, KM_AST, KM_MIN, \
    KM___7, KM___8, KM___9, ___PLS, \
    KM___4, KM___5, KM___6, KM_PLS, \
    KM___1, KM___2, KM___3, ___ENT, \
    KM___0, _____0, KM_DOT, KM_ENT  \
) { \
    { KM_ESC, KM_TAB, KM_BSL, KM_ARR, KM___7, KM___8, KM___9, KM_PLS, KM___1, KM___2, KM___3, }, \
    { KM_NUM, KM_FSL, KM_AST, KM_MIN, KM___4, KM___5, KM___6, KM_ENT, KC_NO,  KM___0, KM_DOT, }, \
}


void matrix_init_user(void);
void matrix_scan_user(void);
bool process_action_user(keyrecord_t *record);
void led_set_user(uint8_t usb_led);
void backlight_init_ports(void);

#endif
