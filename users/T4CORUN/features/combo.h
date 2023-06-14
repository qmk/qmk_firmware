#pragma once
#include "t4corun.h"

enum combos {
  COMDOT_DRGTOG,
  MDOT_SNPTOG,
  KL_SCLN,
  SPCNAV_MB4,
  COMBO_LENGTH
};

//their documentation is so confusing because you don't use COMBO_LEN defining the actions
uint16_t COMBO_LEN = COMBO_LENGTH;
