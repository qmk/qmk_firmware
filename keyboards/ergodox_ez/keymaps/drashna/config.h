
#include "../../config.h"



// make this easy to toggle behavior, so that it can be more easily toggled
#define LAYER_UNDERGLOW_LIGHTING  

#ifdef LAYER_UNDERGLOW_LIGHTING
#undef RGBLIGHT_ANIMATIONS
#endif