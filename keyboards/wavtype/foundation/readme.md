![foundation]

the foundation pcb was designed for protozoa studio's foundation line of keyboards.

Keyboard Maintainer: wavtype

Make example for this keyboard (after setting up your build environment):
make wavtype/foundation:via

Flashing example for this keyboard:
make wavtype/foundation:via:flash

See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

Bootloader
Enter the bootloader in 3 ways:

Bootmagic reset: Hold down the key at (0,1) in the matrix (Escaoe key) and plug in the keyboard
Physical reset button: Briefly press the button on the back of the PCB
Keycode in layout: Press the key mapped to RESET if it is available (by default this is set to "Fn + R")