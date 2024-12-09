# EC 65X

![EC 65X PCB](https://i.imgur.com/8B86zsO.png)

Universal 65% Electrostatic Capacitive PCB, with multi-layout support.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC 65X
* Hardware Availability: TBD

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_66x:default

Flashing example for this keyboard:

    make cipulot/ec_66x:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical button**: Long press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
