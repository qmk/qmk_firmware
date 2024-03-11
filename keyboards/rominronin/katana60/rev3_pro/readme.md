# rominronin/katana60/rev3_pro

![rominronin/katana60/rev3_pro](https://i.imgur.com/kwDWuJP.jpg)

A symmetrical staggered-row layout, with hotswap sockets

* Keyboard Maintainer: [Baris Tosun](https://github.com/rominronin)
* Hardware Supported: Katana60 Pro PCB
* Hardware Availability: Not currently available. For more information, please visit [rominronin.net](https://rominronin.net)
* Cases: Compatible with 60% cases, please read compatibility notes at [rominronin.net](https://rominronin.net)

Make example for this keyboard (after setting up your build environment):

    make rominronin/katana60/rev3_pro:default

Flashing example for this keyboard:

    make rominronin/katana60/rev3_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
