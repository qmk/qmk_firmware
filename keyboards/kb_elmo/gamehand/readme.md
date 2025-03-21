# GameHand

![gamehand](https://i.imgur.com/ia3bcUBh.jpg)

A left-hand gaming keypad with a 3D printed case

* Keyboard Maintainer: [kb-elmo](https://github.com/kb-elmo)
* Hardware Supported: GameHand rev.1 PCB
* Hardware Availability: [OpenSource Project](https://github.com/kb-elmo/GameHand)

Make example for this keyboard (after setting up your build environment):

    make kb_elmo/gamehand:default

Flashing example for this keyboard:

    make kb_elmo/gamehand:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset**: Briefly short the two contacts labeled "RESET" on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
