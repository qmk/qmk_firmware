Infinity 60% keyboard firmware
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Keymaps

Several versions of keymaps are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`


## Compiling

Download or clone the whole firmware and navigate to the keyboards/infinity60 folder. Once your dev env is setup, you'll be able to use the `make` command to both compile your keymap and flash it to your keyboard.

To just compile, which generates the output files in the `.build` folder at the root of the repository, run `make keymap`, where keymap is the name of the keymap that you want to compile.

## Flashing

To flash the firmware to the keyboard

1. First press the flash button on the bottom of the keyboard. If you already have a flah button mapped in a keyboard layout running on the keyboard, you can also use that.
2. Then run `make keymap-dfu-util`, where keymap is the name of the keymap you want to flash. On Linux based operating systems you might need to run the comamnd as root, for example `sudo make keymap-dfu-util` on Ubuntu.

**Tip** `make keymap-dfu-util` will also compile the keymap if needed, so you can skip the compilation step if you want to.

