#pragma once

#if defined(RGB_MATRIX_ENABLE)
# include "rgb_matrix_config.h"
#endif

/* This file is designed to have settings that apply to all my keyboards */

/* Turn off settings we won't use*/
#define NO_ACTION_ONESHOT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

/* Clear out variables that we may be setting */
#if defined(USB_POLLING_INTERVAL_MS)
# undef USB_POLLING_INTERVAL_MS
#endif

#if defined(TAPPING_TERM)
# undef TAPPING_TERM
#endif

/* Common configuration across all keyboards */
#define USB_POLLING_INTERVAL_MS 1

#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define QUICK_TAP_TERM 120
#define QUICK_TAP_TERM_PER_KEY

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#if defined(MOUSEKEY_ENABLE)
# define MOUSEKEY_INTERVAL 12
# define MOUSEKEY_MAX_SPEED 6
# define MOUSEKEY_TIME_TO_MAX 50
# define MOUSEKEY_DELAY 20
#endif //MOUSEKEY_ENABLE

#if defined(COMBO_ENABLE)
# define EXTRA_SHORT_COMBOS
//# define COMBO_MUST_PRESS_IN_ORDER
# define COMBO_TERM 50
#endif //COMBO_ENABLE

#if defined(AUTOMOUSE_ENABLED)
# define POINTING_DEVICE_AUTO_MOUSE_ENABLE
# define AUTO_MOUSE_TIME 300
#endif //AUTOMOUSE_ENABLED