# TrueStrike42

![truestrike42](https://github.com/byungyoonc/TrueStrike42/blob/main/doc/res/truestrike42-built.jpg?raw=true)

TrueStrike42 is a columnar staggered unibody split Hall effect keyboard designed to maximize performance and minimize finger fatigue.

Hall effect part of this firmware code is a modified version of Cipulot's code.

* Keyboard Maintainer: [byungyoonc](https://github.com/byungyoonc)
* Hardware Supported: RP2040 development boards with Pro Micro pin layout
* Hardware Availability: https://github.com/byungyoonc/TrueStrike42

Make example for this keyboard (after setting up your build environment):

    make truestrike42:default

Flashing example for this keyboard:

    make truestrike42:default:flash
    
    OR
    
    Copy the built `uf2` firmware file into `RPI-RP2` drive when the controller is in the bootloader mode

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Quickly double-press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
