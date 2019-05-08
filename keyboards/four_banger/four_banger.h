#ifndef KB_H
#define KB_H

#include "quantum.h"

#define LAYOUT_ortho_2x2( \
  K00, K01, \
  K10, K11  \
) { \
  { K00, K01 }, \
  { K10, K11 }  \
}

#endif
