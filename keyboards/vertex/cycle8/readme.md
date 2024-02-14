# cycle8

![Cycle8](https://i.imgur.com/gCExreih.png)

A customizable soldered TKL/80% keyboard.

* Keyboard Maintainer: [EASON](https://github.com/EasonQian1)
* Hardware Supported: Cycle8 PCB
* Hardware Availability: [EASON](https://github.com/EasonQian1)

Make example for this keyboard (after setting up your build environment):

    make vertex/cycle8:default

Flashing example for this keyboard:

    make vertex/cycle8:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Esc in the keyboard then replug
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
