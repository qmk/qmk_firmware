#pragma once
#define TAPPING_TOGGLE 2

// swap LEDs 1 and 2 - don't need second layer indicator on v0x boards
#undef LED_01
#undef LED_02
#define LED_01 B6
#define LED_02 B1
