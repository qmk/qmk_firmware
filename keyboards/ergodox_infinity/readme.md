# ErgoDox Infinity

The Infinity is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.  To flash them:

  - Make sure you are in the top-level qmk_firmware directory

  - Build the firmware with `make ergodox_infinity:keymapname`

  - Plug in the left hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make ergodox_infinity:keymapname:dfu-util`

  - Build right hand firmware with `make ergodox_infinity:keymapname MASTER=right`

  - Plug in the right hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make ergodox_infinity:keymapname:dfu-util MASTER=right`

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

## Infinity Master/Two Halves

The Infinity is two completely independent keyboards, that can connect together.
You have a few options in how you flash the firmware:

- Flash the left half, rebuild the firmware with "MASTER=right" and then flash
  the right half.  This allows you to plug in either half directly to the
  computer and is what the above instructions do.

- Flash the left half, then flash the same firmware on the right.  This only
  works when the left half is plugged directly to the computer and the keymap
  is mirrored.  It saves the small extra step of rebuilding with
  "MASTER=right".

- The same as the previous one but with "MASTER=right" when you build the
  firmware, then flash the same firmware to both halves.  You just have to
  directly connect the right half to the computer.

- For minor changes such as changing only the keymap without having updated
  any part of the firmware code itself, you can program only the MASTER half.

- It is safest to program both halves though.
