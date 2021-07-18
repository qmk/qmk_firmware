#pragma once

#include "quantum.h"

#define RED_LED_OFF() writePinHigh(F6)
#define RED_LED_ON()  writePinLow(F6)
#define BLU_LED_OFF() writePinHigh(F5)
#define BLU_LED_ON()  writePinLow(F5)
#define GRN_LED_OFF() writePinHigh(D1)
#define GRN_LED_ON()  writePinLow(D1)

#define SET_LED_OFF     (RED_LED_OFF(); GRN_LED_OFF(); BLU_LED_OFF(); )
#define SET_LED_RED     (RED_LED_ON();  GRN_LED_OFF(); BLU_LED_OFF(); )
#define SET_LED_BLUE    (RED_LED_OFF(); GRN_LED_OFF(); BLU_LED_ON(); )
#define SET_LED_GREEN   (RED_LED_OFF(); GRN_LED_ON();  BLU_LED_OFF(); )
#define SET_LED_YELLOW  (RED_LED_ON();  GRN_LED_ON();  BLU_LED_OFF(); )
#define SET_LED_MAGENTA (RED_LED_ON();  GRN_LED_OFF(); BLU_LED_ON(); )
#define SET_LED_CYAN    (RED_LED_OFF(); GRN_LED_ON();  BLU_LED_ON(); )
#define SET_LED_WHITE   (RED_LED_ON();  GRN_LED_ON();  BLU_LED_ON(); )

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k13, k14, k15, k16, \
  k09, k10, k11, k12, \
  k05, k06, k07, k08, \
  k01, k02, k03, k04  \
) \
{ \
	{ k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16 } \
}
