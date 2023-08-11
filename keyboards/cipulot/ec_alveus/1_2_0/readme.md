# EC Alveus

![EC Alveus](https://i.imgur.com/J31LzzOh.jpg)

EC FRL TKL keyboard.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Alveus 1.2.0
* Hardware Availability: Raffle Sale from [Densus](https://www.instagram.com/densusdesign/)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_alveus/1_2_0:default

Flashing example for this keyboard:

    make cipulot/ec_alveus/1_2_0:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset**: Long short the exposed pads on the top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
