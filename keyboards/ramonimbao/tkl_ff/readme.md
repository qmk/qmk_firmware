# TKL-FF

![TKL-FF](https://i.imgur.com/GJCo3F5l.png)

A TKL PCB made for the Geonworks Frog keyboard that supports both F12 and F13. V2 simply adds RGB indicator LEDs.

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: ATmega32u4

Make example for this keyboard (after setting up your build environment):

    make ramonimbao/tkl_ff:default
    
To get to the bootloader, simply press the reset button located at the back of the PCB. You can then flash new firmware onto it.

Flashing example for this keyboard:

    make ramonimbao/tkl_ff:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
