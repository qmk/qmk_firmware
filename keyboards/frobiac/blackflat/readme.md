# frobiac/blackflat

![frobiac/blackflat](https://i.imgur.com/eaewuolh.jpeg)

Custom 3D-printed and handwired 36-key split-keyboard with trackpoint developed in 2016.

* Keyboard Maintainer: [frobiac](https://github.com/frobiac)
* Hardware Supported: Teensy-2.0, IBM Trackpoint
* Development History: [deskthority.net](https://deskthority.net/viewtopic.php?p=339638#p339638)
* Layout [Alpha KLE](http://www.keyboard-layout-editor.com/#/gists/6a6ec84d59fc346effbe894af159eabd) (same as BlackBowl)
* [Original Firmware](https://github.com/frobiac/adnw)

Make example for this keyboard (after setting up your build environment):

    make frobiac/blackflat

Flashing example for this keyboard:

    make frobiac/blackflat:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button between left-hand topmost ringfinger key and USB socket
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available



