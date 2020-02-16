#pragma once

/* split keyboard setup */
#define MASTER_LEFT             /* LEFT or RIGHT (or EE_HANDS) */

#undef RGBLED_NUM
#undef RGBLED_SPLIT
#define RGBLED_NUM (42 + 8)
#define RGBLED_SPLIT { 21 + 4, 21 + 4 }

#define RGBLIGHT_EFFECT_STATIC_GRADIENT
