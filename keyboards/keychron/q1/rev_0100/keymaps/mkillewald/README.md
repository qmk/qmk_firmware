## mkillewald's Keychron Q1 keymap (ANSI rev_0100) v1.0.2

This keymap builds on the keymap by Grayson Carr (gtg465x) but adds a couple more config options.
 
## Features:
- On macOS, F3 opens Mission Control and F4 opens Launchpad without needing to configure shortcuts in System Preferences
- RGB lighting turns off when the computer sleeps
- Caps Lock RGB indicator
    - the Caps Lock key will light when Caps Lock is enabled. RGB mode must be toggled on. If you don't want an RGB mode active, you can turn the brightness all the way off and the Caps Lock indicator will remain at full brightness.
 
    - Some options are available by setting the following defines in config.h 
        - #define CAPS_LOCK_INDICATOR_COLOR [color] to set the backlight color used for the indicator when Caps Lock is enabled
        - #define CAPS_LOCK_INDICATOR_LIGHT_ALPHAS to light all the alpha keys when Caps Lock is enabled
        - #define CAPS_LOCK_INDICATOR_LIGHT_TAB to light the TAB key when Caps Lock is enabled (this is useful with non backlit keycaps/legends)

- Dynamic Fn layer RGB indicator
    - When the Fn key is held down, any keys defined on the Fn layer in VIA will be highlighted with RGB backlight
    
    - Some options are available by setting the following defines in config.h
        - #define FN_LAYER_COLOR [color] to set a static color for defined keys
        - #define FN_LAYER_TRANSPARENT_KEYS_OFF to turn off RGB for keys with no definition

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
    
