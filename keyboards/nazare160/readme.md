# Nazarè Engineering Nazare1-60 QMK Firmware

![nz160](https://i.imgur.com/ZYJgL2G.jpg)

The Nazarè 1-60 is the first revision of a 60% keyboard by Nazare Engineering.

* IC/GB page: https://geekhack.org/index.php?topic=112166
* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: revision Alpha uses an STM32F072 MCU, whilst Beta uses the [Joker template](https://acheronproject.com/joker_mcus/joker/). First units were manufactured using STM32F411 microcontroller;
* Hardware Availability: the Nazare1-60 uses a proprietary PCB

In order to flash this PCB, first build the default layout (after setting up your build environment):

    make nazare160/<revision>:default

Where `revision` is the revision of your PCB. Two revisions were prototyped: _Alpha_ and _Beta_, but only the latter sold publicly. Look into the label on the PCB's back to see what revision is yours.

After building or downloading the firmware, put the PCB into DFU mode by holding the reset button for at least five seconds and upload the firmware onto the microcontroller through a utility like `dfu-util` or QMK Toolbox. Alternatively, you can build and flash using:

    make nazare160/<revision>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
