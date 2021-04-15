#pragma once
#include "id-b3.h"

#ifdef DICE_ROLLER_ENABLE
//enumerate macros
enum custom_keycodes {
  ROLL_D20 = SAFE_RANGE,
  ROLL_D100,
  ROLL_D10,
  ROLL_D8,
  ROLL_D12,
  ROLL_D6,
  ROLL_D4,
  ROLL_D3,
  PM_SCROLL,
};
#endif