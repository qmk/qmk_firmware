# kay60

![kay60](https://i.imgur.com/FVg59LUl.png)

Kay60 PCB, 60% keyboard PCB.
* Keyboard Maintainer: [Mechlovin'](https://mechlovin.studio)
* Hardware Supported: Kay60, Atmega32U4
* Hardware Availability: [Mechlovin'](https://mechlovin.studio)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/kay60:default

Flashing example for this keyboard:

    make mechlovin/kay60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
* **Physic button**: Press reset swith on the bottom of the PCB
