# NIBBLE

![NIBBLE](https://nullbits.co/static/img/nibble1.jpg)

A unique, tweakable 65% keyboard kit built by nullbits. [More info at nullbits.co](https://nullbits.co/nibble/)

* Keyboard Maintainer: [Jay Greco](https://github.com/jaygreco)
* Hardware Supported: NIBBLE Rev1, Pro Micro comaptible MCUs.
* Hardware Availability: [nullbits.co](https://nullbits.co/)

Note: If you are seeing issues with MacOS and keyboard hangs after sleep, make sure `NO_USB_STARTUP_CHECK = yes` is set in your rules.mk.

Adds experimental "Remote Keyboard" functionality, which forwards keystrokes from an external macropad, keyboard, or numpad over UART/TRRS, removing the need for an additional USB connection. 

Make example for this keyboard (after setting up your build environment):

    make nullbitsco/nibble:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
