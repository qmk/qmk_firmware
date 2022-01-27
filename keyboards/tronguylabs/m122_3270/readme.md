# m122-3270

![IBM Model M 122 key](https://i.imgur.com/Oo3Ozqzh.jpg)

This is a replacement controller for the IBM Model M 122 key terminal keyboard running on a STM32F411 BlackPill, intended to act as closely to the 3270 keyboard's functioning as possible while still being usable on a PC.

* Keyboard Maintainer: [Jay Maynard](https://github.com/jmaynard)
* Hardware Supported: BlackPill STM32F411, Teensy++ 2.0
* Hardware Availability: [BlackPill](https://www.adafruit.com/product/4877), [Teensy](https://www.pjrc.com/store/teensypp.html)

Make example for this keyboard (after setting up your build environment):

    make tronguylabs/m122_3270/blackpill:default
    make tronguylabs/m122_3270/teensy:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

A schematic and Gerber files are publicly available for those wishing to have carrier boards made
professionally instead of handwiring things. The M122 matrix connectors plug right into it. It can
be found at https://github.com/jmaynard/tronguylabs-m122-blackpill.

This is derived from Luke Stanley's handwired/ibm122m keyboard, with my own keymapping and rework of the I/O for the BlackPill. There's also a version for the Teensy++ 2.0, since that was my original design and I still use one on one board, even though I switched to the BlackPill for future-proofing. The Teensy++ 2.0 is not recommended for new designs.
