## Keychron Q2 ANSI STM32L432 ENC11 (with knob) Keymap v1.0.0

## Features:
- Retains Keychron factory keycodes for Mission Control, Launchpad, Siri, Cortana, Task View, File Explorer, and others. 

- Caps Word enabled with RGB indicator ([https://docs.qmk.fm/#/feature_caps_word](https://docs.qmk.fm/#/feature_caps_word))
    - Activated by double tapping left Shift
        - can change activation to tapping both left and right Shift by replacing define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD with #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD in config.h
    - Left Shift, left Control and left Option (or left Windows key) will light when Caps Word is enabled
        - #define CAPS_WORD_INDICATOR_COLOR [color] in config.h to set the backlight color used for the indicator when Caps Word is enabled (default: red)
        - remove #define CAPS_WORD_LIGHT_LOWER_LEFT_CORNER from config.h if you wish for the indicator to only light left Shift

- Caps Lock RGB indicator
    - the Caps Lock key will light when Caps Lock is enabled with the following options:
        - #define CAPS_LOCK_INDICATOR_COLOR [color] in config.h to set the backlight color used for the indicator when Caps Lock is enabled (default: red)
        - Fn2+Z (keycode: LTTOG) will toggle lighting the TAB key when Caps Lock is enabled. This is useful with non backlit keycaps/legends. (default: off)
        - Fn2+X (keycode: LATOG) will toggle lighting all the alpha keys when Caps Lock is enabled. (default: off)

- Dynamic Fn layer RGB indicator
    - When either Fn1 or Fn2 is held down, any keys defined on the Fn layers in this firmware or in VIA will be highlighted with the following options:
        - #define FN1_LAYER_COLOR [color] in config.h to set a static color for defined keys on Fn1 layer (default: orange)
        - #define FN2_LAYER_COLOR [color] in config.h to set a static color for defined keys on Fn2 layer (default: green)
        - Fn2+C (keycode: TKTOG) will toggle turning off RGB for keys with no definition (default: RGB off)
        - Fn2+V (keycode: FCTOG) will toggle lighting the defined Fn layer keys with the static color set with FN1_LAYER_COLOR or FN2_LAYER_COLOR (default: static color off)

All custom keycodes described above can be moved to different keys in VIA by using the following keycodes:
- CUSTOM(64) = LTTOG (default: Fn2+Z) Caps Lock Light Tab Toggle
- CUSTOM(65) = LATOG (default: Fn2+X) Caps Lock Light Alpha Toggle
- CUSTOM(66) = TKTOG (default: Fn2+C) Fn layer Trasnparent Key Toggle
- CUSTOM(67) = FCTOG (default: Fn2+V) Fn layer Color Toggle

RGB must be toggled on for all indicators to function. If you do not want an RGB mode active but still want the indicators, toggle RGB on and turn the brightness all the way off. The indicators will remain at full brightness.

Please make sure to save any customizations you have made in VIA to a .json file before flashing the firmware. Sometimes it has been necessary to re-apply those changes in VIA after flashing the firmware. If that is the case, you will most likely need to manually add the custom keycodes back in.

## Optional .json Configuration File

[keychron_q2_ansi_knob_configure_mkillewald.json](https://drive.google.com/file/d/1fCnly9thzn6KfIpd2yOrHi0w9CQgaIxn/view?usp=share_link)

I have included an optional .json configuration file which can be loaded in VIA on the Configure Tab (keyboard icon) to make the following layout changes:

- Removes redundant lighting and NKRO keycodes from Fn1 layer (they remain on Fn2 layer)

- Fn1+Q in Mac mode will lock and sleep display

- Uses Grave Escape on key to the left of the 1 key:
    - Base Layer: key functions as ESC, shift+key gives ~
    - Fn1 and Fn2 Layer: Fn+key gives `

- Changes the two vertical keys under the knob as follows:
    - Base Layer: PGUP and PGDN
    - Fn1 Layer: Home and End (Mac mode does Cmd-left and Cmd-right)
    - Fn2 Layer: Delete and Home (Mac mode Home returns to top of page)

- Changes the knob to function as follows:
    - Base Layer: volume up, down Press: mute
    - Fn1 Layer:  zoom in, out Press: return to 100% zoom
    - Fn2 Layer:  LED brighness inc, dec Press: backlight toggle
    
## Known Issues

1. Keychron factory reset (clear eeprom) Fn1+J+Z is not working 
2. Keychron LED test Fn1+Home+Right is not working

It seems Keychron has not pushed the relavant code to the main QMK repo yet. I see the code is in Keychron's fork, and I may manually add that code here at some point.
 

#### USE AT YOUR OWN RISK

## Changelog:

v1.0.0  March 19, 2023 
- Carried over features from my Q1V2 keymap.