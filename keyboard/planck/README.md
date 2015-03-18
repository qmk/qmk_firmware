Planck keyboard firmware
======================
DIY/Assembled compact ortholinear keyboard by [Ortholinear Keyboards](http://ortholinearkeyboards.com).

## Notable TMK forks (which some of the keymap files are from)
- [Shane's Fork](https://github.com/shanecelis/tmk_keyboard/tree/master/keyboard/planck)
- [Pierre's Fork](https://github.com/pcarrier/tmk_keyboard/blob/pcarrier/planck/keyboard/gh60/keymap_planck.c)
- [Nathan's Fork](https://github.com/nathanrosspowell/tmk_keyboard/tree/planck-jack/keyboard/planck)
- [Matthew's Fork](https://github.com/pepers/tmk_keyboard/tree/master/keyboard/planck_grid)

## Build

Follow [this guide](http://deskthority.net/workshop-f7/how-to-build-your-very-own-keyboard-firmware-t7177.html) to setup your development environment before anything else.

Download the whole firmware [here](https://github.com/jackhumbert/tmk_keyboard/archive/master.zip) and navigate to the keyboard/planck folder. Once your dev env is setup, you'll be able to type "make" to generate your .hex that you can load with the Teensy app onto your Planck (once you've hit reset/shorted GND & RST).

Move to this directory then just run `make` like:

    $ make

Use `make -f Makefile.pjrc` if you want to use PJRC stack but I find no reason to do so now.


## Keymap
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document(you can find in top README.md) and existent keymap files.

To build firmware binary hex file with a certain keymap just do `make` with `KEYMAP` option like:

    $ make KEYMAP=[<name>]
