# Keycodes Overview

When defining a [keymap](keymap.md) each key needs a valid key definition. This page documents the symbols that correspond to keycodes that are available to you in QMK.

This is a reference only. Each group of keys links to the page documenting their functionality in more detail.

## Basic Keycodes :id=basic-keycodes

See also: [Basic Keycodes](keycodes_basic.md)

### Letters and Numbers

[keycodes_letters_and_numbers.md](./keycodes_letters_and_numbers.md ':include')

### F Keys

[keycodes_f_keys.md](./keycodes_f_keys.md ':include')

### Punctuation

[keycodes_punctuation.md](./keycodes_punctuation.md ':include')

### Lock Keys

[keycodes_lock_keys.md](./keycodes_lock_keys.md ':include')

### Basic Modifiers

[keycodes_basic_modifiers.md](./keycodes_basic_modifiers.md ':include')

### International Keys

[keycodes_international.md](./keycodes_international.md ':include')

### Commands

[keycodes_commands.md](./keycodes_commands.md ':include')

### Media Keys

[keycodes_media.md](./keycodes_media.md ':include')

### Number Pad

[keycodes_number_pad.md](./keycodes_number_pad.md ':include')

### Special Keys

[keycodes_special.md](./keycodes_special.md ':include')


## Quantum Keycodes :id=quantum-keycodes

See also: [Quantum Keycodes](quantum_keycodes.md#qmk-keycodes)

[keycodes_quantum_keycodes.md](./keycodes_quantum_keycodes.md ':include')

## Audio Keys :id=audio-keys

See also: [Audio](feature_audio.md)

[keycodes_audio.md](./keycodes_audio.md ':include')

## Backlighting :id=backlighting

See also: [Backlighting](feature_backlight.md)

[keycodes_backlight.md](./keycodes_backlight.md ':include')

## Bluetooth :id=bluetooth

See also: [Bluetooth](feature_bluetooth.md)

[keycodes_bluetooth.md](./keycodes_bluetooth.md ':include')

## Dynamic Macros :id=dynamic-macros

See also: [Dynamic Macros](feature_dynamic_macros.md)

[keycodes_dynamic_macros.md](./keycodes_dynamic_macros.md ':include')

## Grave Escape :id=grave-escape

See also: [Grave Escape](feature_grave_esc.md)

[keycodes_grave_escape.md](./keycodes_grave_escape.md ':include')

## Key Lock :id=key-lock

See also: [Key Lock](feature_key_lock.md)

[keycodes_key_lock.md](./keycodes_key_lock.md ':include')

## Layer Switching :id=layer-switching

See also: [Layer Switching](feature_layers.md#switching-and-toggling-layers)

[keycodes_layer_switching.md](./keycodes_layer_switching.md ':include')

## Leader Key :id=leader-key

See also: [Leader Key](feature_leader_key.md)

[keycodes_leader.md](./keycodes_leader.md ':include')

## Magic Keycodes :id=magic-keycodes

See also: [Magic Keycodes](features_magic_keycodes.md)

[keycodes_magic.md](./keycodes_magic.md ':include')

## MIDI :id=midi

See also: [MIDI](feature_midi.md)

[keycodes_midi.md](./keycodes_midi.md ':include')

## Mouse Keys :id=mouse-keys

See also: [Mouse Keys](feature_mouse_keys.md)

|Key             |Aliases  |Description                |
|----------------|---------|---------------------------|
|`KC_MS_UP`      |`KC_MS_U`|Mouse Cursor Up            |
|`KC_MS_DOWN`    |`KC_MS_D`|Mouse Cursor Down          |
|`KC_MS_LEFT`    |`KC_MS_L`|Mouse Cursor Left          |
|`KC_MS_RIGHT`   |`KC_MS_R`|Mouse Cursor Right         |
|`KC_MS_BTN1`    |`KC_BTN1`|Mouse Button 1             |
|`KC_MS_BTN2`    |`KC_BTN2`|Mouse Button 2             |
|`KC_MS_BTN3`    |`KC_BTN3`|Mouse Button 3             |
|`KC_MS_BTN4`    |`KC_BTN4`|Mouse Button 4             |
|`KC_MS_BTN5`    |`KC_BTN5`|Mouse Button 5             |
|`KC_MS_WH_UP`   |`KC_WH_U`|Mouse Wheel Up             |
|`KC_MS_WH_DOWN` |`KC_WH_D`|Mouse Wheel Down           |
|`KC_MS_WH_LEFT` |`KC_WH_L`|Mouse Wheel Left           |
|`KC_MS_WH_RIGHT`|`KC_WH_R`|Mouse Wheel Right          |
|`KC_MS_ACCEL0`  |`KC_ACL0`|Set mouse acceleration to 0|
|`KC_MS_ACCEL1`  |`KC_ACL1`|Set mouse acceleration to 1|
|`KC_MS_ACCEL2`  |`KC_ACL2`|Set mouse acceleration to 2|

## Advanced Modifiers :id=advanced-modifiers

See also: [Advanced Modifier Keys](feature_advanced_keycodes.md#advanced-modifier-keys)

[keycodes_advanced_modifiers.md](./keycodes_advanced_modifiers.md ':include')

## Mod-Tap Keys :id=mod-tap-keys

See also: [Mod-Tap](mod_tap.md)

|Key          |Aliases                                                          |Description                                                   |
|-------------|-----------------------------------------------------------------|--------------------------------------------------------------|
|`MT(mod, kc)`|                                                                 |`mod` when held, `kc` when tapped                             |
|`LCTL_T(kc)` |`CTL_T(kc)`                                                      |Left Control when held, `kc` when tapped                      |
|`LSFT_T(kc)` |`SFT_T(kc)`                                                      |Left Shift when held, `kc` when tapped                        |
|`LALT_T(kc)` |`LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                           |Left Alt when held, `kc` when tapped                          |
|`LGUI_T(kc)` |`LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)`|Left GUI when held, `kc` when tapped                          |
|`RCTL_T(kc)` |                                                                 |Right Control when held, `kc` when tapped                     |
|`RSFT_T(kc)` |                                                                 |Right Shift when held, `kc` when tapped                       |
|`RALT_T(kc)` |`ROPT_T(kc)`, `ALGR_T(kc)`                                       |Right Alt (AltGr) when held, `kc` when tapped                 |
|`RGUI_T(kc)` |`RCMD_T(kc)`, `RWIN_T(kc)`                                       |Right GUI when held, `kc` when tapped                         |
|`LSG_T(kc)`  |`SGUI_T(kc)`, `SCMD_T(kc)`, `SWIN_T(kc)`                         |Left Shift and GUI when held, `kc` when tapped                |
|`LAG_T(kc)`  |                                                                 |Left Alt and GUI when held, `kc` when tapped                  |
|`RSG_T(kc)`  |                                                                 |Right Shift and GUI when held, `kc` when tapped               |
|`RAG_T(kc)`  |                                                                 |Right Alt and GUI when held, `kc` when tapped                 |
|`LCA_T(kc)`  |                                                                 |Left Control and Alt when held, `kc` when tapped              |
|`LSA_T(kc)`  |                                                                 |Left Shift and Left Alt when held, `kc` when tapped           |
|`RSA_T(kc)`  |`SAGR_T(kc)`                                                     |Right Shift and Right Alt (AltGr) when held, `kc` when tapped |
|`RCS_T(kc)`  |                                                                 |Right Control and Right Shift when held, `kc` when tapped     |
|`LCAG_T(kc)` |                                                                 |Left Control, Alt and GUI when held, `kc` when tapped         |
|`RCAG_T(kc)` |                                                                 |Right Control, Alt and GUI when held, `kc` when tapped        |
|`C_S_T(kc)`  |                                                                 |Left Control and Shift when held, `kc` when tapped            |
|`MEH_T(kc)`  |                                                                 |Left Control, Shift and Alt when held, `kc` when tapped       |
|`HYPR_T(kc)` |`ALL_T(kc)`                                                      |Left Control, Shift, Alt and GUI when held, `kc` when tapped - more info [here](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|

## Tapping Term Keys :id=tapping-term-keys

See also: [Dynamic Tapping Term](tap_hold#dynamic-tapping-term)

| Key         | Description                                                                                                            |
|-------------|------------------------------------------------------------------------------------------------------------------------|
| `DT_PRNT`   | "Dynamic Tapping Term Print": Types the current tapping term, in milliseconds                                          |
| `DT_UP`     | "Dynamic Tapping Term Up": Increases the current tapping term by `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms by default)   |
| `DT_DOWN`   | "Dynamic Tapping Term Down": Decreases the current tapping term by `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms by default) |

## RGB Lighting :id=rgb-lighting

See also: [RGB Lighting](feature_rgblight.md)

|Key                |Aliases   |Description                                                         |
|-------------------|----------|--------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                       |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held           |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held|
|`RGB_HUI`          |          |Increase hue, decrease hue when Shift is held                       |
|`RGB_HUD`          |          |Decrease hue, increase hue when Shift is held                       |
|`RGB_SAI`          |          |Increase saturation, decrease saturation when Shift is held         |
|`RGB_SAD`          |          |Decrease saturation, increase saturation when Shift is held         |
|`RGB_VAI`          |          |Increase value (brightness), decrease value when Shift is held      |
|`RGB_VAD`          |          |Decrease value (brightness), increase value when Shift is held      |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|Static (no animation) mode                                          |
|`RGB_MODE_BREATHE` |`RGB_M_B` |Breathing animation mode                                            |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |Rainbow animation mode                                              |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|Swirl animation mode                                                |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|Snake animation mode                                                |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |"Knight Rider" animation mode                                       |
|`RGB_MODE_XMAS`    |`RGB_M_X` |Christmas animation mode                                            |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |Static gradient animation mode                                      |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |Red,Green,Blue test animation mode                                  |

## RGB Matrix Lighting :id=rgb-matrix-lighting

See also: [RGB Matrix Lighting](feature_rgb_matrix.md)

|Key                |Aliases   |Description                                                                           |
|-------------------|----------|--------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                                         |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held                             |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held                  |
|`RGB_HUI`          |          |Increase hue, decrease hue when Shift is held                                         |
|`RGB_HUD`          |          |Decrease hue, increase hue when Shift is held                                         |
|`RGB_SAI`          |          |Increase saturation, decrease saturation when Shift is held                           |
|`RGB_SAD`          |          |Decrease saturation, increase saturation when Shift is held                           |
|`RGB_VAI`          |          |Increase value (brightness), decrease value when Shift is held                        |
|`RGB_VAD`          |          |Decrease value (brightness), increase value when Shift is held                        |
|`RGB_SPI`          |          |Increase effect speed (does not support eeprom yet), decrease speed when Shift is held|
|`RGB_SPD`          |          |Decrease effect speed (does not support eeprom yet), increase speed when Shift is held|

## Thermal Printer :id=thermal-printer

See also: [Thermal Printer](feature_thermal_printer.md)

|Key        |Description                             |
|-----------|----------------------------------------|
|`PRINT_ON` |Start printing everything the user types|
|`PRINT_OFF`|Stop printing everything the user types |

## US ANSI Shifted Symbols :id=us-ansi-shifted-symbols

See also: [US ANSI Shifted Symbols](keycodes_us_ansi_shifted.md)

|Key                     |Aliases            |Description|
|------------------------|-------------------|-----------|
|`KC_TILDE`              |`KC_TILD`          |`~`        |
|`KC_EXCLAIM`            |`KC_EXLM`          |`!`        |
|`KC_AT`                 |                   |`@`        |
|`KC_HASH`               |                   |`#`        |
|`KC_DOLLAR`             |`KC_DLR`           |`$`        |
|`KC_PERCENT`            |`KC_PERC`          |`%`        |
|`KC_CIRCUMFLEX`         |`KC_CIRC`          |`^`        |
|`KC_AMPERSAND`          |`KC_AMPR`          |`&`        |
|`KC_ASTERISK`           |`KC_ASTR`          |`*`        |
|`KC_LEFT_PAREN`         |`KC_LPRN`          |`(`        |
|`KC_RIGHT_PAREN`        |`KC_RPRN`          |`)`        |
|`KC_UNDERSCORE`         |`KC_UNDS`          |`_`        |
|`KC_PLUS`               |                   |`+`        |
|`KC_LEFT_CURLY_BRACE`   |`KC_LCBR`          |`{`        |
|`KC_RIGHT_CURLY_BRACE`  |`KC_RCBR`          |`}`        |
|`KC_PIPE`               |                   |`\|`       |
|`KC_COLON`              |`KC_COLN`          |`:`        |
|`KC_DOUBLE_QUOTE`       |`KC_DQUO`, `KC_DQT`|`"`        |
|`KC_LEFT_ANGLE_BRACKET` |`KC_LABK`, `KC_LT` |`<`        |
|`KC_RIGHT_ANGLE_BRACKET`|`KC_RABK`, `KC_GT` |`>`        |
|`KC_QUESTION`           |`KC_QUES`          |`?`        |

## One Shot Keys :id=one-shot-keys

See also: [One Shot Keys](one_shot_keys.md)

|Key         |Description                       |
|------------|----------------------------------|
|`OSM(mod)`  |Hold `mod` for one keypress       |
|`OSL(layer)`|Switch to `layer` for one keypress|
|`OS_ON`     |Turns One Shot keys on            |
|`OS_OFF`    |Turns One Shot keys off           |
|`OS_TOGG`   |Toggles One Shot keys status      |

## Programmable Button Support :id=programmable-button

See also: [Programmable Button](feature_programmable_button.md)

|Key                     |Description                                                     |
|------------------------|----------------------|
|`PROGRAMMABLE_BUTTON_1` |Programmable button 1 |
|`PROGRAMMABLE_BUTTON_2` |Programmable button 2 |
|`PROGRAMMABLE_BUTTON_3` |Programmable button 3 |
|`PROGRAMMABLE_BUTTON_4` |Programmable button 4 |
|`PROGRAMMABLE_BUTTON_5` |Programmable button 5 |
|`PROGRAMMABLE_BUTTON_6` |Programmable button 6 |
|`PROGRAMMABLE_BUTTON_7` |Programmable button 7 |
|`PROGRAMMABLE_BUTTON_8` |Programmable button 8 |
|`PROGRAMMABLE_BUTTON_9` |Programmable button 9 |
|`PROGRAMMABLE_BUTTON_10`|Programmable button 10|
|`PROGRAMMABLE_BUTTON_11`|Programmable button 11|
|`PROGRAMMABLE_BUTTON_12`|Programmable button 12|
|`PROGRAMMABLE_BUTTON_13`|Programmable button 13|
|`PROGRAMMABLE_BUTTON_14`|Programmable button 14|
|`PROGRAMMABLE_BUTTON_15`|Programmable button 15|
|`PROGRAMMABLE_BUTTON_16`|Programmable button 16|
|`PROGRAMMABLE_BUTTON_17`|Programmable button 17|
|`PROGRAMMABLE_BUTTON_18`|Programmable button 18|
|`PROGRAMMABLE_BUTTON_19`|Programmable button 19|
|`PROGRAMMABLE_BUTTON_20`|Programmable button 20|
|`PROGRAMMABLE_BUTTON_21`|Programmable button 21|
|`PROGRAMMABLE_BUTTON_22`|Programmable button 22|
|`PROGRAMMABLE_BUTTON_23`|Programmable button 23|
|`PROGRAMMABLE_BUTTON_24`|Programmable button 24|
|`PROGRAMMABLE_BUTTON_25`|Programmable button 25|
|`PROGRAMMABLE_BUTTON_26`|Programmable button 26|
|`PROGRAMMABLE_BUTTON_27`|Programmable button 27|
|`PROGRAMMABLE_BUTTON_28`|Programmable button 28|
|`PROGRAMMABLE_BUTTON_29`|Programmable button 29|
|`PROGRAMMABLE_BUTTON_30`|Programmable button 30|
|`PROGRAMMABLE_BUTTON_31`|Programmable button 31|
|`PROGRAMMABLE_BUTTON_32`|Programmable button 32|
|`PB_1` to `PB_32`       |Aliases for keymaps   |

## Space Cadet :id=space-cadet

See also: [Space Cadet](feature_space_cadet.md)

|Key        |Description                             |
|-----------|----------------------------------------|
|`KC_LCPO`  |Left Control when held, `(` when tapped |
|`KC_RCPC`  |Right Control when held, `)` when tapped|
|`KC_LSPO`  |Left Shift when held, `(` when tapped   |
|`KC_RSPC`  |Right Shift when held, `)` when tapped  |
|`KC_LAPO`  |Left Alt when held, `(` when tapped     |
|`KC_RAPC`  |Right Alt when held, `)` when tapped    |
|`KC_SFTENT`|Right Shift when held, Enter when tapped|

## Swap Hands :id=swap-hands

See also: [Swap Hands](feature_swap_hands.md)

|Key        |Description                                                              |
|-----------|-------------------------------------------------------------------------|
|`SH_T(key)`|Sends `key` with a tap; momentary swap when held.                        |
|`SW_ON`    |Turns on swapping and leaves it on.                                      |
|`SW_OFF`   |Turn off swapping and leaves it off. Good for returning to a known state.|
|`SH_MON`   |Swaps hands when pressed, returns to normal when released (momentary).   |
|`SH_MOFF`  |Momentarily turns off swap.                                              |
|`SH_TG`    |Toggles swap on and off with every key press.                            |
|`SH_TT`    |Toggles with a tap; momentary when held.                                 |
|`SH_OS`    |One shot swap hands: toggle while pressed or until next key press.       |

## Unicode Support :id=unicode-support

See also: [Unicode Support](feature_unicode.md)

|Key                   |Aliases  |Description                                                     |
|----------------------|---------|----------------------------------------------------------------|
|`UC(c)`               |         |Send Unicode code point `c`, up to `0x7FFF`                     |
|`X(i)`                |         |Send Unicode code point at index `i` in `unicode_map`           |
|`XP(i, j)`            |         |Send Unicode code point at index `i`, or `j` if Shift/Caps is on|
|`UNICODE_MODE_FORWARD`|`UC_MOD` |Cycle through selected input modes                              |
|`UNICODE_MODE_REVERSE`|`UC_RMOD`|Cycle through selected input modes in reverse                   |
|`UNICODE_MODE_MAC`    |`UC_M_MA`|Switch to macOS input                                           |
|`UNICODE_MODE_LNX`    |`UC_M_LN`|Switch to Linux input                                           |
|`UNICODE_MODE_WIN`    |`UC_M_WI`|Switch to Windows input                                         |
|`UNICODE_MODE_BSD`    |`UC_M_BS`|Switch to BSD input (not implemented)                           |
|`UNICODE_MODE_WINC`   |`UC_M_WC`|Switch to Windows input using WinCompose                        |
