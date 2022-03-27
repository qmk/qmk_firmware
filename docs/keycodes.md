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

[keycodes_mouse.md](./keycodes_mouse.md ':include')

## Advanced Modifiers :id=advanced-modifiers

See also: [Advanced Modifier Keys](feature_advanced_keycodes.md#advanced-modifier-keys)

[keycodes_advanced_modifiers.md](./keycodes_advanced_modifiers.md ':include')

## Mod-Tap Keys :id=mod-tap-keys

See also: [Mod-Tap](mod_tap.md)

[keycodes_mod_tap.md](./keycodes_mod_tap.md ':include')

## Tapping Term Keys :id=tapping-term-keys

See also: [Dynamic Tapping Term](tap_hold#dynamic-tapping-term)

[keycodes_tapping_term.md](./keycodes_tapping_term.md ':include')

## RGB Lighting :id=rgb-lighting

See also: [RGB Lighting](feature_rgblight.md)

[keycodes_rgb_lighting.md](./keycodes_rgb_lighting.md ':include')

## RGB Matrix Lighting :id=rgb-matrix-lighting

See also: [RGB Matrix Lighting](feature_rgb_matrix.md)

[keycodes_rgb_lighting.md](./keycodes_rgb_lighting.md ':include')

## Thermal Printer :id=thermal-printer

See also: [Thermal Printer](feature_thermal_printer.md)

[keycodes_thermal_printer.md](./keycodes_thermal_printer.md ':include')

## US ANSI Shifted Symbols :id=us-ansi-shifted-symbols

See also: [US ANSI Shifted Symbols](keycodes_us_ansi_shifted.md)

[keycodes_us_ansi_shifted_symbols.md](./keycodes_us_ansi_shifted_symbols.md ':include')

## One Shot Keys :id=one-shot-keys

See also: [One Shot Keys](one_shot_keys.md)

[keycodes_one_shot.md](./keycodes_one_shot.md ':include')

## Programmable Button Support :id=programmable-button

See also: [Programmable Button](feature_programmable_button.md)

[keycodes_programmable_buttons.md](./keycodes_programmable_buttons.md ':include')

## Space Cadet :id=space-cadet

See also: [Space Cadet](feature_space_cadet.md)

[keycodes_space_cadet.md](./keycodes_space_cadet.md ':include')

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
