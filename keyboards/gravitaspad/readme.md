# gravitaspad

![gravitaspad]https://i.imgur.com/lh1yjni.jpeg


* Keyboard Maintainer: [deverdum](https://github.com/deverdum)
* Hardware Supported: RP2040 zero
* Hardware Availability: https://www.ozon.ru/search/?deny_category_prediction=true&from_global=true&text=%D0%98%D0%B3%D1%80%D0%BE%D0%B2%D0%B0%D1%8F+%D0%BA%D0%BB%D0%B0%D0%B2%D0%B8%D0%B0%D1%82%D1%83%D1%80%D0%B0&product_id=1850319093

Make example for this keyboard (after setting up your build environment):

    make gravitaspad:default

Flashing example for this keyboard:

    make gravitaspad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the maghhifdecabcbbcatrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
