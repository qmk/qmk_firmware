#ifndef LEDBBTWI_H_
#define LEDBBTWI_H_

//For keyboards which use I2C to control LEDs, such as the Ergodox EZ Shine

#ifdef RGBW_BB_TWI

#include "rgblight_types.h"

void ledbbtwi_setleds(LED_TYPE *ledarray, uint16_t leds);

#endif //RGBW_BB_TWI

#endif
