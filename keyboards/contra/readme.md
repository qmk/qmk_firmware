# Contra

Contra is a low cost 40% keyboard.

* Keyboard Maintainer: The QMK Community  
* Hardware Supported: [Contra](https://github.com/ai03-2725/Contra)
* Hardware Availability: PCB sold by various vendors

Make example for this keyboard (after setting up your build environment):

    make contra:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset button**: Briefly press the reset button soldered on the PCB.
* **Bootmagic reset**: Hold down the top left key and plug in the controller.
