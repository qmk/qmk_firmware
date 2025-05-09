# Acheron Themis QMK firmware

![themis](https://i.imgur.com/kwemOsJh.png)

The Themis is Acheron Project's open-source, freely available tenkeyless (TKL) keyboard Printed Circuit Boards (PCB) which features:

- No LED lighting
- Solderless ("hotswap") MX switches support
- Fixed layout for each variant

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: open-source PCB using the [Joker template](https://acheronproject.com/joker_mcus/joker/). First units were manufactured using STM32F4x1 microcontroller;
* Hardware Availability: open-source PCBs

In order to flash this PCB, first build the default layout (after setting up your build environment):

    make acheron/themis/<revision>:default

After building or downloading the firmware, put the PCB into DFU mode by holding the reset button for at least five seconds and upload the firmware onto the microcontroller through a utility like `dfu-util` or QMK Toolbox. Alternatively, you can build and flash using:

    make acheron/themis/<revision>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
