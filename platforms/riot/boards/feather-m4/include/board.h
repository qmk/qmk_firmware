#pragma once

#include_next <board.h>

#undef LED0_PIN
#define LED0_PIN            GPIO_PIN(PA, 23)

#undef LED_PORT
#define LED_PORT            PORT->Group[PA]

#undef LED0_MASK
#define LED0_MASK           (1 << 23)
