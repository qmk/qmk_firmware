#pragma once

#include "quantum.h"

#define LAYOUT_ortho_2x3_2x4_2x3(\
	K00, K01, K02, K06, K07, K08, K09, K14, K15, K16,\
    K03, K04, K05, K10, K11, K12, K13, K17, K18, K19,\
      \
) \
  { \
    { K00,K01,K02,K06,K07,K08,K09,K14,K15,K16,} \
    { K03,K04,K05,K10,K11,K12,K13,K17,K18,K19,} \
	  \
}
