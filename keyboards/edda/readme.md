# Edda PCB

Alice layout PCB with top mounted USB C used in Mekanisk Edda

* Keyboard Maintainer: [martin](https://github.com/arnstadm)
* Hardware Supported: [Edda PCB](https://tastatur.no/collections/forhandsbestilling-1/products/edda-pcb?variant=39481626001453)

Make example for this keyboard (after setting up your build environment):

    make edda:default

Flashing example for this keyboard:

    make edda:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

How to enter bootloader (DFU):

    Press and hold the button on the keyboard (the small one on the same side as the MCU) for more than 1 second. The keyboard will then enter bootloader (DFU) mode and it's ready to flash the firmware.
    Note: If holding the button a shorter time, the keyboard will just reset. If you want to exit bootloader mode without flashing a firmware, disconnect the keyboard from your PC and reconnect it.
