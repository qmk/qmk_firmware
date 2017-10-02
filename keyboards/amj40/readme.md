AMJ40 keyboard firmware
======================
DIY/Assembled compact 40% keyboard.

Ported by N.Hou from the original TMK firmware.

*Supports both backlight LEDs as well as RGB underglow. 

*For reference, the AMJ40 uses pin D3 for underglow lighting.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/amj40
folder. Once your dev env is setup, you'll be able to type `make` to generate
your .hex - you can then use `make dfu` to program your PCB once you hit the
reset button. 

Depending on which keymap you would like to use, you will have to compile
slightly differently.

### Default
To build with the default keymap, simply run `sudo make all`.
The .hex file will appear in the root of the qmk firmware folder.




### Original tmk firmware
The original firmware that was used to port to qmk can be found [here](https://github.com/AMJKeyboard/AMJ40).


