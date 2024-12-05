# contender

![](https://i.imgur.com/JME6nwB.jpg)

A number pad for hardboot.

* Keyboard Maintainer: [sotoba](https://github.com/sotoba)
* Hardware Supported: Contender PCB
* Hardware Availability: [BOOTH: stupa-devices](https://stupa-devices.booth.pm/)

Make example for this keyboard (after setting up your build environment):

    make contender:default

Flashing example for this keyboard:

    make contender:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
