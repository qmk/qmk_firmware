// Copyright 2023 Florent Linguenheld (@FLinguenheld)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "keymap_us_extended.h"

enum layers {
  _BASE,
  _NUMERIC,
  _ARROWS,
  _MOUSE,
  _ADJUST,
  _FN,
  _LEFT_HAND,
};

enum custom_keys {
  UNICODE = SAFE_RANGE, // Shortcut to write unicodes, see numeric layer

  /* See auto-shift */
  CS_A_GRAVE,
  CS_E_GRAVE,
  CS_U_GRAVE,

  CS_A_CIRCUMFLEX,
  CS_E_CIRCUMFLEX,
  CS_I_CIRCUMFLEX,
  CS_O_CIRCUMFLEX,
  CS_U_CIRCUMFLEX,

  CS_E_DIAERESIS,
  CS_I_DIAERESIS,
  CS_U_DIAERESIS,
  CS_Y_DIAERESIS,
};
