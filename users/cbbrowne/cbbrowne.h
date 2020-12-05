#ifndef USERSPACE
#define USERSPACE

#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif
#include "quantum.h"
#include "config.h"

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#ifndef NO_DEBUG
#define NO_DEBUG
#endif
#ifndef NO_PRINT
#define NO_PRINT
#endif

/* cbbrowne user configuration */

#define randadd 53
#define randmul 181
#define randmod 167

/* Filler to make layering a bit clearer *
 * borrowed from basic keymap            */

#define _______ KC_TRNS
#define _____   KC_NO

#define LEADER_TIMEOUT 300
#ifndef LIGHT_CONFIG_H
#define BACKLIGHT_BREATHING
#endif

#endif

#endif
