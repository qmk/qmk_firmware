# frobiac/hypernano

![frobiac/hypernano](https://i.imgur.com/ZVGtpBbh.jpeg)

Custom 3D-printed and handwired 44-key keyboard with trackpoint developed in 2013.

* Keyboard Maintainer: [frobiac](https://github.com/frobiac)
* Hardware Supported: Teensy-2.0, IBM Trackpoint
* Development History: [deskthority.net](https://deskthority.net/viewtopic.php?p=98734#p98734)
* Layout [Alpha KLE](http://www.keyboard-layout-editor.com/#/gists/e4f60451766bbe7002c0b9a9ddfb3e34)
* [Original Firmware](https://github.com/frobiac/adnw)

Make example for this keyboard (after setting up your build environment):

    make frobiac/hypernano

Flashing example for this keyboard:

    make frobiac/hypernano:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button in the middle of the bottom row
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available


