# EC Pro2

![EC Pro 2 PCB](https://i.imgur.com/uYOgTYoh.png)

HHKB Pro2 replacement PCB.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Pro2 PCB
* Hardware Availability: [Github](https://github.com/Cipulot/EC-Pro-2)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_pro2:default

Flashing example for this keyboard:

    make cipulot/ec_pro2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical Boot0 pins**: Short the Boot0 pins on the back of the PCB while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
