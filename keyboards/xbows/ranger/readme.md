# Ranger
![Ranger](https://img.alicdn.com/i3/16731204/O1CN015gRK1R1KlTSHEuHDo_!!16731204.jpg)

Ranger, A 87 keys keyboard with RGB backlight.

* Keyboard Maintainer: X-BOWS
* Hardware Supported: X-BOWS Ranger
* Hardware Availability: [X-BOWS](https://x-bows.com/)

Enter the bootloader in 3 ways:
* Software reset on Fn + ESC
* Bootmagic reset: hold down the top left key (usually escape) and plugin the keyboard
* Physical reset button: There is a button on the back of the PCB, please press it briefly.

Flash new firmware in 2 ways:
* Use the QMK toolbox：https://github.com/qmk/qmk_toolbox/releases
* Use the QMK MSYS：https://msys.qmk.fm/

Make example for this keyboard (after setting up your build environment):

    make xbows/ranger:default
    make xbows/ranger:via

Flashing example for this keyboard:

    make xbows/ranger:default:flash
    make xbows/ranger:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
