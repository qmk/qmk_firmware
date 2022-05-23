# ATSET AT9
The Rad Macro Pad is a USB-C, Macro Pad with 9 keys powered by QMK

Keyboard Maintainer: Anubhav Dhiman
Hardware Supported: ATmega32U4
Hardware Availability: Interest Check
Make example for this keyboard (after setting up your build environment):

make rad:default
Flashing example for this keyboard:

make rad:default:flash
See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

Bootloader
Enter the bootloader in 3 ways:

Bootmagic reset: Hold down the key at (0,2) in the matrix (top right) and plug in the keyboard
Physical reset button: Briefly press the button on the back of the PCB - some may have pads you must short instead
Keycode in layout: Press the key mapped to RESET if it is available