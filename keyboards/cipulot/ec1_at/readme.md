# EC1-AT

![EC1-AT](https://i.imgur.com/69OrQsh.png)

EC version of the W1-AT keyboard.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC1-AT
* Hardware Availability: TBD

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec1_at:default

Flashing example for this keyboard:

    make cipulot/ec1_at:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
