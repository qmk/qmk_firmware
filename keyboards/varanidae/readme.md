# Varanidae

![Varanidae](https://i.imgur.com/0wWfmE1h.png)

Varanidae the left-side pad 110 keys keyboard for creators powered by Elite-C.

* Keyboard Maintainer: [Silc Renew](https://github.com/TokageItLab)
* Hardware Supported: Varanidae
* Hardware Availability: [TokageItLab / Varanidae](https://github.com/TokageItLab/Varanidae)

Make example for this keyboard (after setting up your build environment):

    make varanidae:default
    make varanidae:via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the switch at (0,0) in the matrix (usually the encoder push switch) and plug in the keyboard
* **Physical reset button**: Briefly press the reset switch on the Elite-C
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
