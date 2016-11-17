maxipad keyboard firmware
======================

## Quantum MK Firmware

<<<<<<< HEAD
For the full Quantum feature list, see [the parent readme](/).
=======
For the full Quantum feature list, see [the parent readme.md](/doc/readme.md).
>>>>>>> bce6e52391da7c5f620c96a91857940f0dee19df

## Building

Download or clone the whole firmware and navigate to the keyboards/maxipad folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

<<<<<<< HEAD
To build with the default keymap, simply run `make default`.
=======
To build with the default keymap, simply run `make`.
>>>>>>> bce6e52391da7c5f620c96a91857940f0dee19df

### Other Keymaps

Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

<<<<<<< HEAD
To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
=======
To build the firmware binary hex file with a keymap just do `make` with `keymap` option like:

```
$ make keymap=[default|jack|<name>]
```

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`
>>>>>>> bce6e52391da7c5f620c96a91857940f0dee19df
