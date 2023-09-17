#include "quantum.h"

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9 },
  { 10, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,     11 },
  { 12, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,     13 },
  { 14,     15,     16,     17,     18,     19,     20,     21,     22,     23 },
}, {
  // LED Index to Physical Position
  { 0,  0  }, { 22,  0 }, { 44,  0 }, { 66,  0 }, { 88,  0 }, { 110,  0 }, { 132,  0 }, { 154,  0 }, { 176,  0 }, { 220,  0  },
  { 0,  16 },                                                                                                     { 220,  16 },
  { 0,  32 },                                                                                                     { 220,  32 },
  { 0,  40 }, { 22, 40 }, { 44, 40 }, { 66, 40 }, { 88, 40 }, { 110, 40 }, { 132, 40 }, { 154, 40 }, { 176, 40 }, { 220,  40 }
}, {
  // LED Index to Flag
  8, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1,                         1,
  1,                         1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };

t_rgb_indicator_matcher g_rgb_indicator_matchers[NUMBER_OF_DYNAMIC_INDICATOR_MATCHERS] = {
    {
        .led_index = 0,
        .led_state = {
            .caps_lock = true,
        },
        .color = {
            .h = 85,
            .s = 255,
            .v = 255
        }
    }
};
