Honeycomb Keyboard Firmware
======================

These configuration files use a completely different 'matrix scan' system than other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the macropad - it also receives rotary encoder information from the macropad. The matrix.c file contains the code to poll the external microcontroller for the key matrix, and the keymap.c file contains example code for encoder use. As long as the relevant functions in these files are not changed, all other QMK features are supported.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

Follow the QMK guide for this or ask in their discord.

Depending on which keymap you would like to use, you will have to compile slightly differently.


### Other Keymaps
You are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top readme.md) and existent keymap files.

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
