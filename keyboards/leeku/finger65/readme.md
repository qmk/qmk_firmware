# Leeku Finger65 PCB

* Keyboard Maintainer: [sidcarter](https://github.com/sidcarter)
* Hardware Supported: LeeKu Finger65 PCB, atmega32a

* Make example for this keyboard (after setting up your build environment):

    make leeku/finger65:default

* This PCB is not QMK ready by default. If you want to use your Leeku Finger65 PCB with QMK, you must:

    * ISP Flash the Leeku PCB using the bootloader for the atmega32a that resides in the `util/` folder
    * Build and install [bootloadHID](https://www.obdev.at/products/vusb/bootloadhid.html) on your system
    * You can then do a `make leeku/finger65:default:flash` to flash your PCB with QMK

* See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
