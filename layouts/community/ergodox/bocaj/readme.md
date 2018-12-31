# Bocaj Layout

While I've put my own spin on most things, much of the credit for these ideas belongs to Drashna and/or the people he derived things from. Please see his [layout](../drashna/) and [userspace](../../../../users/drashna/) for lots of ideas and inspiration.

## Layers Overview

* Default
  * Workman
  * Qwerty
  * Windows Workman (swaps GUI and CTRL buttons)
* Lower
  * F1-12 Top Row
  * Grave / Layer Switch macro at Caps Lock position
  * Navigation at QWERTY 'ESDF' position
  * Numpad under right hand
* Adjust
  * Volume Control
  * Mac Lock Macro
  * Make / Reset/ EEPROM keys
  * Default Layer changing keys
  * Diablo Layer
    * Moved shortcuts within left hands reach
    * Macros to spam 1-4 every ~1 second
    * Shift in thumb cluster to prevent pinky fatique

## LEDs Overview

* Used for _LOWER, _ADJUST, and _DIABLO layer indication
* Used for Ctrl/GUI, Shift, and Alt indication when on a default layer

## Wrappers Overview

While it isn't a novel idea, I feel the need to mention it because it really appeals to me as a person that doesn't like repetitive code.

We've all come to know and love the pretty wrapper for Ergodox because it makes for such a beautiful, self-documenting keymap. In this keymap, we are building ontop of the pretty wrapper to wrap our default layers with our keys that aren't unique to the layer.

Now you can wrap your keymap with `LAYOUT_ergodox_pretty_base_wrapper()` and only feed it the alpha keys, having the top, side, bottom, and thumb clusters automatically filled in. If you make a key to any of the top, side, bottom, or thumb cluster keys, it will propegate to all layers that have this wrapper, or have KC_TRNS keycodes in the same location
