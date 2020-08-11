#pragma once

#if defined MAPPING_BIG
#define LAYOUT_exr(\
  K00, 	 K01, 	K02, K03, K04, K05, K06, K40, 	K41,   K42, \
  K10, 	 K11, 	K12, K13, K14, K15, K16, K50, 	K51,   K52, \
  K20, 	 K21, 	K22, K23, K24, K25, K26, K43, 	K53,   N54,\
  N32, 	 N33,   K34, K30, K31, K36, K44, N45,	N46,   N47 \
)\
LAYOUT(\
  K00, K01, K02, K03, K04, K05, K06, K40, K41,  K42, \
  K10,  K11, K12, K13, K14, K15, K16, K50, K51, K52, \
  K20,    K21, K22, K23, K24, K25, K26, K43,    K53, \
  K30, K31,                K34,            K36, K44 \
)
#else
#define MATRIX_MASKED
#define LAYOUT_exr(\
  K00, 	 K01, 	K02, K03, K04, K05, K06, K40, 	K41,   K42, \
  K10, 	 K11, 	K12, K13, K14, K15, K16, K50, 	K51,   K52, \
  K20, 	 K21, 	K22, K23, K24, K25, K26, K43, 	K53,   N54,\
  N30, 	 N31, 	K32, K33, K30, K44, K34, K35,	N45,   N46 \
)\
LAYOUT_split_space(\
  K00, K01, K02, K03, K04, K05, K06, K40, K41,  K42, \
  K10,  K11, K12, K13, K14, K15, K16, K50, K51, K52, \
  K20,    K21, K22, K23, K24, K25, K26, K43,    K53, \
  K30, XXX, K32,      K33, K34,       K35, XXX, K44 \
)
#endif
