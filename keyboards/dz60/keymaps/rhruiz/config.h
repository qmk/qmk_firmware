#pragma once

#include "../../config.h"

// help for fast typist+dual function keys?
#define PERMISSIVE_HOLD

// Enable key for bootmagic lite.
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// mouse settings
#define MOUSEKEY_DELAY 100
#define MOUSEKEY_INTERVAL 30
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_TIME_TO_MAX 20

#ifdef MANUFACTURER
#    undef MANUFACTURER
#endif

#ifdef PRODUCT
#    undef PRODUCT
#endif

#ifdef DESCRIPTION
#    undef DESCRIPTION
#endif

#define MANUFACTURER rhruiz
#define PRODUCT rhruiz one
#define DESCRIPTION rhruiz one keyboard
