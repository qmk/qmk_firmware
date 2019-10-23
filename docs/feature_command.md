# Command

Command, formerly known as Magic, is a way to change your keyboard's behavior without having to flash or unplug it to use [Bootmagic](feature_bootmagic.md). There is a lot of overlap between this functionality and the [Bootmagic Keycodes](feature_bootmagic.md#keycodes). Wherever possible we encourage you to use that feature instead of Command.

On some keyboards Command is disabled by default. If this is the case, it must be explicitly enabled in your `rules.mk`:

```make
COMMAND_ENABLE = yes
```

## Usage

To use Command, hold down the key combination defined by the `IS_COMMAND()` macro. By default this is Left Shift+Right Shift. Then, press the key corresponding to the command you want. For example, to output the current QMK version to the QMK Toolbox console, press Left Shift+Right Shift+`V`.

## Configuration

If you would like to change the key assignments for Command, `#define` these in your `config.h` at either the keyboard or keymap level. All keycode assignments here must omit the `KC_` prefix.

|Define                              |Default                         |Description                                     |
|------------------------------------|--------------------------------|------------------------------------------------|
|`IS_COMMAND()`                      |`(get_mods() == MOD_MASK_SHIFT)`|The key combination to activate Command         |
|`MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS` |`true`                          |Set default layer with the Function row         |
|`MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS` |`true`                          |Set default layer with the number keys          |
|`MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM`|`false`                         |Set default layer with `MAGIC_KEY_LAYER0..9`    |
|`MAGIC_KEY_DEBUG`                   |`D`                             |Toggle debugging over serial                    |
|`MAGIC_KEY_DEBUG_MATRIX`            |`X`                             |Toggle key matrix debugging                     |
|`MAGIC_KEY_DEBUG_KBD`               |`K`                             |Toggle keyboard debugging                       |
|`MAGIC_KEY_DEBUG_MOUSE`             |`M`                             |Toggle mouse debugging                          |
|`MAGIC_KEY_CONSOLE`                 |`C`                             |Enable the Command console                      |
|`MAGIC_KEY_VERSION`                 |`V`                             |Print the running QMK version to the console    |
|`MAGIC_KEY_STATUS`                  |`S`                             |Print the current keyboard status to the console|
|`MAGIC_KEY_HELP`                    |`H`                             |Print Command help to the console               |
|`MAGIC_KEY_HELP_ALT`                |`SLASH`                         |Print Command help to the console (alternate)   |
|`MAGIC_KEY_LAYER0`                  |`0`                             |Make layer 0 the default layer                  |
|`MAGIC_KEY_LAYER0_ALT`              |`GRAVE`                         |Make layer 0 the default layer (alternate)      |
|`MAGIC_KEY_LAYER1`                  |`1`                             |Make layer 1 the default layer                  |
|`MAGIC_KEY_LAYER2`                  |`2`                             |Make layer 2 the default layer                  |
|`MAGIC_KEY_LAYER3`                  |`3`                             |Make layer 3 the default layer                  |
|`MAGIC_KEY_LAYER4`                  |`4`                             |Make layer 4 the default layer                  |
|`MAGIC_KEY_LAYER5`                  |`5`                             |Make layer 5 the default layer                  |
|`MAGIC_KEY_LAYER6`                  |`6`                             |Make layer 6 the default layer                  |
|`MAGIC_KEY_LAYER7`                  |`7`                             |Make layer 7 the default layer                  |
|`MAGIC_KEY_LAYER8`                  |`8`                             |Make layer 8 the default layer                  |
|`MAGIC_KEY_LAYER9`                  |`9`                             |Make layer 9 the default layer                  |
|`MAGIC_KEY_BOOTLOADER`              |`B`                             |Jump to bootloader                              |
|`MAGIC_KEY_BOOTLOADER_ALT`          |`ESC`                           |Jump to bootloader (alternate)                  |
|`MAGIC_KEY_LOCK`                    |`CAPS`                          |Lock the keyboard so nothing can be typed       |
|`MAGIC_KEY_EEPROM`                  |`E`                             |Print stored EEPROM config to the console       |
|`MAGIC_KEY_EEPROM_CLEAR`            |`BSPACE`                        |Clear the EEPROM                                |
|`MAGIC_KEY_NKRO`                    |`N`                             |Toggle N-Key Rollover (NKRO)                    |
|`MAGIC_KEY_SLEEP_LED`               |`Z`                             |Toggle LED when computer is sleeping            |
