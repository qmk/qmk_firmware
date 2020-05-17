#pragma once

// swap LED_01 and LED_02 so actual LED_01 pin acts as numlock indicator
#undef LED_01
#undef LED_02
#define LED_01 B6
#define LED_02 B1
