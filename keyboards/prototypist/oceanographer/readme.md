# prototypist/oceanographer

![prototypist/oceanographer](https://i.imgur.com/loDNEHM.png)

*PCB for the Oceanographer keyboard designed by Hedgey.*

* Keyboard Maintainer: [Josh @ Prototypist](https://github.com/Anjheos)
* Hardware Supported: **Oceanographer**
* Hardware Availability: *TBD*

Make example for this keyboard (after setting up your build environment):

    make prototypist/oceanographer:default
    
Flashing example for this keyboard:

    make prototypist/oceanographer:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB marked `SWRST1`.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
