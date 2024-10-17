Keymap for adjusting the switch acuation point
==============================================

This keymap provides custom keycodes that allow adjusting the actuation point of
the Topre switches on the FC980C. The keyboard comes with an actuation point
predefined from the factory. This value will never be touched, rather QMK will
store the custom actuation point value separetely so that it can easily be reset
to the factory value.

Actuation point adjustment keycodes
-----------------------------------

- `AP_UP` - makes the actuation point deeper
- `AP_DN` - makes the actuation point shallower
- `AP_RST` - restores the factory actuation point value
- `AP_PRINT_VAL` - types out the current actuation point value (between 0 and
  63, inclusive)
