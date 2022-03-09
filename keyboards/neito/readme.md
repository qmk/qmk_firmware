# Neito
### by Oliver Granlund

ISO-variant of TGR Alice with a few tweaks!

![First prototype](https://i.imgur.com/GbZAnIpl.jpg)

![First prototypes backside](https://i.imgur.com/h7Hx6EUl.jpg)

* Keyboard Maintainer: [Oliver Granlund](https://github.com/OlliGranlund)
* Hardware Supported: Neito PCB (ATmega32U4)
* Hardware Availability: Group Buys hosted on [https://olli.works](https://olli.works)

Getting the board into bootloader mode:

To be able to flash firmware onto this board, you'll need to bring the keyboard into bootloader mode. The keyboard has a debug-panel located between the keys "H" and "N". In this 2x3-panel, short the two pins which are furthest away from the atmega32u4 microcontroller. See the red arrows in the image below.

![Reset pins](https://i.imgur.com/fN2XjY8l.jpg)

Make example for this keyboard (after setting up your build environment):

    make neito:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
