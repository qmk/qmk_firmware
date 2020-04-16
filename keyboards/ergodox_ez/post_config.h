#pragma once

#if !defined(ERGODOX_LED_15) && !defined(ERGODOX_LED_30)
// if no value is defined, assume previous behavior
// #    define ERGODOX_LED_15
// #    define ERGODOX_LED_30
#    define ERGODOX_LED_15_MIRROR
#endif

#if (defined(ERGODOX_LED_30) + defined(ERGODOX_LED_15) + defined(ERGODOX_LED_15_MIRROR)) != 1
#    error "You must only define one of the ERGODOX_LED options."
#endif

#ifdef ERGODOX_LED_30
// If using 30 LEDs, then define that many
#    define RGBLED_NUM 30  // Number of LEDs
#else
// If not, then only define 15
#    define RGBLED_NUM 15  // Number of LEDs
#endif
