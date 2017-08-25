GON NerD
========

A Korean Custom TKL.

Keyboard Maintainer: QMK Community
Hardware Supported: GON NerD TKL PCB
Hardware Availability: http://www.gonskeyboardworks.com/pcbs-and-controllers/60-nerd-tkl-ver20-pcb.html

Make example for this keyboard (after setting up your build environment):

    make gonnerd-default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

## Changing Bootloader

It's not possible to simply flash this firmware on the GON NerD keyboard as the original bootloader does not support DFU connections.

It is possible to change the bootloader of the GON NerD with an ISP programmer. A guide on how to change the bootloader on your GON NerD can be found here:
[Converting NerD60 to TMK](https://deskthority.net/wiki/Converting_NerD60_to_TMK). After changing the bootloader you can flash your QMK keymap onto the keyboard.

_After changing the bootloader on your GON NerD PCB you will not be able to go back to the original firmware and the official configuration software will
not work anymore. You will lose your warranty and official support from GON!_

## Reset button

To run the `make dfu` command to flash keymaps onto the board, you need to put the board into DFU mode. As the GON NerD PCBs do not have a reset button on the board to put it into DFU mode, be sure to include a `RESET` button on your keymap. Otherwise you'll have to unscrew your keyboard from the case and short the GND and RST pins.
