TypeTheory Keyboard
======
![Picture of TypeTheory Keyboard](https://typetheory.co.uk/thumb/front.jpg)

The [TypeTheory Keyboard](https://typetheory.co.uk/) is a split ergonomic keyboard inspired by the [Dactyl-Manuform](https://github.com/tshort/dactyl-keyboard) and the Kinesis Advantage2. It uses two Puchi-C microcontrollers, with physical reset buttons.

* Keyboard Maintainer: Marius Gavrilescu
* Hardware Supported: TypeTheory Keyboard
* Hardware Availability: https://typetheory.co.uk


## Compiling and flashing the firmware
> See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Clone the `qmk_firmware` repository and run this command to compile the firmware with the default layout:

    make typetheory:default

To flash a keyboard half, you must connect it to the computer and reset the microcontroller. To reset, you can either:
1. Press the RESET key on the keyboard, this is RAISE+RIGHT SHIFT on the default layout.
2. With the keyboard unplugged, hold SPACE + B while plugging in the keyboard.
3. Open up the keyboard half, and press the reset button on the Puchi-C board

Once reset, you can flash the left/right half by using one of these commands respectively:

    make typetheory:default:dfu-split-left
    make typetheory:default:dfu-split-right

Tip: if desired, you can flash different layouts to the left/right side. Then, the entire keyboard will use the 'left' layout when the left side is plugged into the computer, and vice-versa for the right side. Do not attempt to plug in both keyboard halves into the computer at once.
