#pragma once

#define USE_SERIAL
#define EE_HANDS

#undef TAPPING_TERM
#define TAPPING_TERM 200

#define OLED_DISPLAY_128X64

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D2

#undef OLED_TIMEOUT
#define OLED_TIMEOUT 240000
