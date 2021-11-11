# yunomi

![yunomi](https://raw.githubusercontent.com/google/mozc-devices/master/mozc-yunomi/images/device.jpg)

*A QMK port of the mozc-yunomi firmware. The [mozc-yunomi](https://github.com/google/mozc-devices/tree/master/mozc-yunomi) is an open-source keyboard by Google.*

* Keyboard Maintainer: [Austin Wang](https://github.com/Dafondo)
* Hardware Supported: [mozc-yunomi](https://github.com/google/mozc-devices/tree/master/mozc-yunomi)
* Hardware Availability: [mozc-yunomi](https://github.com/google/mozc-devices/tree/master/mozc-yunomi)

Make example for this keyboard (after setting up your build environment):

    make yunomi:default

Flashing example for this keyboard:

    make yunomi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
