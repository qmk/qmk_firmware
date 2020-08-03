#pragma once

#define PERMISSIVE_HOLD // https://docs.qmk.fm/#/feature_advanced_keycodes?id=permissive-hold

// Enable single-color backlighting
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 5
#define BREATHING_PERIOD 4

#ifdef LOCKING_SUPPORT_ENABLE
#   undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#   undef LOCKING_RESYNC_ENABLE
#endif

#define NO_ACTION_ONESHOT
