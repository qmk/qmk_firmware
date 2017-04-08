frosty_flake keyboard firmware
======================

This is the firmware for Rev. 20140521 of the Frosty Flake controller by [Bathroom Epiphanies](http://bathroomepiphanies.com/controllers/), a replacement controller for the [Cooler Master Quick Fire Rapid](http://www.coolermaster.com/peripheral/keyboards/quickfirerapid/).

The code was adapted from the [BathroomEpiphanies TMK Firmware](https://github.com/BathroomEpiphanies/epiphanies_tmk_keyboard/tree/master/be_controllers), but has been cleaned up to match the [schematic](https://deskthority.net/wiki/File:Frosty_Flake_Schematics.pdf) and gone through some minor refactoring for QMK.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

Download or clone the whole firmware and navigate to the keyboards/frosty_flake folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

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
