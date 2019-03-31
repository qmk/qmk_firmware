#pragma once

#include "../../config.h"

#ifdef MANUFACTURER
#undef MANUFACTURER
#endif
#define MANUFACTURER domonkos

#ifdef DESCRIPTION
#undef DESCRIPTION
#endif
#define DESCRIPTION endgame

#ifdef PRODUCT
#undef PRODUCT
#endif
#define PRODUCT DacMan

#define PREVENT_STUCK_MODIFIERS
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#define USE_SERIAL
#define EE_HANDS
