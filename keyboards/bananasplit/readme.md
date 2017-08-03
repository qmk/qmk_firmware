Bananasplit keyboard firmware
======================

The BananaSplit60 is a custom 60% keyboard with a split space bar. It was conceived by Arhipio and evangs. It was ported to QMK by Coloneljesus.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

Download or clone the whole firmware and navigate to the keyboards/bananasplit folder. Once your dev env is set up, you'll be able to type `make` to generate your .hex which can then be flashed to the keyboard.

### Default

To build with the default keymap, simply run `make default`.

### Other Keymaps

You are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
