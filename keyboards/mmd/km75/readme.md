# MMD-KM75

![](https://raw.githubusercontent.com/JackyJia73/img/main/IMG_20240716_173524.jpg)

* A customizable soldering 75% keyboard.

* Keyboard Maintainer: [MMD](https://github.com/Smartmmd)
* Hardware Supported: [i-game](http://www.i-game.tech)
* Hardware Availability: [i-game](http://www.i-game.tech)

Make example for this keyboard (after setting up your build environment):

    make mmd/km75:default
Flashing example for this keyboard:

    make mmd/km75:default:flash

See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

## Bootloader ESC the bootloader in 3 ways:
* **Bootmagic reset: Hold down Enter in the keyboard then replug
* **Physical reset button: Briefly press the button on the back of the PCB
* **Keycode in layout: Press the key mapped to QK_BOOT
