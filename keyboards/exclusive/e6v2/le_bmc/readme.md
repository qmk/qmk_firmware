# E6-V2 Bootmapper Client (ps2avrgb) LE

These docs are for the BMC version of the E6-V2 PCB sold during Round 2 which has an atmega32a microcontroller. Please do not flash this `.hex` file on your atmega32u4 equipped E6-V2 or your E6V2 BMC from Round 1. 

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: ps2avrgb E6-V2 with atmega32a microcontroller
* Hardware Availability: [geekhack.org/index.php?topic=90787.0](https://geekhack.org/index.php?topic=90787.0)

Make example for this keyboard (after setting up your build environment):

    make exclusive/e6v2/le_bmc:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make exclusive/e6v2/le_bmc:default:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *left control* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
