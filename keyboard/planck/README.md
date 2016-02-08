Planck keyboard firmware
======================
DIY/Assembled compact ortholinear 40% keyboard by [Ortholinear Keyboards](http://ortholinearkeyboards.com).

## Quantum MK Firmware

For the full Quantum feature list, see [the parent README.md](/README.md).

## Building

Download or clone the whole firmware and navigate to the keyboard/planck folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use `make dfu` to program your PCB once you hit the reset button. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top README.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
Keymaps follow the format **__<name\>.c__** and are stored in the `keymaps` folder.

### Notable forks (which some of the keymap files are from)
- [Shane's Fork](https://github.com/shanecelis/tmk_keyboard/tree/master/keyboard/planck)
- [Pierre's Fork](https://github.com/pcarrier/tmk_keyboard/blob/pcarrier/planck/keyboard/gh60/keymap_planck.c)
- [Nathan's Fork](https://github.com/nathanrosspowell/tmk_keyboard/tree/planck-jack/keyboard/planck)
- [Matthew's Fork](https://github.com/pepers/tmk_keyboard/tree/master/keyboard/planck_grid)
