# Dizzy40

![Dizzy40](https://i.imgur.com/TNXHaUGh.jpeg)

A simple drop-in replacement PCB for the KPRepublic Daisy40 keyboard.

* Keyboard Maintainer: [kb-elmo](https://github.com/kb-elmo)
* Hardware Supported: Dizzy40 rev.1 PCB
* Hardware Availability: [Open source project](https://github.com/kb-elmo/dizzy40)

Make example for this keyboard (after setting up your build environment):

    make kb_elmo/dizzy40:default

Flashing example for this keyboard:

    make kb_elmo/dizzy40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset**: Briefly short the two contacts labeled "RESET" on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
