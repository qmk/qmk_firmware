# ErgoDox Infinity

The Infinity is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.  To flash them:

  - Make sure you are in the top-level qmk_firmware directory

  - Build the firmware with `make input_club/ergodox_infinity:keymapname`

  - Plug in the left hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make input_club/ergodox_infinity:keymapname:dfu-util`

  - Plug in the right hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make input_club/ergodox_infinity:keymapname:dfu-util`

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

## Infinity Two Halves

The Infinity is two completely independent keyboards, that can connect together.
You have a few options in how you flash the firmware:

- Add `#define EE_HANDS` to your config.h, initialize the EEPROM values (see below),
  and then flash the same firmware to both halves.

- Flash with the instructions above, which assume the left hand is connected to USB.

- For minor changes such as changing only the keymap without having updated
  any part of the firmware code itself, you can program only the half connected to USB,
  but it is safest to program both halves.

### EE_HANDS initialization

To initialize the EEPROM values for `EE_HANDS` to work properly, these steps should work.
They only need to be done once, unless you reset the EEPROM later.

  - Plug in the left keyboard half to the computer, and press its program button.

  - Flash the left half with `make input_club/ergodox_infinity:default:dfu-util-split-left`
    (If you need to use a different method to flash your keyboard, still run this command,
    and abort it with Ctrl+C when the flashing attempts starts to print errors,
    then flash the built firmware).

  - On the left half, press the top vertical 1.5U key (second from the top in the rightmost column) once,
    then the 1U key at the bottom in the opposite corner (bottom left corner).

  - Plug in the right keyboard half to the computer, and press its program button.

  - Flash the right half with `make input_club/ergodox_infinity:default:dfu-util-split-right`

  - On the right half, press the top vertical 1.5U key (second from the top in the leftmost column) once,
    then the 1U key at the bottom in the opposite corner (bottom right corner).

  - Add `#define EE_HANDS` to the config.h file of your keymap, and build your firmware using
    `make input_club/ergodox_infinity:keymapname`.

  - After this, you can flash both halves with the same firmware, _without_ risking a mirrored keyboard when connected the wrong way.
    If you reset your EEPROM later, you'll have to follow these steps again, though.

