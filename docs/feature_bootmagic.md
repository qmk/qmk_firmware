# Bootmagic

There are three separate but related features that allow you to change the behavior of your keyboard without reflashing. While each of them have similar functionality, it is accessed in different ways depending on how your keyboard is configured.

**Bootmagic** is a system for configuring your keyboard while it initializes. To trigger a Bootmagic command, hold down the Bootmagic key and one or more command keys.

**Bootmagic Keycodes** are prefixed with `MAGIC_`, and allow you to access the Bootmagic functionality *after* your keyboard has initialized. To use the keycodes, assign them to your keymap as you would any other keycode.

**Command**, formerly known as **Magic**, is another feature that allows you to control different aspects of your keyboard. While it shares some functionality with Bootmagic, it also allows you to do things that Bootmagic does not, such as printing version information to the console. For more information, see [Command](feature_command.md).

On some keyboards Bootmagic is disabled by default. If this is the case, it must be explicitly enabled in your `rules.mk` with:

```make
BOOTMAGIC_ENABLE = full
```

?> You may see `yes` being used in place of `full`, and this is okay. However, `yes` is deprecated, and ideally `full` (or `lite`) should be used instead.

Additionally, you can use [Bootmagic Lite](#bootmagic-lite) (a scaled down, very basic version of Bootmagic) by adding the following to your `rules.mk` file:

```make
BOOTMAGIC_ENABLE = lite
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
|`L`               |Set "Left Hand" for EE_HANDS handedness      |
|`R`               |Set "Right Hand" for EE_HANDS handedness     |
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

## Keycodes :id=keycodes

|Key                               |Aliases  |Description                                                               |
|----------------------------------|---------|--------------------------------------------------------------------------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`     |`CL_SWAP`|Swap Caps Lock and Left Control                                           |
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`   |`CL_NORM`|Unswap Caps Lock and Left Control                                         |
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
|`MAGIC_SWAP_GRAVE_ESC`            |`GE_SWAP`|Swap <code>&#96;</code> and Escape                                        |
|`MAGIC_UNSWAP_GRAVE_ESC`          |`GE_NORM`|Unswap <code>&#96;</code> and Escape                                      |
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`  |`BS_SWAP`|Swap `\` and Backspace                                                    |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|`BS_NORM`|Unswap `\` and Backspace                                                  |
|`MAGIC_HOST_NKRO`                 |`NK_ON`  |Enable N-key rollover                                                     |
|`MAGIC_UNHOST_NKRO`               |`NK_OFF` |Disable N-key rollover                                                    |
|`MAGIC_TOGGLE_NKRO`               |`NK_TOGG`|Toggle N-key rollover                                                     |
|`MAGIC_EE_HANDS_LEFT`             |`EH_LEFT`|Set the master half of a split keyboard as the left hand (for `EE_HANDS`) |
|`MAGIC_EE_HANDS_RIGHT`            |`EH_RGHT`|Set the master half of a split keyboard as the right hand (for `EE_HANDS`)|

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
|`BOOTMAGIC_KEY_EE_HANDS_LEFT`           |`KC_L`       |Set "Left Hand" for EE_HANDS handedness            |
|`BOOTMAGIC_KEY_EE_HANDS_RIGHT`          |`KC_R`       |Set "Right Hand" for EE_HANDS handedness           |
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

# Bootmagic Lite :id=bootmagic-lite

In addition to the full blown Bootmagic feature, is the Bootmagic Lite feature that only handles jumping into the bootloader. This is great for boards that don't have a physical reset button but you need a way to jump into the bootloader, and don't want to deal with the headache that Bootmagic can cause.

To enable this version of Bootmagic, you need to enable it in your `rules.mk` with:

```make
BOOTMAGIC_ENABLE = lite
```

Additionally, you may want to specify which key to use. This is especially useful for keyboards that have unusual matrices. To do so, you need to specify the row and column of the key that you want to use. Add these entries to your `config.h` file:

```c
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1
```

By default, these are set to 0 and 0, which is usually the "ESC" key on a majority of keyboards.

And to trigger the bootloader, you hold this key down when plugging the keyboard in. Just the single key.

!> Using bootmagic lite will **always reset** the EEPROM, so you will lose any settings that have been saved.

## Split Keyboards

When handedness is predetermined via an option like `SPLIT_HAND_PIN`, you might need to configure a different key between halves. This To do so, add these entries to your `config.h` file:

```c
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 1
```

By default, these values are not set.

## Advanced Bootmagic Lite

The `bootmagic_lite` function is defined weakly, so that you can replace this in your code, if you need. A great example of this is the Zeal60 boards that have some additional handling needed.

To replace the function, all you need to do is add something like this to your code:

```c
void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
      // Jump to bootloader.
      bootloader_jump();
    }
}
```

You can additional feature here. For instance, resetting the eeprom or requiring additional keys to be pressed to trigger bootmagic. Keep in mind that `bootmagic_lite` is called before a majority of features are initialized in the firmware.
