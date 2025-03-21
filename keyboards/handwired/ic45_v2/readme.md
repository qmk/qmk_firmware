# ic45_v2

![ic45_v2](https://i.imgur.com/a/FNxxXGd)

*A 46-key keyboard ANSI keyboard with split spacebar. Files available here [here](https://github.com/lighteningAB/45keyboard_v1)*

* Keyboard Maintainer: [PatrickFan](https://github.com/PatrickFan)
* Hardware Supported: Integrated ATmega32U4
* Hardware Availability: [GitHub](https://github.com/lighteningAB/45keyboard_v1)

Make example for this keyboard (after setting up your build environment):

    make handwired/ic45_v2:default

Flashing example for this keyboard:

    make handwired/ic45_v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
