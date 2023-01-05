# Mona v1.1 (ATmega32A version)

![Mona v1.1](https://i.imgur.com/VaWcIkjl.png)

A gummy-worm o-ring mount 60% marble keyboard. Now with ALPS/MX, Caps Lock LED, and split spacebar support. ATmega32A version exists because I need alternatives because of the chip shortage.

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: ATmega32A

To get to the bootloader, with the USB cable plugged in, press the `RESET` button on the back of the PCB.

Make example for this keyboard (after setting up your build environment):

    make ramonimbao/mona/v32a:default

Flashing example for this keyboard:

    make ramonimbao/mona/v32a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
