# nordic65

PCB designed for kbnordic.se

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: nordic65

Make example for this keyboard (after setting up your build environment):

    make kbnordic/nordic65/rev_a:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the ESC key
* **Physical reset button**: Briefly press the button on the back of the PCB or short the two pads in the "RST" header for more than 3 seconds.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
