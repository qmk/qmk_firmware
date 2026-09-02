# Tiwaz

Split gaming keyboard with multiple joystick options. Either half can be used independently.

* Keyboard Maintainer: [Timo Strube](https://timostrube.de)
* Hardware Supported: Tiwaz - STM32F401
* Hardware Availability: 
  - PCB on [Crowd Supply](https://www.crowdsupply.com/timo-strube/tiwaz)
  - Case on [Printables](https://www.printables.com/model/1715647-tiwaz-split-gaming-keyboard-gasket-mounted)
* More Information: [Github Project Page](https://github.com/tstrube/Tiwaz)

![Tiwaz](https://github.com/tstrube/Tiwaz/blob/main/Images/Tiwaz.jpg)
![Front](https://github.com/tstrube/Tiwaz/blob/main/Images/PCB_Front.jpg)
![Back](https://github.com/tstrube/Tiwaz/blob/main/Images/PCB_Back.jpg)

Make examples for this keyboard (after setting up your build environment):

    make tiwaz:default

Flashing examples for this keyboard:

    make tiwaz:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: Hold boot button on back of PCB, then plug in keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (FN + PLAY (top media key))
