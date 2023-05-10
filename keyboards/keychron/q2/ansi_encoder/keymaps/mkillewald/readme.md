## Keychron Q2 SEVERED RGB ANSI STM32L432 ENC11 (knob) Keymap v2.0.2

<img src="https://raw.githubusercontent.com/mkillewald/glamour_shots/main/keyboards/keychron/q2/IMG_5515.jpg" alt="Keychron Q2 ANSI encoder" width="1000">

### Highly Recommended:
When you flash this firmware for the first time, you should clear the eeprom so that the eeprom defaults are properly set. Be aware that clearing the eeprom will erase any changes previously made in VIA. Please backup your VIA config before clearing the eeprom. If you place your keyboard in DFU mode by holding ESC and plugging in the USB cable, this should clear the eeprom even if you take it out of DFU mode at that point without flashing. Alternatively, you may use the factory reset key combo (Fn1+J+Z) to clear the eeprom after flashing.

## Features:
- Retains Keychron factory keycodes for Mission Control, Launchpad, Siri, Cortana, Task View, File Explorer, and others.

- Retains Keychron factory reset:
    - Hold Fn1+J+Z for 4 seconds. The RGB LEDs will flash red to indicate that the reset has occurred.
    - This will clear the eeprom which returns RGB settings back to defaults and erases any changes made with VIA.

- Retains Keychron LED test:
    - Hold Fn1+Right+PgDn for 4 seconds. The RGB LEDs will all turn white.
    - Press Right to cycle RGB colors (white, red, green and blue) to check operation of each LED.
    - Press PgDn to exit

- SEVERED! Different RGB settings for Mac base and Win base layers. You can set different RGB animations, colors, brightness and speed using the standard RGB keyboard shortcuts. (Hi kids, whats for dinner?)

- Autocorrect is enabled. ([https://docs.qmk.fm/#/feature_autocorrect](https://docs.qmk.fm/#/feature_autocorrect))
    - Uses getreuer's 400 entry autocorrect dictionary.
    [https://github.com/getreuer/qmk-keymap/blob/main/features/autocorrection_dict_extra.txt](https://github.com/getreuer/qmk-keymap/blob/main/features/autocorrection_dict_extra.txt)

- Caps Word enabled with RGB indicator. ([https://docs.qmk.fm/#/feature_caps_word](https://docs.qmk.fm/#/feature_caps_word))

- Caps Lock RGB indicator. Will light Caps Lock key with options to also light Tab key (useful for some keycap sets), and/or light all alpha keys.

- Dynamic Fn layer RGB indicator. When either Fn1 or Fn2 is held down, any keys defined on the Fn layers in this firmware or in VIA will be highlighted.

##### Notes:

###### Toggling RGB mode off will disable RGB and indicators separately for each base layer (Mac or Win). RGB must be toggled on for all indicators to function. If you do not want an RGB mode active but still want the indicators, toggle RGB on and turn the brightness all the way off. The indicators will remain at full brightness.
###### Changing RGB settings with VIA lighting tab is unsupported at this time and may have undesired effects. Keymap changes with VIA is supported.

## Config.h options

Default options (these defaults will be applied whenever the eeprom is cleared):

```
    #define DEFAULT_CAPS_LOCK_LIGHT_TAB      0            // 1 = enable, 0 = disable
    #define DEFAULT_CAPS_LOCK_LIGHT_ALPHA    1            // 1 = enable, 0 = disable
    #define DEFAULT_FN_LAYER_TRANSPARENT_OFF 0            // 1 = enable, 0 = disable
    #define DEFAULT_FN_LAYER_SHOW_COLOR      1            // 1 = enable, 0 = disable
    #define DEFAULT_RGB_ENABLE_MAC_BASE      1            // 1 = enable, 0 = disable
    #define DEFAULT_RGB_ENABLE_WIN_BASE      1            // 1 = enable, 0 = disable
    #define DEFAULT_HUE_WIN_BASE             80           // HSV green hue (Win Base layer)
    #define RGB_MATRIX_DEFAULT_HUE           170          // HSV blue hue  (Mac Base layer)
    #define RGB_MATRIX_DEFAULT_SAT           255          // Both Win/Mac Base layers
    #define RGB_MATRIX_DEFAULT_VAL           255          // Both Win/Mac Base layers
    #define RGB_MATRIX_DEFAULT_SPD           127          // Both Win/Mac Base layers
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BREATHING  // Both Win/Mac Base layers
```

Autocorrect option:

```
    // Autocorrect is on at start up. If you want Autocorrect to be off at startup,
    // un-comment the following line
    //#define AUTOCORRECT_OFF_AT_STARTUP
```

Caps Lock RGB indicator option:

```
    #define CAPS_LOCK_INDICATOR_COLOR RGB_RED
```

Dynamic Fn Layer RGB indicator options:

```
    #define FN1_LAYER_COLOR 0xFE, 0x23, 0x00  // RGB orange
    #define FN2_LAYER_COLOR RGB_YELLOW
```

Caps Word options:

```
    // Caps Word RGB indicator color
    #define CAPS_WORD_INDICATOR_COLOR RGB_RED

    // Caps Word is activated by double-tapping left Shift. Replace this with
    // #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD if you want to activate Caps Word
    // by single-tapping both left and right Shift togeter.
    #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

    // Caps Word will light left Shift, left Control and left Option (or left Windows
    // key) when acitvated. Remove this line if you want Caps Word to only light left
    // Shift when enabled.
    #define CAPS_WORD_LIGHT_LOWER_LEFT_CORNER
```

## This keymap makes the following layout changes over the factory firmware

- Removes redundant lighting and NKRO keycodes from Fn1 layer (they remain on Fn2 layer)
- Fn2+Left Shift toggles Autocorrect on/off
- Fn2+Backspace enters DFU mode (but does not reset eeprom)
- Fn2+Z (KC_LTTOG) Caps Lock Light Tab Toggle (default: off)
    - toggle lighting the Tab key when Caps Lock is enabled. This is useful with non backlit keycaps/legends.
- Fn2+X (KC_LATOG) Caps Lock Light Alpha Toggle (default: on)
    - toggle lighting all the alpha keys when Caps Lock is enabled.
- Fn2+C (KC_TKTOG) Fn layer Trasnparent Key Off Toggle (default: RGB on)
    - toggle turning off RGB for keys with no definition
- Fn2+V (KC_FCTOG) Fn layer Color Toggle (default: static color on)
    - toggle lighting the defined Fn layer keys with the static color set with FN1_LAYER_COLOR or FN2_LAYER_COLOR

- Uses Grave Escape on key to the left of the 1 key:
    - Base Layer: key functions as ESC, shift+key gives ~
    - Fn1 Layer: Fn1+key gives `
    - Fn2 Layer: Fn2+key gives ~

- Changes the two vertical keys under the knob as follows:
    - Base Layer: PGUP and PGDN
    - Fn1 Layer: Home and End (Mac mode does Cmd-left and Cmd-right)
    - Fn2 Layer: Delete and Home (Mac mode Home returns to top of page)

- Changes the knob to function as follows:
    - Base Layer: volume up, down Press: mute
    - Fn1 Layer:  zoom in, out Press: return to 100% zoom
    - Fn2 Layer:  LED brighness inc, dec Press: backlight toggle

- Mac mode only
    - Fn1+Q (KC_LBMAC) will lock and sleep display
    - Fn1+< sets my secondary display to 0° rotation
    - Fn1+> sets my secondary display to 90° rotation

    Note: display rotation requires additional software and changes made, see this link for more information:
    [https://www.reddit.com/r/Keychron/comments/1254g36/howto_macos_rotate_screen_from_keyboard_shortcut/](https://www.reddit.com/r/Keychron/comments/1254g36/howto_macos_rotate_screen_from_keyboard_shortcut/)

All custom keycodes can be moved to different keys in VIA by using the following:
- CUSTOM(64) = KC_LTTOG (default: Fn2+Z) Caps Lock Light Tab Toggle
- CUSTOM(65) = KC_LATOG (default: Fn2+X) Caps Lock Light Alpha Toggle
- CUSTOM(66) = KC_TKTOG (default: Fn2+C) Fn layer Trasnparent Key Off Toggle
- CUSTOM(67) = KC_FCTOG (default: Fn2+V) Fn layer Color Toggle
- CUSTOM(68) = KC_LBMAC (default Mac Only: Fn1+Q) Lock and Blank Mac


#### USE AT YOUR OWN RISK

## Changelog:

v2.0.2  May 9, 2023
- added Keychron factory reset and LED test

v2.0.1  April 11, 2023
- enabled separate RGB toggle for each base layer (Mac / Win)

v2.0.0  April 7, 2023
- added different RGB settings for Mac Base and Win Base layers

v1.0.1  April 4, 2023
- made requested changes by QMK reveiwers
- removed optional .json file and baked my layout changes into the firmware

v1.0.0  March 19, 2023
- Carried over features from my Q1V2 keymap.
