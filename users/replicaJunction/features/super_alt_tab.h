#pragma once
#include QMK_KEYBOARD_H
#include "rj_keycodes.h"

#ifndef USER_SUPER_ALT_TAB_TIMEOUT
#    define USER_SUPER_ALT_TAB_TIMEOUT 500
#endif

void matrix_scan_super_alt_tab(void);

bool process_record_super_alt_tab(uint16_t keycode, const keyrecord_t *record);
