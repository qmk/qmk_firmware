// Taken from https://github.com/Adam13531/qmk_firmware/blob/master/keyboards/crkbd/keymaps/adam/customkeys.h

#pragma once

#include QMK_KEYBOARD_H

enum custom_keycodes {
  // Switch app: cmd+tab on Mac, alt+tab on Windows
  SW_APP = SAFE_RANGE,
  // Switch window: cmd+` (just for Mac since Windows doesn't have something like this)
  SW_WIN,
  // Close window: cmd+w on Mac, ctrl+w on Windows
  CLS_WIN,
  // Mac/Windows variants for common commands
  MW_UNDO,
  MW_CUT,
  MW_COPY,
  MW_PSTE,
  MW_REDO,
  CT_PIPE,
  SEL_WRD,
  SEL_SRCH,
  ARROW,
  GRAVE,
  // Norwegian keys
  CT_AA,
  CT_AE,
  CT_OE,
  CT_F
};
