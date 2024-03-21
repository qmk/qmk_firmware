# derb_planck

![derb_planck](https://i.imgur.com/UVefC9Y.jpg)

This is an planck keyboard with integrated USB multiplexer. Up to three host devices can be connected.
For more details see [https://der-b.com/posts/2024-05-08-mechanical-keyboard-derb-planck/](https://der-b.com/posts/2024-05-08-mechanical-keyboard-derb-planck/)

* Keyboard Maintainer: [Bernd Lehmann](https://github.com/der-b)
* Hardware Supported: ATmega32u4
* Hardware Availability: [GitHub](https://github.com/der-b/derb-planck)

Make example for this keyboard (after setting up your build environment):

    make handwired/derb_planck/rev1:default

Flashing example for this keyboard:

    make handwired/derb_planck/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
