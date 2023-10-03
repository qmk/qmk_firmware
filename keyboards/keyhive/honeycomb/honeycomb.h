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
