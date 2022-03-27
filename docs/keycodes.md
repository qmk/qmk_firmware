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

|Key              |Aliases  |Description                                            |
|-----------------|---------|-------------------------------------------------------|
|`QK_BOOTLOADER`  |`QK_BOOT`|Put the keyboard into bootloader mode for flashing     |
|`QK_DEBUG_TOGGLE`|`DB_TOGG`|Toggle debug mode                                      |
|`QK_CLEAR_EEPROM`|`EE_CLR` |Reinitializes the keyboard's EEPROM (persistent memory)|

## Audio Keys :id=audio-keys

See also: [Audio](feature_audio.md)

|Key             |Aliases  |Description                       |
|----------------|---------|----------------------------------|
|`AU_ON`         |         |Turns on Audio Feature            |
|`AU_OFF`        |         |Turns off Audio Feature           |
|`AU_TOG`        |         |Toggles Audio state               |
|`CLICKY_TOGGLE` |`CK_TOGG`|Toggles Audio clicky mode         |
|`CLICKY_UP`     |`CK_UP`  |Increases frequency of the clicks |
|`CLICKY_DOWN`   |`CK_DOWN`|Decreases frequency of the clicks |
|`CLICKY_RESET`  |`CK_RST` |Resets frequency to default       |
|`MU_ON`         |         |Turns on Music Mode               |
|`MU_OFF`        |         |Turns off Music Mode              |
|`MU_TOG`        |         |Toggles Music Mode                |
|`MU_MOD`        |         |Cycles through the music modes    |

## Backlighting :id=backlighting

See also: [Backlighting](feature_backlight.md)

|Key      |Description                               |
|---------|------------------------------------------|
|`BL_TOGG`|Turn the backlight on or off              |
|`BL_STEP`|Cycle through backlight levels            |
|`BL_ON`  |Set the backlight to max brightness       |
|`BL_OFF` |Turn the backlight off                    |
|`BL_INC` |Increase the backlight level              |
|`BL_DEC` |Decrease the backlight level              |
|`BL_BRTG`|Toggle backlight breathing                |

## Bluetooth :id=bluetooth

See also: [Bluetooth](feature_bluetooth.md)

|Key       |Description                                   |
|----------|----------------------------------------------|
|`OUT_AUTO`|Automatically switch between USB and Bluetooth|
|`OUT_USB` |USB only                                      |
|`OUT_BT`  |Bluetooth only                                |

## Dynamic Macros :id=dynamic-macros

See also: [Dynamic Macros](feature_dynamic_macros.md)

|Key              |Aliases  |Description                                       |
|-----------------|---------|--------------------------------------------------|
|`DYN_REC_START1` |`DM_REC1`|Start recording Macro 1                           |
|`DYN_REC_START2` |`DM_REC2`|Start recording Macro 2                           |
|`DYN_MACRO_PLAY1`|`DM_PLY1`|Replay Macro 1                                    |
|`DYN_MACRO_PLAY2`|`DM_PLY2`|Replay Macro 2                                    |
|`DYN_REC_STOP`   |`DM_RSTP`|Finish the macro that is currently being recorded.|

## Grave Escape :id=grave-escape

See also: [Grave Escape](feature_grave_esc.md)

|Key              |Aliases  |Description                                                       |
|-----------------|---------|------------------------------------------------------------------|
|`QK_GRAVE_ESCAPE`|`QK_GESC`|Escape when pressed, <code>&#96;</code> when Shift or GUI are held|

## Key Lock :id=key-lock

See also: [Key Lock](feature_key_lock.md)

|Key      |Description                                                   |
|---------|--------------------------------------------------------------|
|`KC_LOCK`|Hold down the next key pressed, until the key is pressed again|

## Layer Switching :id=layer-switching

See also: [Layer Switching](feature_layers.md#switching-and-toggling-layers)

|Key             |Description                                                                       |
|----------------|----------------------------------------------------------------------------------|
|`DF(layer)`     |Set the base (default) layer                                                      |
|`MO(layer)`     |Momentarily turn on `layer` when pressed (requires `KC_TRNS` on destination layer)|
|`OSL(layer)`    |Momentarily activates `layer` until a key is pressed. See [One Shot Keys](one_shot_keys.md) for details. |
|`LM(layer, mod)`|Momentarily turn on `layer` (like MO) with `mod` active as well.  Where `mod` is a mods_bit.  Mods can be viewed [here](mod_tap.md).  Example Implementation: `LM(LAYER_1, MOD_LALT)`|
|`LT(layer, kc)` |Turn on `layer` when held, `kc` when tapped                                       |
|`TG(layer)`     |Toggle `layer` on or off                                                          |
|`TO(layer)`     |Turns on `layer` and turns off all other layers, except the default layer |
|`TT(layer)`     |Normally acts like MO unless it's tapped multiple times, which toggles `layer` on |

## Leader Key :id=leader-key

See also: [Leader Key](feature_leader_key.md)

|Key      |Description             |
|---------|------------------------|
|`KC_LEAD`|Begins a leader sequence|

## Magic Keycodes :id=magic-keycodes

See also: [Magic Keycodes](keycodes_magic.md)

|Key                               |Aliases  |Description                                                               |
|----------------------------------|---------|--------------------------------------------------------------------------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
|`MAGIC_TOGGLE_CONTROL_CAPSLOCK`   |`CL_TOGG`|Toggle Caps Lock and Left Control swap                                    |
|`MAGIC_CAPSLOCK_TO_CONTROL`       |`CL_CTRL`|Treat Caps Lock as Control                                                |
|`MAGIC_UNCAPSLOCK_TO_CONTROL`     |`CL_CAPS`|Stop treating Caps Lock as Control                                        |
|`MAGIC_SWAP_LCTL_LGUI`            |`LCG_SWP`|Swap Left Control and GUI                                                 |
|`MAGIC_UNSWAP_LCTL_LGUI`          |`LCG_NRM`|Unswap Left Control and GUI                                               |
|`MAGIC_SWAP_RCTL_RGUI`            |`RCG_SWP`|Swap Right Control and GUI                                                |
|`MAGIC_UNSWAP_RCTL_RGUI`          |`RCG_NRM`|Unswap Right Control and GUI                                              |
|`MAGIC_SWAP_CTL_GUI`              |`CG_SWAP`|Swap Control and GUI on both sides                                        |
|`MAGIC_UNSWAP_CTL_GUI`            |`CG_NORM`|Unswap Control and GUI on both sides                                      |
|`MAGIC_TOGGLE_CTL_GUI`            |`CG_TOGG`|Toggle Control and GUI swap on both sides                                 |
|`MAGIC_SWAP_LALT_LGUI`            |`LAG_SWP`|Swap Left Alt and GUI                                                     |
|`MAGIC_UNSWAP_LALT_LGUI`          |`LAG_NRM`|Unswap Left Alt and GUI                                                   |
|`MAGIC_SWAP_RALT_RGUI`            |`RAG_SWP`|Swap Right Alt and GUI                                                    |
|`MAGIC_UNSWAP_RALT_RGUI`          |`RAG_NRM`|Unswap Right Alt and GUI                                                  |
|`MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides                                            |
|`MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Alt and GUI on both sides                                          |
|`MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Alt and GUI swap on both sides                                     |
|`MAGIC_NO_GUI`                    |`GUI_OFF`|Disable the GUI keys                                                      |
|`MAGIC_UNNO_GUI`                  |`GUI_ON` |Enable the GUI keys                                                       |
|`MAGIC_TOGGLE_GUI`                |`GUI_TOG`|Toggles the status of the GUI keys                                        |
|`MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`MAGIC_HOST_NKRO`                 |`NK_ON`  |Enable N-key rollover                                                     |
|`MAGIC_UNHOST_NKRO`               |`NK_OFF` |Disable N-key rollover                                                    |
|`MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|

## MIDI :id=midi

See also: [MIDI](feature_midi.md)

|Key         |Aliases  |Description                      |
|------------|---------|---------------------------------|
|`MI_ON`     |         |Turn MIDI on                     |
|`MI_OFF`    |         |Turn MIDI off                    |
|`MI_TOG`    |         |Toggle MIDI enabled              |
|`MI_C`      |         |C octave 0                       |
|`MI_Cs`     |`MI_Db`  |C♯/D♭ octave 0                   |
|`MI_D`      |         |D octave 0                       |
|`MI_Ds`     |`MI_Eb`  |D♯/E♭ octave 0                   |
|`MI_E`      |         |E octave 0                       |
|`MI_F`      |         |F octave 0                       |
|`MI_Fs`     |`MI_Gb`  |F♯/G♭ octave 0                   |
|`MI_G`      |         |G octave 0                       |
|`MI_Gs`     |`MI_Gs`  |G♯/A♭ octave 0                   |
|`MI_A`      |         |A octave 0                       |
|`MI_As`     |`MI_Bb`  |A♯/B♭ octave 0                   |
|`MI_B`      |         |B octave 0                       |
|`MI_C_1`    |         |C octave 1                       |
|`MI_Cs_1`   |`MI_Db_1`|C♯/D♭ octave 1                   |
|`MI_D_1`    |         |D octave 1                       |
|`MI_Ds_1`   |`MI_Eb_1`|D♯/E♭ octave 1                   |
|`MI_E_1`    |         |E octave 1                       |
|`MI_F_1`    |         |F octave 1                       |
|`MI_Fs_1`   |`MI_Gb_1`|F♯/G♭ octave 1                   |
|`MI_G_1`    |         |G octave 1                       |
|`MI_Gs_1`   |`MI_Ab_1`|G♯/A♭ octave 1                   |
|`MI_A_1`    |         |A octave 1                       |
|`MI_As_1`   |`MI_Bb_1`|A♯/B♭ octave 1                   |
|`MI_B_1`    |         |B octave 1                       |
|`MI_C_2`    |         |C octave 2                       |
|`MI_Cs_2`   |`MI_Db_2`|C♯/D♭ octave 2                   |
|`MI_D_2`    |         |D octave 2                       |
|`MI_Ds_2`   |`MI_Eb_2`|D♯/E♭ octave 2                   |
|`MI_E_2`    |         |E octave 2                       |
|`MI_F_2`    |         |F octave 2                       |
|`MI_Fs_2`   |`MI_Gb_2`|F♯/G♭ octave 2                   |
|`MI_G_2`    |         |G octave 2                       |
|`MI_Gs_2`   |`MI_Ab_2`|G♯/A♭ octave 2                   |
|`MI_A_2`    |         |A octave 2                       |
|`MI_As_2`   |`MI_Bb_2`|A♯/B♭ octave 2                   |
|`MI_B_2`    |         |B octave 2                       |
|`MI_C_3`    |         |C octave 3                       |
|`MI_Cs_3`   |`MI_Db_3`|C♯/D♭ octave 3                   |
|`MI_D_3`    |         |D octave 3                       |
|`MI_Ds_3`   |`MI_Eb_3`|D♯/E♭ octave 3                   |
|`MI_E_3`    |         |E octave 3                       |
|`MI_F_3`    |         |F octave 3                       |
|`MI_Fs_3`   |`MI_Gb_3`|F♯/G♭ octave 3                   |
|`MI_G_3`    |         |G octave 3                       |
|`MI_Gs_3`   |`MI_Ab_3`|G♯/A♭ octave 3                   |
|`MI_A_3`    |         |A octave 3                       |
|`MI_As_3`   |`MI_Bb_3`|A♯/B♭ octave 3                   |
|`MI_B_3`    |         |B octave 3                       |
|`MI_C_4`    |         |C octave 4                       |
|`MI_Cs_4`   |`MI_Db_4`|C♯/D♭ octave 4                   |
|`MI_D_4`    |         |D octave 4                       |
|`MI_Ds_4`   |`MI_Eb_4`|D♯/E♭ octave 4                   |
|`MI_E_4`    |         |E octave 4                       |
|`MI_F_4`    |         |F octave 4                       |
|`MI_Fs_4`   |`MI_Gb_4`|F♯/G♭ octave 4                   |
|`MI_G_4`    |         |G octave 4                       |
|`MI_Gs_4`   |`MI_Ab_4`|G♯/A♭ octave 4                   |
|`MI_A_4`    |         |A octave 4                       |
|`MI_As_4`   |`MI_Bb_4`|A♯/B♭ octave 4                   |
|`MI_B_4`    |         |B octave 4                       |
|`MI_C_5`    |         |C octave 5                       |
|`MI_Cs_5`   |`MI_Db_5`|C♯/D♭ octave 5                   |
|`MI_D_5`    |         |D octave 5                       |
|`MI_Ds_5`   |`MI_Eb_5`|D♯/E♭ octave 5                   |
|`MI_E_5`    |         |E octave 5                       |
|`MI_F_5`    |         |F octave 5                       |
|`MI_Fs_5`   |`MI_Gb_5`|F♯/G♭ octave 5                   |
|`MI_G_5`    |         |G octave 5                       |
|`MI_Gs_5`   |`MI_Ab_5`|G♯/A♭ octave 5                   |
|`MI_A_5`    |         |A octave 5                       |
|`MI_As_5`   |`MI_Bb_5`|A♯/B♭ octave 5                   |
|`MI_B_5`    |         |B octave 5                       |
|`MI_OCT_N2` |         |Set octave to -2                 |
|`MI_OCT_N1` |         |Set octave to -1                 |
|`MI_OCT_0`  |         |Set octave to 0                  |
|`MI_OCT_1`  |         |Set octave to 1                  |
|`MI_OCT_2`  |         |Set octave to 2                  |
|`MI_OCT_3`  |         |Set octave to 3                  |
|`MI_OCT_4`  |         |Set octave to 4                  |
|`MI_OCT_5`  |         |Set octave to 5                  |
|`MI_OCT_6`  |         |Set octave to 6                  |
|`MI_OCT_7`  |         |Set octave to 7                  |
|`MI_OCTD`   |         |Move down an octave              |
|`MI_OCTU`   |         |Move up an octave                |
|`MI_TRNS_N6`|         |Set transposition to -6 semitones|
|`MI_TRNS_N5`|         |Set transposition to -5 semitones|
|`MI_TRNS_N4`|         |Set transposition to -4 semitones|
|`MI_TRNS_N3`|         |Set transposition to -3 semitones|
|`MI_TRNS_N2`|         |Set transposition to -2 semitones|
|`MI_TRNS_N1`|         |Set transposition to -1 semitone |
|`MI_TRNS_0` |         |No transposition                 |
|`MI_TRNS_1` |         |Set transposition to +1 semitone |
|`MI_TRNS_2` |         |Set transposition to +2 semitones|
|`MI_TRNS_3` |         |Set transposition to +3 semitones|
|`MI_TRNS_4` |         |Set transposition to +4 semitones|
|`MI_TRNS_5` |         |Set transposition to +5 semitones|
|`MI_TRNS_6` |         |Set transposition to +6 semitones|
|`MI_TRNSD`  |         |Decrease transposition           |
|`MI_TRNSU`  |         |Increase transposition           |
|`MI_VEL_0`  |         |Set velocity to 0                |
|`MI_VEL_1`  |         |Set velocity to 12               |
|`MI_VEL_2`  |         |Set velocity to 25               |
|`MI_VEL_3`  |         |Set velocity to 38               |
|`MI_VEL_4`  |         |Set velocity to 51               |
|`MI_VEL_5`  |         |Set velocity to 64               |
|`MI_VEL_6`  |         |Set velocity to 76               |
|`MI_VEL_7`  |         |Set velocity to 89               |
|`MI_VEL_8`  |         |Set velocity to 102              |
|`MI_VEL_9`  |         |Set velocity to 114              |
|`MI_VEL_10` |         |Set velocity to 127              |
|`MI_VELD`   |         |Decrease velocity                |
|`MI_VELU`   |         |Increase velocity                |
|`MI_CH1`    |         |Set channel to 1                 |
|`MI_CH2`    |         |Set channel to 2                 |
|`MI_CH3`    |         |Set channel to 3                 |
|`MI_CH4`    |         |Set channel to 4                 |
|`MI_CH5`    |         |Set channel to 5                 |
|`MI_CH6`    |         |Set channel to 6                 |
|`MI_CH7`    |         |Set channel to 7                 |
|`MI_CH8`    |         |Set channel to 8                 |
|`MI_CH9`    |         |Set channel to 9                 |
|`MI_CH10`   |         |Set channel to 10                |
|`MI_CH11`   |         |Set channel to 11                |
|`MI_CH12`   |         |Set channel to 12                |
|`MI_CH13`   |         |Set channel to 13                |
|`MI_CH14`   |         |Set channel to 14                |
|`MI_CH15`   |         |Set channel to 15                |
|`MI_CH16`   |         |Set channel to 16                |
|`MI_CHD`    |         |Decrease channel                 |
|`MI_CHU`    |         |Increase channel                 |
|`MI_ALLOFF` |         |Stop all notes                   |
|`MI_SUS`    |         |Sustain                          |
|`MI_PORT`   |         |Portmento                        |
|`MI_SOST`   |         |Sostenuto                        |
|`MI_SOFT`   |         |Soft Pedal                       |
|`MI_LEG`    |         |Legato                           |
|`MI_MOD`    |         |Modulation                       |
|`MI_MODSD`  |         |Decrease modulation speed        |
|`MI_MODSU`  |         |Increase modulation speed        |
|`MI_BENDD`  |         |Bend pitch down                  |
|`MI_BENDU`  |         |Bend pitch up                    |

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
