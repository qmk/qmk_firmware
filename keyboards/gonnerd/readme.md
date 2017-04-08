GON NerD keyboard firmware
======================

## Changing Bootloader

It's not possible to simply flash this firmware on the GON NerD keyboard as the original bootloader does not support DFU connections.

It is possible to change the bootloader of the GON NerD with an ISP programmer. A guide on how to change the bootloader on your GON NerD can be found here:
[Converting NerD60 to TMK](https://deskthority.net/wiki/Converting_NerD60_to_TMK). After changing the bootloader you can flash your QMK keymap onto the keyboard.

_After changing the bootloader on your GON NerD PCB you will not be able to go back to the original firmware and the official configuration software will
not work anymore. You will lose your warranty and official support from GON!_

## Reset button

To run the `make dfu` command to flash keymaps onto the board, you need to put the board into DFU mode. As the GON NerD PCBs do not have a reset button on the board to put it into DFU mode, be sure to include a `RESET` button on your keymap. Otherwise you'll have to unscrew your keyboard from the case and short the GND and RST pins.

## Building

Download or clone the whole firmware and navigate to the keyboards/gonnerd folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make default`.

### Other Keymaps

Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
