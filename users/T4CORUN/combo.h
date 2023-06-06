#pragma once
#include "T4CORUN.h"

enum combos {
  COMDOT_DRGTOG,
  MDOT_SNPTOG,

  MB2MB3_DRGTOG,
  MB1MB3_SNPTOG,

  SPCNAV_MB4,
  COMBO_LENGTH
};

//their documentation is so confusing because you don't use COMBO_LEN defining the actions
uint16_t COMBO_LEN = COMBO_LENGTH;
