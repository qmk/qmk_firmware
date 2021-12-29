![BareDev Layout Image](https://i.imgur.com/FXye4Hn.png)

# ManoShu's custom layout

Has all the functions of a ABNT TKL keyboard, sans right shift.

Basic media functions also included.

Trying to emulate where notebooks/smaller OEM keyboard put the function key, for this reason the GUI key was moved and it can be used by holding the Caps Lock key.

To not use the new GUI position very often, commonly used GUI + [X] commands are sent using `SEND_STRING()`, `(un)register_code()` and `tap_code()`.

## Why you didn't used `LT(FUNCTIONS, KC_LGUI)` on the GUI/FN key?
Because I don't want rely on the tapping term to determine I will send either KC_HOME or snap the active window to the left.

If there is a better way to solve this, please let me know.