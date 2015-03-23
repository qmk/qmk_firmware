Planck keyboard firmware
======================
DIY/Assembled compact ortholinear 40% keyboard by [Ortholinear Keyboards](http://ortholinearkeyboards.com).

## Extended Keymap
If you include extended_keymap_common.h instead of keymap_common.h at the top of your file, you'll have access to a bunch of goodies:

- Use `LSFT()`, `LCTL()`, et. al. (listed in extended_keymap_common.h) as modifiers for keys (daisy-chain-able)
- Use `FUNC(1)` instead of `FN1` (etc.) to access the function layers beyond the 32 function layer limit
- Use `CM_F` instead of `KC_F` to get the ColeMak equivilent for shortcuts (maps backwards)
- Use `MACRODOWN()` instead of `MACRO()` to easily make a keydown macro (`CM_*` works here too)

### Some notes on usage:

- The `KEYMAP()` macro is unable to be used due to the bitwise modifications that take place - refer to extended_keymap_jack.c to see how to set things up with the `KC_` prefix
- Keep an eye on the Makefile - this needs to include the correct files to work
- Don't forget to use `const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {` instead of the 8bit equivilent

## Build

Follow [this guide](http://deskthority.net/workshop-f7/how-to-build-your-very-own-keyboard-firmware-t7177.html) to setup your development environment before anything else.

Download the whole firmware [here](https://github.com/jackhumbert/tmk_keyboard/archive/master.zip) and navigate to the keyboard/planck folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex that you can load with the Teensy app onto your Planck (once you've hit reset/shorted GND & RST).

Move to this directory then just run `make` like:

    $ make

## Keymap
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document (you can find in top README.md) and existent keymap files.

To build firmware binary hex file with a certain keymap just do `make` with `KEYMAP` option like:

    $ make KEYMAP=[<name>]

## Notable TMK forks (which some of the keymap files are from)
- [Shane's Fork](https://github.com/shanecelis/tmk_keyboard/tree/master/keyboard/planck)
- [Pierre's Fork](https://github.com/pcarrier/tmk_keyboard/blob/pcarrier/planck/keyboard/gh60/keymap_planck.c)
- [Nathan's Fork](https://github.com/nathanrosspowell/tmk_keyboard/tree/planck-jack/keyboard/planck)
- [Matthew's Fork](https://github.com/pepers/tmk_keyboard/tree/master/keyboard/planck_grid)