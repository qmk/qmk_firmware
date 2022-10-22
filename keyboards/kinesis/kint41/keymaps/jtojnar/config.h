#pragma once

// Make keypad button work as both a modifier and single-tap toggle button.
#define TAPPING_TOGGLE 1

// The default KinT layout does not support keypad,
// so it uses the keypad LED indicator for Compose status.
// Since we do support keypad, let’s restore the LED indication.
// We will need to control the LED explicitly, though.
#undef LED_COMPOSE_PIN

// I redefined Caps Lock to Compose key in my OS
// so I can just use the indicator for Compose status.
#define LED_COMPOSE_PIN LINE_PIN12
