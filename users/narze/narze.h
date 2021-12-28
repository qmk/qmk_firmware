#pragma once

#include "quantum.h"
#include "eeconfig.h"
#include "keymap_colemak.h"

#ifdef COMBO_ENABLE
#   include "superduper.h"
#endif

#define HPR_ESC ALL_T(KC_ESC)
#define SFT_ENT SFT_T(KC_ENT)
#define ALT_COLN RALT_T(KC_F13) // Remap F13 to Colon in software (eg. Keyboard Maestro)
