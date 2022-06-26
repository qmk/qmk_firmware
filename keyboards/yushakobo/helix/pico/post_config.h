#pragma once

#if defined(SPLIT_KEYBOARD) /* if use split_common */
#  if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_SPLIT)
#    define RGBLIGHT_SPLIT /* helix hardware need this */
#  endif
#endif
