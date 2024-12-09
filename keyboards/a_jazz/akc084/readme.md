# A-JAZZ  AKC084

A customizable 84keys keyboard

![akc084](https://i.imgur.com/381vaD7.png)
* Keyboard Maintainer: [Feng](https://github.com/fenggx-a-jazz)
* Hardware Supported: [a-jazz](https://www.a-jazz.com)
* Hardware Availability: [a-jazz](https://ajazzstore.com/collections/all/products/ajazz-akp846)

Make example for this keyboard (after setting up your build environment):

    make a_jazz/akc084:default

Flashing example for this keyboard:

    make a_jazz/akc084:default:flash

See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

## Bootloader ESC the bootloader in 3 ways:
* **Bootmagic reset: Hold down Enter in the keyboard then replug
* **Physical reset button: Briefly press the button on the back of the PCB
* **Keycode in layout: Press the key mapped to QK_BOOT
