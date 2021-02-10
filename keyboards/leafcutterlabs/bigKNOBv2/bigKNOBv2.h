#pragma once

#include "quantum.h"

#define LAYOUT_ortho_1x5( \
    k01, k02, k03, k04, k05 \
  ) { \
    { k01, k02, k03, k04, k05 } \
}

#define LAYOUT LAYOUT_ortho_1x5 
