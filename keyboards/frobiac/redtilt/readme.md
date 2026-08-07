# frobiac/redtilt

![frobiac/redtilt](https://i.imgur.com/stMcpmSh.jpeg)

Custom 3D-printed and handwired 46-key split-keyboard with trackpoint developed in 2013.

* Keyboard Maintainer: [frobiac](https://github.com/frobiac)
* Hardware Supported: Teensy-2.0, IBM Trackpoint
* Development History: [deskthority.net](https://deskthority.net/viewtopic.php?p=116641#p116641)
* Layout [Full KLE](http://www.keyboard-layout-editor.com/#/gists/8f30f08f84f61749c0e549f7eca97262)
* [Original Firmware](https://github.com/frobiac/adnw)

Make example for this keyboard (after setting up your build environment):

    make frobiac/redtilt

Flashing example for this keyboard:

    make frobiac/redtilt:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the Teensy by inserting a small pin in the small hole in the switch plate
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available



