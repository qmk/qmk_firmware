#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// place overrides here
#define TAPPING_TERM 175

#ifdef BACKLIGHT_ENABLE
  #define BACKLIGHT_PIN B5
  #define BACKLIGHT_LEVELS 3
  #define BACKLIGHT_ON_STATE 0
#endif	
	
#endif
