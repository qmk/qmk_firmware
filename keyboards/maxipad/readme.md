<<<<<<< HEAD
Maxipad keyboard firmware
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).
=======
## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

>>>>>>> a06115df19a74d39b08758472b221e630c3680d3

## Building

If you are using a pro micro then make sure to enable USE_PRO_MICRO in the makefile

Download or clone the whole firmware and navigate to the keyboards/maxipad folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
<<<<<<< HEAD
To build with the default keymap, simply run `make default`.
=======

To build with the default keymap, simply run `make`.

>>>>>>> a06115df19a74d39b08758472b221e630c3680d3

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top readme.md) and existent keymap files.

<<<<<<< HEAD
=======
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

>>>>>>> a06115df19a74d39b08758472b221e630c3680d3
To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```
<<<<<<< HEAD
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
=======

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.

>>>>>>> a06115df19a74d39b08758472b221e630c3680d3
