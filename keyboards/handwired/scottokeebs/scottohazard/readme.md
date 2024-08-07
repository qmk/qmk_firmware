# ScottoHazard

![ScottoHazard](https://i.imgur.com/y2j7DOxh.jpg)

A 3x5 (40-keys) or 3x6 (48-keys) split ortholinear keyboard that uses a TRRS cable for the interconnect.

* Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: RP2040 Pro Micro
*   Hardware Availability: [ScottoKeebs](https://scottokeebs.com), [Amazon](https://amazon.com), [AliExpress](https://aliexpress.com)

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottohazard:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottohazard:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,1) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
