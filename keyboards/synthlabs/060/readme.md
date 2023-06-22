# Synth Labs 060

![060](https://i.imgur.com/0EDUgjth.jpg)

The 060 Keyboard by Synth Labs in collaboration with keebwerk and 0xCB.

* Keyboard Maintainer: [Nostril](https://github.com/hongaaronc)
* Hardware Supported: [Synth Labs 060 Soldered + Hotswap PCB](https://github.com/0xCB-dev/SL-060-PCB)
* Hardware Designer: [0xCB](https://0xcb.dev/)
* Hardware Availability: Available from [keebwerk](https://www.keebwerk.com/), or order your own parts using [the open-source PCB production files](https://github.com/0xCB-dev/SL-060-PCB)


Make example for this keyboard (after setting up your build environment):

    make synthlabs/060:default

Flashing example for this keyboard:

    make synthlabs/060:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the Escape key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
