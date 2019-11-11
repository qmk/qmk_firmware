# Leeku Finger 65 PCB

* Keyboard Maintainer: [sidcarter](https://github.com/sidcarter)

* Hardware Supported: atmega32a 

* Make example for this keyboard (after setting up your build environment):

    make leeku/finger65:default

* This PCB is not QMK ready by default. If you want to use your Leeku Finger65 PCB with QMK, you must:

    * ISP Flash the Leeku PCB using the bootloader for the atmega32a that resides in the `util/` folder
    * After ISP Flashing the PCB, you can then use QMK to flash the PCB
    * Before flashing, remember to install bootloadHID on your system
    * Once you have bootloadHID, you can do make make leeku/finger65:default:flash to flash your PCB

* See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
