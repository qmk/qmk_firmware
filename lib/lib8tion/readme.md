# FastLED lib8tion Library

Moddified from [Version 3.7.8](https://github.com/FastLED/FastLED/tree/3.7.8/src/lib8tion) to be C compliant.

## Changes

### `random8.h`

* Update function prototypes from `x()` to `x(void)`
* Rename `uint8_t random8(uint8_t lim)` to `uint8_t random8_max(uint8_t lim)`
* Rename `uint8_t random8(uint8_t min, uint8_t lim)` to `uint8_t random8_min_max(uint8_t min, uint8_t lim)`
* Rename `uint8_t random16(uint8_t lim)` to `uint8_t random16_max(uint8_t lim)`
* Rename `uint8_t random16(uint8_t min, uint8_t lim)` to `uint8_t random16_min_max(uint8_t min, uint8_t lim)`

### `scale8.h`

* Remove `void nscale8_video_LEAVING_R1_DIRTY(uint8_t &i, fract8 scale)`
* Remove `void nscale8x3(uint8_t &r, uint8_t &g, uint8_t &b, fract8 scale)`
* Remove `void nscale8x3_video(uint8_t &r, uint8_t &g, uint8_t &b, fract8 scale)`
* Remove `void nscale8x2(uint8_t &i, uint8_t &j, fract8 scale)`
* Remove `void nscale8x2_video(uint8_t &i, uint8_t &j, fract8 scale)`

### `trig8.h`

* Add `uint8_t atan2_8(int16_t dy, int16_t dx)`
* Change `b_m16_interleave` to static

### `types.h`

* Remove `namespace.h` include
* Remove `FASTLED_NAMESPACE_*`

### `lib8tion.cpp`

* Rename unit to `lib8tion.c`
* Remove extern c
* Remove `FastLED.h` include
* Remove `FASTLED_NAMESPACE_*`

### `lib8tion.h`

* Remove extern c
* Remove `FastLED.h` include
* Remove `__INC_LED_SYSDEFS_H` check
* Removed forced in lining for lib8tion functions
* Remove default arg from `uint8_t squarewave8( uint8_t in, uint8_t pulsewidth)`
* Remove `WaveformGenerators`, `FractionalTypes`, `Timekeeping` sections
* Remove `FASTLED_NAMESPACE_*`
