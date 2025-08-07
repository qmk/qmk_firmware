# Eliza

![Eliza](https://i.imgur.com/OGpPhReh.jpeg)

40% alice-style ergo keyboard with a seamless 3D printed gasket-mount case.

* Keyboard Maintainer: [kb-elmo](https://github.com/kb-elmo)
* Hardware Supported: Eliza rev.1 PCB
* Hardware Availability: [Open source project](https://github.com/kb-elmo/eliza)

Make example for this keyboard (after setting up your build environment):

    make kb_elmo/eliza:default

Flashing example for this keyboard:

    make kb_elmo/eliza:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset**: Briefly short the two contacts labeled "RESET" on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
