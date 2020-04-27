#pragma once

#include "quantum.h"

#define RGB_OFF 0,0,0
#define RGB_WHITE 255, 255, 255
#define RGB_RED 255, 0, 0
#define RGB_ORANGE 255, 20, 0
#define RGB_YELLOW 255, 255, 0
#define RGB_GREEN 0, 255, 0
#define RGB_CYAN 0, 255, 255
#define RGB_BLUE 0, 0, 255
#define RGB_PURPLE 255, 0, 255
#define RGB_PINK 255, 20, 20

// set LOCK_INDICATORS to false if not used or if leds are used for custom function
// do not use both, lock indicators will override layer indicator.
#define LOCK_INDICATORS false // indicate capslock, scroll lock etc with rgb led
#define LAYER_INDICATOR true // indicate layer with rgb led, functions may need modification.

#define BRIGHTNESS_LEVELS 10
#define DEFAULT_BRIGHTNESS_LEVEL 5

#define TIMER_TOP 0xFFFFU

bool led_update_kb(led_t led_state);
bool led_update_user(led_t led_state);
void keyboard_pre_init_kb(void);
void led_set_color(uint8_t r, uint8_t g, uint8_t b);
void init_led(void);
uint16_t cie_lightness(uint16_t v);

// variables
uint16_t brightness_level;

enum waffling_layers {
  _BASE1,
  _BASE2,
  _FN1,
  _FN2,
};

// k<row><col>
#define LAYOUT_all( \
    k00, k01, k11, k02, k03, k04, k05, k15, k06, k07, k08, k18, k09, k0a, k1a, \
    k10, k21, k12, k22, k13, k14, k25, k35, k16, k17, k28, k19, k29, k2a, \
    k20, k31, k32, k23, k33, k24, k45, k26, k36, k27, k38, k39, k3a, \
    k30, k40, k41, k42, k43, k34, k44, k55, k46, k37, k47, k48, k49, k4a, \
    k50, k51, k52, k53, k54, k56, k57, k58, k59, k5a  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a}, \
    {k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a}, \
    {k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a}  \
}
