#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#ifndef NO_DEBUG
#define NO_DEBUG
#endif
#ifndef NO_PRINT
#define NO_PRINT
#endif

#include "../../config.h"

#define LEADER_TIMEOUT 300
#define BACKLIGHT_BREATHING

/* cbbrowne user configuration */

#define randadd 53
#define randmul 181
#define randmod 167

/* Filler to make layering a bit clearer *
 * borrowed from basic keymap            */

#define _______ KC_TRNS

#endif

