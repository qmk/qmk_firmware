# EC TKL X

![EC TKL X PCB](https://i.imgur.com/pdkT14y.png)

Universal TKL Electrostatic Capacitive PCB, with multi-layout support (F12/F13 version).

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC TKL X PCB
* Hardware Availability: TBD

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_tkl_x:default

Flashing example for this keyboard:

    make cipulot/ec_tkl_x:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long press the button on the bottom on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
