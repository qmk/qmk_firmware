# EC 60

![EC 60 PCB](https://i.imgur.com/XNwsVOnh.png)

60% Electrostatic Capacitive PCB, GH60 mounting compatible, with multi-layout support

* Keyboard Maintainer: [cipulot](https://github.com/Cipulot)
* Hardware Supported: EC 60
* Hardware Availability: [Github](https://github.com/Cipulot/EC60)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_60:default

Flashing example for this keyboard:

    make cipulot/ec_60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical Boot0 pins**: Short the Boot0 pins on the back of the PCB while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
