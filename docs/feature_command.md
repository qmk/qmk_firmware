# Command (Formerly known as Magic)

Command is a way to change your keyboard's behavior without having to flash or unplug it to use [Bootmagic](feature_bootmagic.md). There is a lot of overlap between this functionality and the [Bootmagic Keycodes](feature_bootmagic.md). Whenever possible we encourage you to use that functionality instead of Command.

## Enabling Command

By default Command is disabled. You can enable it in your `rules.mk` file:

    COMMAND_ENABLE = yes

## Usage

To use Command you hold down the key combination defined by `IS_COMMAND`. By default that combination is both shift keys. While holding the key combination press the key corresponding to the command you want.

For example, to write the current QMK version to the QMK Toolbox console, you can press `Left Shift`+`Right Shift`+`V`.

## Configuration

The following values can be defined in `config.h` to control the behavior of Command.

|Define |Default | Description |
|-------|--------|-------------|
|`IS_COMMAND()`                      |`(keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))`|Key combination to activate Command|
|`MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS` |`true`                                                                |Do layer switching with Function row|
|`MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS` |`true`                                                                |Do layer switching with number keys.|
|`MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM`|`false`                                                               |Do layer switching with custom keys (`MAGIC_KEY_LAYER0..9` below.)|
|`MAGIC_KEY_HELP1`                   |`H`                                                                   |Show help.|
|`MAGIC_KEY_HELP2`                   |`SLASH`                                                               |Show help.|
|`MAGIC_KEY_DEBUG`                   |`D`                                                                   |Turn on debug mode.|
|`MAGIC_KEY_DEBUG_MATRIX`            |`X`                                                                   |Turn on matrix debugging.|
|`MAGIC_KEY_DEBUG_KBD`               |`K`                                                                   |Turn on keyboard debugging.|
|`MAGIC_KEY_DEBUG_MOUSE`             |`M`                                                                   |Turn on mouse debugging.|
|`MAGIC_KEY_VERSION`                 |`V`                                                                   |Write the QMK version to the console|
|`MAGIC_KEY_STATUS`                  |`S`                                                                   |Show the current keyboard status|
|`MAGIC_KEY_CONSOLE`                 |`C`                                                                   |Enable the Command Console|
|`MAGIC_KEY_LAYER0_ALT1`             |`ESC`                                                                 |Alternate access to layer 0|
|`MAGIC_KEY_LAYER0_ALT2`             |`GRAVE`                                                               |Alternate access to layer 0|
|`MAGIC_KEY_LAYER0`                  |`0`                                                                   |Change default layer to 0|
|`MAGIC_KEY_LAYER1`                  |`1`                                                                   |Change default layer to 1|
|`MAGIC_KEY_LAYER2`                  |`2`                                                                   |Change default layer to 2|
|`MAGIC_KEY_LAYER3`                  |`3`                                                                   |Change default layer to 3|
|`MAGIC_KEY_LAYER4`                  |`4`                                                                   |Change default layer to 4|
|`MAGIC_KEY_LAYER5`                  |`5`                                                                   |Change default layer to 5|
|`MAGIC_KEY_LAYER6`                  |`6`                                                                   |Change default layer to 6|
|`MAGIC_KEY_LAYER7`                  |`7`                                                                   |Change default layer to 7|
|`MAGIC_KEY_LAYER8`                  |`8`                                                                   |Change default layer to 8|
|`MAGIC_KEY_LAYER9`                  |`9`                                                                   |Change default layer to 9|
|`MAGIC_KEY_BOOTLOADER`              |`PAUSE`                                                               |Exit keyboard and enter bootloader|
|`MAGIC_KEY_LOCK`                    |`CAPS`                                                                |Lock the keyboard so nothing can be typed|
|`MAGIC_KEY_EEPROM`                  |`E`                                                                   |Erase EEPROM settings|
|`MAGIC_KEY_NKRO`                    |`N`                                                                   |Toggle NKRO on/off|
|`MAGIC_KEY_SLEEP_LED`               |`Z`                                                                   |Toggle LED when computer is sleeping on/off|
