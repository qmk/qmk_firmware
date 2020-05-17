#pragma once

// Don't actually have a v1.0 PCB yet
// swap LED_01 and LED_02 so actual LED_01 pin acts as numlock indicator
#undef LED_01
#undef LED_02
#define LED_01 B6
#define LED_02 B1
