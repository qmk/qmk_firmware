roadkit keyboard firmware
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the QMK Wiki](https://github.com/qmk/qmk_firmware/wiki).

## Building

Download or clone the whole firmware and navigate to the `keyboards/roadkit` folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex. You can then use the programmer of your choice to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make default`. For the roadkit, the default layout is a standard numpad layout.

### Singles

The singles layout for the roadkit corresponds to the configuration where only 1u keys are used and there are 16 of them on the board. To build the singles keymap, run `make singles`.

### Other Keymaps

Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`
