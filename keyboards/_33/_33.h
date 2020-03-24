#pragma once

#include "quantum.h"
#include "led.h"

#define XXX KC_NO

#define LAYOUT_33_BIG_SPACE( \
  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
  K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
  K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
       K31,           K34,                K38       \
) \
{ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09  }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19  }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29  }, \
  { XXX, K31, XXX, XXX, K34, XXX, XXX, XXX, K38, XXX  }  \
}

#define LAYOUT_33_SPLIT_SPACE( \
  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
  K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
  K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
       K31, K32,      K34,      K36,      K38       \
) \
{ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09  }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19  }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29  }, \
  { XXX, K31, K32, XXX, K34, XXX, K36, XXX, K38, XXX  }  \
}
