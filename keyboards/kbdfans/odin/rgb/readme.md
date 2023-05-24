# ODIN RGB

A customizable HOTSWAP RGB keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Hardware Supported: KBDFANS
* Hardware Availability: [kbdfans](https://kbdfans.myshopify.com/)

Make example for this keyboard (after setting up your build environment):

    make kbdfans/odin/rgb:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix
* **Physical reset button**:press and hold the button on the back of the PCB, then plugin to PC
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
