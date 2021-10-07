## mkillewald's Keychron Q1 keymap (rev_0100)

This keymap builds on the keymap by gtg465x but adds a couple more config options.
 
## Features:
- On macOS, F3 opens Mission Control and F4 opens Launchpad without needing to configure shortcuts in System Preferences
- RGB lighting turns off when the computer sleeps
- Caps Lock indicator 

#### USE AT YOUR OWN RISK

## Changelog:

v1.0.2  October 7, 2021
- adapted Grayson Carr's (gtg465x) Caps Lock alphas and dynamic Fn layer RGB routines
- added CAPS_LOCK_INDICATOR_LIGHT_TAB config option to enable/disable lighting Tab with Caps Lock indicator
- added FN_LAYER_COLOR config option to set FN layer static color

v1.0.1  October 7, 2021
- Mission Control and Launchpad custom keycodes are now defined using the VIA user keycodes range so thay can be labeled properly in VIA (adopted change from gtg465x)

v1.0.0  September 30, 2021
- Initial release built upon keymap by Grayson Carr (gtg465x)
- defined Mission Control (F3) and Launchpad (F4) keycodes for macOs
- RGB backlight turns off when computer sleeps
- added Caps Lock indicator lighting both the Caps Lock and Tab LEDs for better effect on non-backlit keycaps
    
