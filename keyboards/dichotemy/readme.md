Dichotemy Keyboard Firmware
======================

These configuration files were based off the Mitosis keyboard. This keyboard uses a completely different 'matrix scan' system to other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the keyboard halves - it also receives mouse pointer information from the keyboard halves, which is implemented through a new feature, "Pointing Device". The matrix.c file contains the code to poll the external microcontroller for the key matrix, and the keymap.c file contains similar code to obtain the mouse report. As long as the relavant functions in these files are not changed, all other QMK features are supported.

Build log of the keyboard can be found [here](http://google.com)

Hardware design files can be found [here](http://google.com)

Firmware for the nordic MCUs can be found [here](http://google.com)

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

Download or clone the whole firmware and navigate to the keyboards/atreus folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use `make dfu` to program your PCB once you hit the reset button. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make default`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top readme.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
