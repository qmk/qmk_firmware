fivethirteen keyboard firmware
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/doc/README.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/handwired/fivethirteen folder.
Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use
the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make`.

### Other Keymaps

To build the firmware binary hex file with a keymap just do `make` with `keymap` option like:

```
$ make keymap=[default|jack|<name>]
```

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`
