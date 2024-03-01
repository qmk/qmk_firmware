# The Compensator

[Compensator](https://i.imgur.com/fAB2SSTh.png)

A 40% monstrosity with 10U spacebar support and a required 2 keycap sets to fill. It supports VIA. [Geekhack Post](https://geekhack.org/index.php?topic=122493.0)

* Keyboard Maintainer: [Lrfoster03](https://lrfoster03.github.io/) and on [GitHub](https://github.com/Lrfoster03)
* Hardware Supported: A 40% with 2 numpads, 2 nav clusters, and 2 XT columns with an ATMEGU32U4
* Hardware Availability: Contact @victusss on discord. [vk.works Discord](https://discord.gg/7weV2kyqFB)

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make compensator:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Flash
- Ensure PCB is plugged in and recognized by the computer
- Hold Physical reset button on back of the PCB to enter bootloader mode
- Flash using QMK Toolbox or CLI (`make compensator:<keymap>:flash`)
