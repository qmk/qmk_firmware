ErgoDox
==

The ErgoDox is a split ergonomic keyboard originally developed by Dominic "Dox" Beauchamp.

* The **ErgoDox EZ** is a Teensy-based split mechanical keyboard, sold assembled and with warranty at [ErgoDox-EZ.com](https://ergodox-ez.com).
* The **ErgoDox Infinity** is an ARM-based split mechanical keyboard, sold from time to time in kit form at [MassDrop.com](https://www.massdrop.com/buy/infinity-ergodox)

The ErgoDox EZ code is maintained by Erez Zukerman and is officially supported by the EZ -- the keyboard ships running QMK from the factory.

The ErgoDox Infinity code is maintained by Fredizzimo, as a community contribution.

## Standard Build Instructions

To build QMK for the ErgoDox, see the official [build guide](/docs/build_guide.md).

## Additional resources

A graphical configurator for the ErgoDox EZ is available at [configure.ergodox-ez.com](http://configure.ergodox-ez.com). It outputs QMK-compiled binaries, as well as source code for your layout, which you can use as a jumping-off point to further customize in QMK.

# Flashing Firmware

## ErgoDox EZ

The Ez uses the [Teensy Loader](https://www.pjrc.com/teensy/loader.html).

Linux users need to modify udev rules as described on the [Teensy
Linux page].  Some distributions provide a binary, maybe called
`teensy-loader-cli`.

[Teensy Linux page]: https://www.pjrc.com/teensy/loader_linux.html

To flash the firmware:

  - Build the firmware with `make keymapname`, for example `make default`
  - This will result in a hex file called `ergodox_ez_keymapname.hex`, e.g.
    `ergodox_ez_default.hex`

  - Start the teensy loader.

  - Load the .hex file into it.

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

  - Click the button in the Teensy app to download the firmware.

To flash with ´teensy-loader-cli´:

  - Build the firmware with `make keymapname`, for example `make default`

  - Run ´<path/to/>teensy_loader_cli -mmcu=atmega32u4 -w ergodox_ez_<keymap>.hex´

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

## ErgoDox Infinity

The Infinity is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.  To flash them:

  - Build the firmware with `make infinity-keymapname`

  - Plug in the left hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make infinity-keymapname-dfu-util`

  - Build right hand firmware with `make infinity-keymapname MASTER=right`

  - Plug in the right hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make infinity-keymapname-dfu-util MASTER=right`

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

### Infinity Master/Two Halves

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
  It is safest to program both halves though.

## ErgoDone

The ErgoDone uses its own HID bootloader and needs to be flashed using the [TKG Toolkit](https://github.com/kairyu/tkg-toolkit).

  - Build the firmware with `make ergodone-keymapname`

  - While plugging in the USB cable, hold the two right-most keys on the left half of the ErgoDone to enter FLASH mode.

  - Use the utility from [TKG Toolkit](https://github.com/kairyu/tkg-toolkit) to flash the keyboard: `hid_bootloader_cli -mmcu=atmega32u4 ergodox_ergodone_keymapname.hex`
