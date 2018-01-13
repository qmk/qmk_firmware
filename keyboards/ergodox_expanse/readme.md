# ErgoDox Expanse

The ErgoDox Expanse is a DIY hand-wired version of the EdgoDox Infinity using the Teensy 3.2 board as the controller. The display used is a 128x64 OLED display with the SSD1306 controller instead of the Infinty LCD. RGB backlight support is planned but not yet tested.

The only keymap tested is the 'ballanux' one, intended for spanish layout, but any other ergodox keymap should work.

![Ergodox Expanse](https://i.imgur.com/h3It6Bm.jpg)

## Hardware instructions

The hardware design files an instructions are located at the following repository:

[https://github.com/sballano/ergodox_expanse](https://github.com/sballano/ergodox_expanse)

## Building and flashing


The Expanse is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.

Instead of using the Infinity bootloader we wil be using the Teensy Loader that can be found at:

[https://www.pjrc.com/teensy/loader_cli.html](https://www.pjrc.com/teensy/loader_cli.html)


To flash them:

  - Make sure you are in the top-level qmk_firmware directory
  - Build the firmware with `make ergodox_expanse:keymapname`
  - Go to the build directory `cd .build`
  - Copy the teensy_loader_cli in this folder.
  - Plug in the left hand keyboard only.
  - Install the firmware with `teensy_loader_cli -mmcu=mk20dx256 -w ergodox_expanse_ballanux.hex`
  - Press the reset button on the Teensy 3.2 board; it will flash in a few seconds.
  - Go to the top-level qmk_firmware directory `cd ..`
  - Build right hand firmware with `make ergodox_expanse:keymapname MASTER=right`
  - Plug in the right hand keyboard only.
  - Go to the build directory `cd .build`
  - Install the firmware with `teensy_loader_cli -mmcu=mk20dx256 -w ergodox_expanse_ballanux.hex`
  - Press the reset button on the Teensy 3.2 board; it will flash in a few seconds.

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

## Expanse Master/Two Halves

The Expanse is two completely independent keyboards, that can connect together.
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
