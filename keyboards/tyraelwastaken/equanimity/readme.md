# equanimity

![equanimity](https://i.imgur.com/kIGyOi4.png)

Arisu-ish Alice keyboard with an EC11 and some accent keys, staggered.

* Keyboard Maintainer: [TyraelWasTaken](https://github.com/TyraelWasTaken)
* Hardware Supported: *UDB C3 or greater with Equanimity PCB, no other PCBs are supported for the case*
* Hardware Availability: *If you wish to build this, all files are available here: https://github.com/TyraelWasTaken/Equanimity*

Make example for this keyboard (after setting up your build environment):

    make tyraelwastaken/equanimity:default

Flashing example for this keyboard:

    make TyraelWasTaken/equanimity:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (set as Delete by default) and plug in the keyboard
* **Physical reset button**: Press both the Top and Bottom buttons at the same time
* **Keycode in layout**: Press the key mapped to `RESET` if it is available (this has not been mapped by default)
