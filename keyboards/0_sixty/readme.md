# 0-Sixty

![0-Sixty](https://imgur.com/azmMb6Rl.jpg)

![0-Sixty PCB](https://i.imgur.com/I0TkQ0Rl.jpg)

0-Sixty (pronounced "zero to sixty") is a 60 key ortholinear keyboard inspired by the [Discipline](https://github.com/coseyfannitutti/discipline) and the [Preonic](https://drop.com/buy/preonic-mechanical-keyboard). It is designed as a DIY through-hole kit and uses the ProMicro as its controller.

[More images here](https://imgur.com/a/b0JINqX)

* Keyboard Maintainer: [vinamarora8](https://github.com/vinamarora8)
* Hardware Supported: 0-Sixty PCB
* Hardware Availability: Private Group-Buy

Getting the board into bootloader mode:

To be able to flash firmware onto this board, you'll need to bring the ProMicro into bootloader mode. Simply tap the small reset button twice. The button is placed to the right of the ProMicro.

Make example for this keyboard (after setting up your build environment):

    make 0_sixty:default

Flashing example for this keyboard:

    make 0_sixty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
