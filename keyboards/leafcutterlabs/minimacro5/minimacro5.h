/* Copyright 2020 Craig Gardner 
  * 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  * 
  */ 
#pragma once

#include "quantum.h"

#define LAYOUT_ortho_1x5( \
    k01, k02, k03, k04, k05\
  ) { \
    { k01, k02, k03, k04, k05 } \
}

#define LAYOUT LAYOUT_ortho_1x5 
