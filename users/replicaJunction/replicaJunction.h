#pragma once
#include QMK_KEYBOARD_H
#include "rj_keycodes.h"
#include "keycode_aliases.h"
#include "version.h"

#ifdef USER_CAPS_WORD_ENABLE
#    include "features/caps_word.h"
#endif

#ifdef USER_MOUSE_JIGGLE_ENABLE
#    include "features/mouse_jiggle.h"
#endif

#ifdef USER_SECRETS_ENABLE
#    include "features/secrets.h"
#endif

#ifdef USER_SUPER_ALT_TAB_ENABLE
#    include "features/super_alt_tab.h"
#endif
