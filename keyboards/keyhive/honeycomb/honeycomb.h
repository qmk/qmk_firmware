#pragma once

#include "quantum.h"

#define RED_LED_OFF() gpio_write_pin_high(F6)
#define RED_LED_ON()  gpio_write_pin_low(F6)
#define BLU_LED_OFF() gpio_write_pin_high(F5)
#define BLU_LED_ON()  gpio_write_pin_low(F5)
#define GRN_LED_OFF() gpio_write_pin_high(D1)
#define GRN_LED_ON()  gpio_write_pin_low(D1)

#define SET_LED_OFF     (RED_LED_OFF(); GRN_LED_OFF(); BLU_LED_OFF(); )
#define SET_LED_RED     (RED_LED_ON();  GRN_LED_OFF(); BLU_LED_OFF(); )
#define SET_LED_BLUE    (RED_LED_OFF(); GRN_LED_OFF(); BLU_LED_ON(); )
#define SET_LED_GREEN   (RED_LED_OFF(); GRN_LED_ON();  BLU_LED_OFF(); )
#define SET_LED_YELLOW  (RED_LED_ON();  GRN_LED_ON();  BLU_LED_OFF(); )
#define SET_LED_MAGENTA (RED_LED_ON();  GRN_LED_OFF(); BLU_LED_ON(); )
#define SET_LED_CYAN    (RED_LED_OFF(); GRN_LED_ON();  BLU_LED_ON(); )
#define SET_LED_WHITE   (RED_LED_ON();  GRN_LED_ON();  BLU_LED_ON(); )
