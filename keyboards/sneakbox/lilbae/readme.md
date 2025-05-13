# Sneakbox Lil' BAE

![Lil' BAE](https://i.imgur.com/a/S7FKp7r.jpg)

A small macropad featuring key positions for a Big-Ass Enter (Reverse L-shaped enter key)

Keyboard Maintainer: [mujimanic](https://sneakbox.com)
Hardware Supported: The PCBs, controllers supported
Hardware Availability: [sneakbox.design](https://sneakbox.com/products/lil-bae-macropad)

Make example for this keyboard (after setting up your build environment):

    make lilbae:default

Flashing example for this keyboard:

    make lilbae:default:flash
    
See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

Bootloader
Enter the bootloader in 3 ways:

Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
Physical reset button: Briefly press the button on the back of the PCB - some may have pads you must short instead
Keycode in layout: Press the key mapped to QK_BOOT if it is available