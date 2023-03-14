# h08

![h08](https://i.imgur.com/8B0ORJE.png)

8-key macropad for the Singa Ocelot.

* Keyboard Maintainer: [hineybush](https://github.com/hineybush)
* Hardware Supported: h08
* Hardware Availability: Singa Ocelot

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make hineybush/h08_ocelot:default

Flashing example for this keyboard:

    make hineybush/h08_ocelot:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
