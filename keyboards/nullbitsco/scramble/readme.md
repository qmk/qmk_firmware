# SCRAMBLE

![SCRAMBLE](https://nullbits.co/static/img/scramble1.jpg)

A 6-switch key tester macropad built by nullbits. [More info at nullbits.co](https://nullbits.co/scramble/)

* Keyboard Maintainer: [Jay Greco](https://github.com/jaygreco)
* Hardware Supported: SCRAMBLE Rev1
* Hardware Availability: [nullbits.co](https://nullbits.co/)

Note: If you are seeing issues with MacOS and keyboard hangs after sleep, make sure `NO_USB_STARTUP_CHECK = yes` is set in your rules.mk.

In order to enter the bootloader, hold switch #6 while plugging in the USB cable. The LED will stay on to indicate that it's in DFU mode.

Flashing example for this keyboard:

    make nullbitsco/scramble:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
