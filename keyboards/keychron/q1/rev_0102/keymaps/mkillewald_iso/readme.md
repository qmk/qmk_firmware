## mkillewald's Keychron Q1 keymap (ISO rev_0102) v1.0.4

This keymap builds on the keymap by Grayson Carr (gtg465x) but adds a couple options.

## Features:
- On macOS, F3 opens Mission Control and F4 opens Launchpad without needing to configure shortcuts in System Preferences
- RGB lighting turns off when the computer sleeps
- Caps Lock RGB indicator
    - the Caps Lock key will light when Caps Lock is enabled with the following options:
        - #define CAPS_LOCK_INDICATOR_COLOR [color] in config.h to set the backlight color used for the indicator when Caps Lock is enabled (default: red)
        - Fn+Z will toggle lighting the TAB key when Caps Lock is enabled. This is useful with non backlit keycaps/legends. (default: off)
        - Fn+X will toggle lighting all the alpha keys when Caps Lock is enabled. (default: off)

- Dynamic Fn layer RGB indicator
    - When the Fn key is held down, any keys defined on the Fn layer in this firmware or in VIA will be highlighted with the following options:
        - #define FN_LAYER_COLOR [color] in config.h to set a static color for defined keys (default: orange)
        - Fn+C will toggle turning off RGB for keys with no definition (default: RGB off)
        - Fn+V will toggle lighting the defined Fn layer keys with the static color set with FN_LAYER_COLOR (default: static color off)

- All custom keycodes can be moved to different keys in VIA by using the ANY key with the following keycodes:
    - USER00 (default: F3) macOS Mission Control
    - USER01 (default: F4) macOS Launchpad
    - USER02 (default: Fn+Z) Caps Lock light Tab toggle
    - USER03 (default: Fn+X) Caps Lock light alphas toggle
    - USER04 (default: Fn+C) Fn layer non-defined keys RGB toggle
    - USER05 (default: Fn+V) Fn layer defined keys static color toggle

RGB must be toggled on for all indicators to function. If you do not want an RGB mode active but still want the indicators, toggle RGB on and turn the brightness all the way off. The indicators will remain at full brightness.

Please make sure to save any customizations you have made in VIA to a .json file before flashing the firmware. Sometimes it has been necessary to re-apply those changes in VIA after flashing the firmware. If that is the case, you will most likely need to manually add the USER00 through USER05 custom keycodes after loading your customizations from the saved .json file. Then re-save a new .json file which will have your previous customizations and the custom keycodes for future use as needed.
    
#### USE AT YOUR OWN RISK

## Changelog:

v1.0.4  October 9, 2021
- Caps Lock and Fn layer toggles are now stored in eeprom so settings will remain when Q1 is unplugged

v1.0.3  October 8, 2021
- now using keycode toggles instead of preprocessor directives to set the various Caps Lock and Fn Layer RGB lighting options. This allows for setting the options from user space without having to recompile.

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
