xd75 keyboard firmware
======================

The XD75Re is a 15x5 full-grid ortholinear keyboard manufactured by XIUDI. This port of the QMK firmware is my first shot at using QMK, so if you see any features done wrong (or just plain missing), feel free to fix them and put in a pull request!

## Quantum MK Firmware

For more info on this firmware (and how to make it your own), head over to [qmk.fm](http://qmk.fm).

## Building

Download or clone the whole firmware and navigate to the keyboards/xd75 folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make default`.

### Other Keymaps

The "default" keymap included is basically the OLKB Atomic keymap with a few buttons added for RGB underglow control. This should be usable as a starting point, but most people will be best served creating their own keymap and flashing it - more info on creating your own keymap is available in [the official QMK documentation](https://docs.qmk.fm).

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
