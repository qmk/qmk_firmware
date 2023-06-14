# Acheron Athena QMK firmware

![athena](https://acheronproject.com/images/athena/IMG_9653.jpg)

The Athena is Acheron Project's open-source, freely available tenkeyless (TKL) keyboard Printed Circuit Boards (PCB) which features:

- Per-key LED lighting
- Solderable MX switches support
- Wide variety of layouts including Tsangan bottom row, split right and left shifts, ISO enter, split backspace, F13 top row

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: open-source PCB using the [Joker template](https://acheronproject.com/joker_mcus/joker/). First units were manufactured using STM32F4x1 microcontroller;
* Hardware Availability: these PCBs are open-source so you can manufacture them yourself or order them from a factory. See the [project's documentation](https://acheronproject.com/pcbs/athena/athena/) for more information.

In order to flash this PCB, first build the default layout (after setting up your build environment):

    make acheron/athena/<revision>:default

Where `revision` is the revision of your PCB. Two revisions were prototyped and sold: _Alpha_ and _Beta_. Look into the label on the PCB's back to see what revision is yours. Ready-to-use binaries for the default and the VIA layouts are available in the release pages of the [project's repository](https://github.com/AcheronProject/Athena).

After building or downloading the firmware, put the PCB into DFU mode by holding the reset button for at least five seconds and upload the firmware onto the microcontroller through a utility like `dfu-util` or QMK Toolbox. Alternatively, you can build and flash using:

    make acheron/athena/<revision>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
