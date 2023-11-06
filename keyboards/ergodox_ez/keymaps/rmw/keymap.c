#include QMK_KEYBOARD_H
#include "version.h"

#define LONGPRESS_DELAY 180
#define LAYER_TOGGLE_DELAY 350

#ifdef MACOSX
#include "keymap-mac.c"
#endif

#ifdef WINDOWS
#include "keymap-win.c"
#endif
