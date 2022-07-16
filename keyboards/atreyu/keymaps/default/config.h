#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

// place overrides here
#ifdef TAPPING_TERM
#undef TAPPING_TERM
#define TAPPING_TERM 150
#endif

#define RETRO_TAPPING

#endif
