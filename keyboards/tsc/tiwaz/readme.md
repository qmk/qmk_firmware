# Tiwaz

Split gaming keyboard with multiple joystick options. Either half can be used independently.

* Keyboard Maintainer: [Timo Strube](https://timostrube.de)
* Hardware Supported: Tiwaz - RP2040 rev1, Tiwaz - STM32F401 rev2
* Hardware Availability: [Tiwaz](https://github.com/tstrube/Tiwaz)

![Real](https://github.com/tstrube/Tiwaz/blob/main/Images/Tiwaz.jpg)

Make examples for this keyboard (after setting up your build environment):

    make tsc/tiwaz/rev1:default
    make tsc/tiwaz/rev2:default

Flashing examples for this keyboard:

    make tsc/tiwaz/rev1:flash
    make tsc/tiwaz/rev2:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: Hold boot button on back of PCB, then plug in keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (FN + PLAY (top media key))
