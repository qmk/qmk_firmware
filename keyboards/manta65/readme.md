# Manta 65 QMK firwmare

![manta](https://i.imgur.com/jcNcx2g.png)

The Manta65 is a 65% keyboard designed by Bowl and Alexotos. The PCB was designed by Gondolindrim, who is also the firmware maintainer. The PCB uses a STM32F411 microcontroller implementation.

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: proprietary PCB using STM32F4x1 microcontroller;
* Hardware Availability: the Manta65 group buy is already over as of may 2026.

In order to flash this PCB, first build the default layout (after setting up your build environment):

    make manta65/<version>:default

Where `version` is either `manta65s` for solderable or `manta65h` for hotwsap.

After building or downloading the firmware, put the PCB into DFU mode by holding the reset button for at least five seconds and upload the firmware onto the microcontroller through a utility like `dfu-util` or QMK Toolbox. Alternatively, you can build and flash using:

    make manta65/<version>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
