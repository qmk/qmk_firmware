# Contra

![CONTRA](https://raw.githubusercontent.com/ai03-2725/Contra/master/Images/back-2.0.jpg)

Contra is a low cost 40% keyboard.

## Keyboard Info
* Keyboard Maintainer: The QMK Community  
* Hardware Supported: [Contra](https://github.com/ai03-2725/Contra)
* Hardware Availability: PCB sold by various vendors

Make example for this keyboard (after setting up your build environment):

    make contra:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset button**: Briefly press the reset button soldered on the PCB.
* **Bootmagic reset**: Hold down the top left key and plug in the controller.
