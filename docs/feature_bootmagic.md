# Bootmagic Lite :id=bootmagic-lite

The Bootmagic Lite feature that only handles jumping into the bootloader. This is great for boards that don't have a physical reset button, giving you a way to jump into the bootloader

On some keyboards Bootmagic Lite is disabled by default. If this is the case, it must be explicitly enabled in your `rules.mk` with:

```make
BOOTMAGIC_ENABLE = yes
```

Additionally, you may want to specify which key to use. This is especially useful for keyboards that have unusual matrices. To do so, you need to specify the row and column of the key that you want to use. Add these entries to your `config.h` file:

```c
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1
```

By default, these are set to 0 and 0, which is usually the "ESC" key on a majority of keyboards.

And to trigger the bootloader, you hold this key down when plugging the keyboard in. Just the single key.

!> Using Bootmagic Lite will **always reset** the EEPROM, so you will lose any settings that have been saved.

## Split Keyboards

When handedness is predetermined via an option like `SPLIT_HAND_PIN`, you might need to configure a different key between halves. To do so, add these entries to your `config.h` file:

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

You can additional feature here. For instance, resetting the EEPROM or requiring additional keys to be pressed to trigger Bootmagic Lite. Keep in mind that `bootmagic_lite` is called before a majority of features are initialized in the firmware.

## Addenda

To manipulate settings that were formerly configured through the now-deprecated full Bootmagic feature, see [Magic Keycodes](keycodes_magic.md).

The Command feature, formerly known as Magic, also allows you to control different aspects of your keyboard. While it shares some functionality with Magic Keycodes, it also allows you to do things that Magic Keycodes cannot, such as printing version information to the console. For more information, see [Command](feature_command.md).
