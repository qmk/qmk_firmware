# EC Theca

![EC Theca](https://i.imgur.com/ZdeJLVdh.png)

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Theca
* Hardware Availability: [KLC](https://klc-playground.com/)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_theca:default

Flashing example for this keyboard:

    make cipulot/ec_theca:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset**: Long short the exposed pads on the top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
