#ifndef _fancy_lighting_h
#define _fancy_lighting_h
#ifdef RGBLIGHT_ENABLE

#include "xtonhasvim.h"

extern uint8_t user_rgb_mode;
extern LED_TYPE shadowed_led[];
void keyboard_has_heat(void);

extern float keyboard_heat;
void start_firey_return(void);

#endif //_fancy_lighting_h

enum xtonhasvim_rgbmodes {
  BREATH_FIRE = 1,
  FADE_BACK
};

#endif //RGBLIGHT_ENABLE
