# ErgoDox EZ

The Ez uses the [Teensy Loader](https://www.pjrc.com/teensy/loader.html).

Linux users need to modify udev rules as described on the [Teensy
Linux page].  Some distributions provide a binary, maybe called
`teensy-loader-cli`.

[Teensy Linux page]: https://www.pjrc.com/teensy/loader_linux.html

To flash the firmware:

  - Build the firmware with `make <keyboardname>:<keymapname>`, for example `make ergodox_ez:default`

  - This will result in a hex file called `ergodox_ez_keymapname.hex`, e.g.
    `ergodox_ez_default.hex`

  - Start the teensy loader.

  - Load the .hex file into it.

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corner.

  - Click the button in the Teensy app to download the firmware.

See also [video demonstration](https://www.youtube.com/watch?v=9PyiGUO9_KQ) using Teensy in auto mode.

To flash with ´teensy-loader-cli´:

  - Build the firmware with `make keymapname`, for example `make default`

  - Run ´<path/to/>teensy_loader_cli -mmcu=atmega32u4 -w ergodox_ez_<keymap>.hex´

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

## Settings

You may want to enable QMK_KEYS_PER_SCAN because the Ergodox has a relatively
slow scan rate.
