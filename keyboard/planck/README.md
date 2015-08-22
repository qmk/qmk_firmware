Planck keyboard firmware
======================
DIY/Assembled compact ortholinear 40% keyboard by [Ortholinear Keyboards](http://ortholinearkeyboards.com).

## OLKB Keymap
You have access to a bunch of goodies:

- Use `LSFT()`, `LCTL()`, et. al. (listed in keymap_common.h) as modifiers for keys (daisy-chain-able)
- Use `FUNC(1)` instead of `FN1` (etc.) to access the function layers beyond the 32 function layer limit
- Use `CM_F` instead of `KC_F` to get the ColeMak equivilent for shortcuts (maps backwards)
- Use `MACRODOWN()` instead of `MACRO()` to easily make a keydown macro (`CM_*` works here too)

### Some notes on usage:

- The `KEYMAP()` macro is unable to be used due to the bitwise modifications that take place - refer to extended_keymap_jack.c to see how to set things up with the `KC_` prefix
- Keep an eye on the Makefile - this needs to include the correct files to work
- Don't forget to use `const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {` instead of the 8bit equivilent

## Build

Follow [this guide](http://deskthority.net/workshop-f7/how-to-build-your-very-own-keyboard-firmware-t7177.html) to setup your development environment before anything else. Abbreviated instructions are provide at the [bottom of this document](https://github.com/rswiernik/tmk_keyboard/tree/rswiernik_dev/keyboard/planck#environment-setup)

Download the whole firmware [here](https://github.com/jackhumbert/tmk_keyboard/archive/master.zip) and navigate to the keyboard/planck folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex that you can load with the Teensy app onto your Planck (once you've hit reset/shorted GND & RST). 

Depending on which keymap you would like to use, you will have to compile slightly differently.

####Default
To build with the default keymap, simply move to the tmk\_keyboard/keyboard/planck/ and run `make` as follows:
```
$ make
```

## Keymap
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document (you can find in top README.md) and existent keymap files.
    
####**Keymaps**

To build the firmware binary hex file with an extended keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
_The only applicable keymaps will work with this option._ Keymaps follow the format **__keymap\_\<name\>.c__** and are stored in the `keymaps` folder.

## Notable TMK forks (which some of the keymap files are from)
- [Shane's Fork](https://github.com/shanecelis/tmk_keyboard/tree/master/keyboard/planck)
- [Pierre's Fork](https://github.com/pcarrier/tmk_keyboard/blob/pcarrier/planck/keyboard/gh60/keymap_planck.c)
- [Nathan's Fork](https://github.com/nathanrosspowell/tmk_keyboard/tree/planck-jack/keyboard/planck)
- [Matthew's Fork](https://github.com/pepers/tmk_keyboard/tree/master/keyboard/planck_grid)
