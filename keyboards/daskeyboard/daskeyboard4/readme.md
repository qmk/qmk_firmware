# daskeyboard4

![daskeyboard4pro](https://i.imgur.com/Y3xT9Zu.jpeg)

![PCB](https://i.imgur.com/UfzVHcj.jpeg)

*Reverse engineered PCB definition of daskeyboard 4 (Professional)*

* Keyboard Maintainer: [Commander1024](https://github.com/Commander1024)
* Hardware Supported: *The PCB*
* Hardware Availability: *https://www.daskeyboard.com/de/daskeyboard-4-professional/*

I used an STM32 development board to replace the keyboards destroyed controller. This keyboard definition is here, to enable to painless usage of the OEM PCB in a custom keyboard, as the rows and columns are placed in a very unintuitive fashion.

The layout definition in **info.json** contains the magic. The rows and columns appear in the pin definition in the order they appear on the 26 pads, where the original ribbon cable was connected for intuitive cabling and adoption to other microcontrollers.

**Note**: Pad 25 is not connected.

Make example for this keyboard (after setting up your build environment):

    make daskeyboard4:default

Flashing example for this keyboard:

    make daskeyboard4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
