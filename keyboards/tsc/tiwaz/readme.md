# Tiwaz

Split gaming keyboard with different joystick options. Either half can be used independently.

* Keyboard Maintainer: [Timo Strube](https://timostrube.de)
* Hardware Supported: Tiwaz - RP2040
* Hardware Availability: [Tiwaz](https://github.com/tstrube/Tiwaz)

![Real](https://github.com/tstrube/Tiwaz/blob/main/Images/Real.png)
![PCB Front](https://github.com/tstrube/Tiwaz/blob/main/Images/3D_Front.png)
![PCB Back](https://github.com/tstrube/Tiwaz/blob/main/Images/3D_Back.png)
![Render](https://github.com/tstrube/Tiwaz/blob/main/Images/Render.png)

Make example for this keyboard (after setting up your build environment):

    make tsc/tiwaz:default

Flashing example for this keyboard:

    make tsc/tiwaz:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: Hold boot button on back of PCB, then plug in keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (FN + PLAY (top media key))
