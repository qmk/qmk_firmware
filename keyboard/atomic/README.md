Atomic keyboard firmware
======================
DIY/Assembled ortholinear 60% keyboard by [Ortholinear Keyboards](http://ortholinearkeyboards.com).

## Quantum MK Firmware

For the full Quantum feature list, see [the parent README.md](/README.md).

## Building

Download or clone the whole firmware and navigate to the keyboard/atomic folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use `make dfu` to program your PCB once you hit the reset button. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document (you can find in top README.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
Keymaps follow the format **__keymap\_\<name\>.c__** and are stored in the `keymaps` folder.
