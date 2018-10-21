# Bootmagic

There are three separate but related features that allow you to change the behavior of your keyboard without reflashing. While each of them have similar functionality, it is accessed in different ways depending on how your keyboard is configured.

**Bootmagic** is a system for configuring your keyboard while it initializes. To trigger a Bootmagic command, hold down the Bootmagic key and one or more command keys.

**Bootmagic Keycodes** are prefixed with `MAGIC_`, and allow you to access the Bootmagic functionality *after* your keyboard has initialized. To use the keycodes, assign them to your keymap as you would any other keycode.

**Command**, formerly known as **Magic**, is another feature that allows you to control different aspects of your keyboard. While it shares some functionality with Bootmagic, it also allows you to do things that Bootmagic does not, such as printing version information to the console. For more information, see [Command](feature_command.md).

On some keyboards Bootmagic is disabled by default. If this is the case, it must be explicitly enabled in your `rules.mk` with:

```make
BOOTMAGIC_ENABLE = yes
```

## Hotkeys

Hold down the Bootmagic key (Space by default) and the desired hotkey while plugging in your keyboard. For example, holding Space+`B` should cause it to enter the bootloader.

|Hotkey            |Description                                  |
|------------------|---------------------------------------------|
|Escape            |Ignore Bootmagic configuration in EEPROM     |
|`B`               |Enter the bootloader                         |
|`D`               |Toggle debugging over serial                 |
|`X`               |Toggle key matrix debugging                  |
|`K`               |Toggle keyboard debugging                    |
|`M`               |Toggle mouse debugging                       |
|Backspace         |Clear the EEPROM                             |
|Caps Lock         |Toggle treating Caps Lock as Left Control    |
|Left Control      |Toggle swapping Caps Lock and Left Control   |
|Left Alt          |Toggle swapping Left Alt and Left GUI        |
|Right Alt         |Toggle swapping Right Alt and Right GUI      |
|Left GUI          |Toggle the GUI keys (useful when gaming)     |
|<code>&#96;</code>|Toggle swapping <code>&#96;</code> and Escape|
|`\`               |Toggle swapping `\` and Backspace            |
|`N`               |Toggle N-Key Rollover (NKRO)                 |
|`0`               |Make layer 0 the default layer               |
|`1`               |Make layer 1 the default layer               |
|`2`               |Make layer 2 the default layer               |
|`3`               |Make layer 3 the default layer               |
|`4`               |Make layer 4 the default layer               |
|`5`               |Make layer 5 the default layer               |
|`6`               |Make layer 6 the default layer               |
|`7`               |Make layer 7 the default layer               |

## Keycodes

|Keycode                           |Aliases  |Description                               |
|----------------------------------|---------|------------------------------------------|
|`MAGIC_CAPSLOCK_TO_CONTROL`       |         |Treat Caps Lock as Left Control           |
|`MAGIC_UNCAPSLOCK_TO_CONTROL`     |         |Stop treating Caps Lock as Left Control   |
|`MAGIC_HOST_NKRO`                 |         |Force N-Key Rollover (NKRO) on            |
|`MAGIC_UNHOST_NKRO`               |         |Force NKRO off                            |
|`MAGIC_TOGGLE_NKRO`               |         |Turn NKRO on or off                       |
|`MAGIC_NO_GUI`                    |         |Disable the GUI keys (useful when gaming) |
|`MAGIC_UNNO_GUI`                  |         |Enable the GUI keys                       |
|`MAGIC_SWAP_ALT_GUI`              |`AG_SWAP`|Swap Alt and GUI on both sides (for macOS)|
|`MAGIC_UNSWAP_ALT_GUI`            |`AG_NORM`|Unswap Left Alt and Left GUI              |
|`MAGIC_TOGGLE_ALT_GUI`            |`AG_TOGG`|Toggle Left Alt and GUI swap              |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |         |Swap `\` and Backspace                    |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|         |Unswap `\` and Backspace                  |
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |         |Swap Left Control and Caps Lock           |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |         |Unswap Left Control and Caps Lock         |
|`MAGIC_SWAP_GRAVE_ESC`            |         |Swap <code>&#96;</code> and Escape        |
|`MAGIC_UNSWAP_GRAVE_ESC`          |         |Unswap <code>&#96;</code> and Escape      |
|`MAGIC_SWAP_LALT_LGUI`            |         |Swap Left Alt and Left GUI                |
|`MAGIC_UNSWAP_LALT_LGUI`          |         |Unswap Left Alt and Left GUI              |
|`MAGIC_SWAP_RALT_RGUI`            |         |Swap Right Alt and Right GUI              |
|`MAGIC_UNSWAP_RALT_RGUI`          |         |Unswap Right Alt and Right GUI            |

## Configuration

If you would like to change the hotkey assignments for Bootmagic, `#define` these in your `config.h` at either the keyboard or keymap level.

|Define                                  |Default      |Description                                        |
|----------------------------------------|-------------|---------------------------------------------------|
|`BOOTMAGIC_KEY_SALT`                    |`KC_SPACE`   |The Bootmagic key                                  |
|`BOOTMAGIC_KEY_SKIP`                    |`KC_ESC`     |Ignore Bootmagic configuration in EEPROM           |
|`BOOTMAGIC_KEY_EEPROM_CLEAR`            |`KC_BSPACE`  |Clear the EEPROM configuration                     |
|`BOOTMAGIC_KEY_BOOTLOADER`              |`KC_B`       |Enter the bootloader                               |
|`BOOTMAGIC_KEY_DEBUG_ENABLE`            |`KC_D`       |Toggle debugging over serial                       |
|`BOOTMAGIC_KEY_DEBUG_MATRIX`            |`KC_X`       |Toggle matrix debugging                            |
|`BOOTMAGIC_KEY_DEBUG_KEYBOARD`          |`KC_K`       |Toggle keyboard debugging                          |
|`BOOTMAGIC_KEY_DEBUG_MOUSE`             |`KC_M`       |Toggle mouse debugging                             |
|`BOOTMAGIC_KEY_SWAP_CONTROL_CAPSLOCK`   |`KC_LCTRL`   |Swap Left Control and Caps Lock                    |
|`BOOTMAGIC_KEY_CAPSLOCK_TO_CONTROL`     |`KC_CAPSLOCK`|Toggle treating Caps Lock as Left Control          |
|`BOOTMAGIC_KEY_SWAP_LALT_LGUI`          |`KC_LALT`    |Toggle swapping Left Alt and Left GUI (for macOS)  |
|`BOOTMAGIC_KEY_SWAP_RALT_RGUI`          |`KC_RALT`    |Toggle swapping Right Alt and Right GUI (for macOS)|
|`BOOTMAGIC_KEY_NO_GUI`                  |`KC_LGUI`    |Toggle the GUI keys (useful when gaming)           |
|`BOOTMAGIC_KEY_SWAP_GRAVE_ESC`          |`KC_GRAVE`   |Toggle swapping <code>&#96;</code> and Escape      |
|`BOOTMAGIC_KEY_SWAP_BACKSLASH_BACKSPACE`|`KC_BSLASH`  |Toggle swapping `\` and Backspace                  |
|`BOOTMAGIC_HOST_NKRO`                   |`KC_N`       |Toggle N-Key Rollover (NKRO)                       |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_0`         |`KC_0`       |Make layer 0 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_1`         |`KC_1`       |Make layer 1 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_2`         |`KC_2`       |Make layer 2 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_3`         |`KC_3`       |Make layer 3 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_4`         |`KC_4`       |Make layer 4 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_5`         |`KC_5`       |Make layer 5 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_6`         |`KC_6`       |Make layer 6 the default layer                     |
|`BOOTMAGIC_KEY_DEFAULT_LAYER_7`         |`KC_7`       |Make layer 7 the default layer                     |
