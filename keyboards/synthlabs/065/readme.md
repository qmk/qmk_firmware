# Synth Labs 065

![065](https://i.imgur.com/1iLYrP1h.jpg)

The 065 Keyboard by Synth Labs.

* Keyboard Maintainer: [Nostril](https://github.com/hongaaronc)
* Hardware Supported: [Synth Labs 065 Soldered + Hotswap PCB](https://github.com/0xCB-dev/SL-065-PCB)
* Hardware Designer: [0xCB](https://0xcb.dev/)
* Hardware Availability: Awaiting GB, or order your own parts using [the open-source PCB production files](https://github.com/0xCB-dev/SL-065-PCB)


Make example for this keyboard (after setting up your build environment):

    make synthlabs/065:default

Flashing example for this keyboard:

    make synthlabs/065:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the Escape key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
