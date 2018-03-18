# Bootmagic and Magic Keycodes

There are 3 separate but related features that allow you to change the behavior of your keyboard without reflashing. While each of them have similar functionality you access that functionality in different ways depending on how your keyboard is configured.

Bootmagic is a system for configuring your keyboard while it initializes. To trigger a Bootmagic command you hold down the bootmagic key (`KC_SPACE` on most keyboards) and one or more command keys.

Bootmagic Keycodes allow you to access the Bootmagic functionality after your keyboard has initialized. To use Bootmagic Keycodes you assign keycodes starting with `MAGIC_`, much in the same way you define any other key.

Command is a feature that allows you to control different aspects of your keyboard. Command used to be called Magic. Command is typically accessed by holding Left and Right Shift at the same time, although that can be customized. While it shares some functionality with Bootmagic it also allows you to access functionality that Bootmagic does not. For more information see the (Command)[feature_command.md) documentation page.

## Enabling Bootmagic

Bootmagic is disabled by default. To use Bootmagic you need to enable it in your `rules.mk` file:

    BOOTMAGIC_ENABLE = yes

## Bootmagic Hotkeys and Keycodes

This table describes the default Hotkeys for Bootmagic and the Keycodes for Magic. These may be overriden at the Keyboard or Keymap level. Some functionality is not available in both methods.

To use the Hotkey hold down `BOOTMAGIC_KEY_SALT` (`KC_SPACE` by default) and the Hotkey while plugging in your keyboard. To use the Keycode assign that keycode to a layer. For example, if you hold down Space+B while plugging in most keyboards, you will enter bootloader mode.

|Hotkey     |Keycode                           |Description                                             |
|-----------|----------------------------------|--------------------------------------------------------|
|`ESC`      |                                  |Skip bootmagic and saved eeprom configuration           |
|`B`        |`RESET`                           |Enter bootloader instead of firmware                    |
|`D`        |`DEBUG`                           |Enable debugging (writes messages to serial)            |
|`X`        |                                  |Enable matrix debugging                                 |
|`K`        |                                  |Enable keyboard debugging                               |
|`M`        |                                  |Enable mouse debugging                                  |
|`BACKSPACE`|                                  |Clear the saved settings from flash                     |
|`CAPSLOCK` |`MAGIC_CAPSLOCK_TO_CONTROL`       |Treat `Capslock` as `Control`                           |
|           |`MAGIC_UNCAPSLOCK_TO_CONTROL`     |Stop treating CapsLock as Control                       |
|`LCTRL`    |`MAGIC_SWAP_CONTROL_CAPSLOCK`     |Swap `Control` and `Capslock`                           |
|           |`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |Unswap Left Control and Caps Lock                       |
|           |`MAGIC_SWAP_ALT_GUI`              |Swap Alt and GUI on both sides                          |
|           |`MAGIC_UNSWAP_ALT_GUI`            |Unswap Left Alt and GUI                                 |
|`LALT`     |`MAGIC_SWAP_LALT_LGUI`            |Swap Left `Alt` and `GUI`, e.g. for OSX Opt and Cmd     |
|           |`MAGIC_UNSWAP_LALT_LGUI`          |Unswap Left Alt and GUI                                 |
|`RALT`     |`MAGIC_SWAP_RALT_RGUI`            |Swap Right `Alt` and `GUI`                              |
|           |`MAGIC_UNSWAP_RALT_RGUI`          |Unswap Right Alt and GUI                                |
|`LGUI`     |`MAGIC_NO_GUI`                    |Disable GUI key - e.g. disable Windows key during gaming|
|           |`MAGIC_UNNO_GUI`                  |Enable the GUI key                                      |
|`GRAVE`    |`MAGIC_SWAP_GRAVE_ESC`            |Swap `\`~` and `ESC`                                    |
|           |`MAGIC_UNSWAP_GRAVE_ESC`          |Unswap `\`~` and Escape                                 |
|`BACKSLASH`|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |Swap Blackslash and Backspace                           |
|           |`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|Unswap Backslash and Backspace                          |
|`N`        |`MAGIC_HOST_NKRO`                 |Force N-Key Rollover (NKRO) on                          |
|           |`MAGIC_UNHOST_NKRO`               |Force NKRO off                                          |
|           |`MAGIC_TOGGLE_NKRO`               |Toggle NKRO on or off                                   |
|`0`        |`DF(0)`                           |Make Layer 0 the default layer at bootup                |
|`1`        |`DF(1)`                           |Make Layer 1 the default layer at bootup                |
|`2`        |`DF(2)`                           |Make Layer 2 the default layer at bootup                |
|`3`        |`DF(3)`                           |Make Layer 3 the default layer at bootup                |
|`4`        |`DF(4)`                           |Make Layer 4 the default layer at bootup                |
|`5`        |`DF(5)`                           |Make Layer 5 the default layer at bootup                |
|`6`        |`DF(6)`                           |Make Layer 6 the default layer at bootup                |
|`7`        |`DF(7)`                           |Make Layer 7 the default layer at bootup                |

## Bootmagic Configuration

When setting up your keyboard and/or keymap there are a number of `#define`s that control the behavior of Bootmagic. To use these put them in your `config.h`, either at the keyboard or keymap level.

|Define |Default|Description |
|-------|-------|------------|
|`BOOTMAGIC_KEY_SALT`|`KC_SPACE`|The key to hold down to trigger Bootmagic during initialization.|
|`BOOTMAGIC_KEY_SKIP`|`KC_ESC`|The Hotkey to ignore saved eeprom configuration.|
|`BOOTMAGIC_KEY_EEPROM_CLEAR`|`KC_BSPACE`|The hotkey to clear the saved eeprom configuration.|
|`BOOTMAGIC_KEY_BOOTLOADER`|`KC_B`|The hotkey to enter the bootloader.|
|`BOOTMAGIC_KEY_DEBUG_ENABLE`|`KC_D`|The hotkey to enable debug mode.|
|`BOOTMAGIC_KEY_DEBUG_MATRIX`|`KC_X`|The hotkey to enable matrix debugging mode.|
|`BOOTMAGIC_KEY_DEBUG_KEYBOARD`|`KC_K`|The hotkey to enable keyboard debugging mode.|
|`BOOTMAGIC_KEY_DEBUG_MOUSE`|`KC_M`|The hotkey to enable mouse debugging mode.|
|`BOOTMAGIC_KEY_SWAP_CONTROL_CAPSLOCK`|`KC_LCTRL`||
|`BOOTMAGIC_KEY_CAPSLOCK_TO_CONTROL`|`KC_CAPSLOCK`||
|`BOOTMAGIC_KEY_SWAP_LALT_LGUI`|`KC_LALT`||
|`BOOTMAGIC_KEY_SWAP_RALT_RGUI`|`KC_RALT`||
|`BOOTMAGIC_KEY_NO_GUI`|`KC_LGUI`||
|`BOOTMAGIC_KEY_SWAP_GRAVE_ESC`|`KC_GRAVE`||
|`BOOTMAGIC_KEY_SWAP_BACKSLASH_BACKSPACE`|`KC_BSLASH`||
|`BOOTMAGIC_HOST_NKRO`|`KC_N`||
|`BOOTMAGIC_KEY_DEFAULT_LAYER_0`|`KC_0`|Hotkey to set Layer 0 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_1`|`KC_1`|Hotkey to set Layer 1 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_2`|`KC_2`|Hotkey to set Layer 2 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_3`|`KC_3`|Hotkey to set Layer 3 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_4`|`KC_4`|Hotkey to set Layer 4 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_5`|`KC_5`|Hotkey to set Layer 5 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_6`|`KC_6`|Hotkey to set Layer 6 as the default layer|
|`BOOTMAGIC_KEY_DEFAULT_LAYER_7`|`KC_7`|Hotkey to set Layer 7 as the default layer|
