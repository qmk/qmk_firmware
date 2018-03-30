# ErgoDox EZ

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

  - {if desired, turn on Verbose mode: menu arrow/help/verbose info}

  - Load the .hex file into it {'Open Hex File'}.

  - Press the Reset button by inserting a paperclip gently into the reset hole in the top right corder. {or using the Reset key if already programmed}

  - Click the {'Program' down (Arrow, should be green when ready)} button in the Teensy app to download the firmware. {Menu options also work: arrow/operation/program}

  - {Click 'Reboot' (menu: arrow/operation/reboot) if the board did not do so automatically}

{To flash using Teensy Loader in Auto mode: [video instructions](https://www.youtube.com/watch?v=9PyiGUO9_KQ)

  - open teensy loader

  - load desired hex file

  - click auto button or choose auto from operation menu

  - press reset button on keyboard}

To flash with ´teensy-loader-cli´:

  - Build the firmware with `make keymapname`, for example `make default`

  - Run ´<path/to/>teensy_loader_cli -mmcu=atmega32u4 -w ergodox_ez_<keymap>.hex´

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

## Settings

You may want to enable QMK_KEYS_PER_SCAN because the Ergodox has a relatively
slow scan rate.

{annotations in curley braces are attempts to update instructions for Teensy Loader 1.4.  Original [file](https://raw.githubusercontent.com/qmk/qmk_firmware/master/keyboards/ergodox_ez/readme.md) }

