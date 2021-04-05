# S20

![S20](https://i.imgur.com/RvOACqR.jpg?1)

The S20 keyboard is a FR4 sandwich keyboard which was orginally designed to add extra functionality to a user's current keyboard setup.

* Keyboard Maintainer: [polycarbdiet](https://github.com/polycarbdiet)
* Hardware Supported: S20 - FR4 sandwich MacroPad/NumberPad
* Hardware Availability: Custom, limitied quantaties. 

Make example for this keyboard (after setting up your build environment):

    make polycarbdiet/s20:default

Flashing example for this keyboard:

    make polycarbdiet/s20:default:flash

**Reset Method:** 
- Press the `RESET` button on the under side of the PCB  

**Bootloader Method:** 
- Hold down the key located at `K00`, commonly programmed as `ESC`, while plugging in the keyboard.
- Hold down the key located at `K00`, commonly programmed as `ESC`, and press the RESET button on the PCB.
- Hold down the key located at `K42` and then press the key located at `K40`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
