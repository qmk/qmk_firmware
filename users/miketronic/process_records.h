// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include "miketronic.h"


bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
uint16_t copy_paste_timer;

enum custom_keycodes {
  WM = QK_USER,
  QW,
  MAKE,
  VERSION,
  M01,
  M02,
  M03,
  M04,
  M05,
  M06, 
  M07,
  M08,
  M09,
  M10,
  M11, 
  M12,
  RGB1,
  RGB2,	
  RGB3,
  RGB4,
  RGB5,
  IENTER,
  PRN,
  BRACES,
  CCCV
};
