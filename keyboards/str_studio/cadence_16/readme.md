# Cadence_16

![Cadence_16](https://strstudio.net/_next/image?url=%2Fcadence-1.png&w=1920&q=100)

A weighty compact 16 keys numpad made and sold by [str studio](https://strstudio.net/).

* Keyboard Maintainer: [str studio](https://strstudio.net/)
* Hardware Availability: [str studio - store](https://strstudio.net/store/cadence)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb str_studio/cadence16 -km default

Flashing the firmware using [QMK Toolbox](https://github.com/qmk/qmk_toolbox)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button on the top of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
