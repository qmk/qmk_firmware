pegasushoof keyboard firmware
=============================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent README.md](/README.md).

## Building

Download or clone the whole firmware and navigate to the `keyboard/pegasushoof` folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your `.hex` file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build all keymaps, simply run `make`, the `.hex` files will end up in the top directory.

### Specific Keymap
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>/keymap.c` in the `keymaps` folder, and see keymap document (you can find in top README.md) and existent keymap files.

To build the firmware binary hex file with a keymap just enter the keymap directory and type `make`:
```
$ cd keymaps/default
$ make
```
