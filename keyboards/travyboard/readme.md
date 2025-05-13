# travyboard

![travyboard](https://i.imgur.com/0HxqCsD.jpeg)

A split 23 key keyboard created from scratch. Firmware is written as well, but QMK support is important as well.

* Keyboard Maintainer: [Travis Hepworth](https://github.com/travmonkey)
* Hardware Supported: *travyboard pcb + waveshare rp2040 zero*
* Hardware Availability: *DIY only, [travyboard repository](https://github.com/travishepworth/travyboard)*
    * NOTE: If using my PCBv1, you will need to bridge TX and RX on the pico for qmk.

Make example for this keyboard (after setting up your build environment):

    make travyboard:default

Flashing example for this keyboard:

    make travyboard:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader via the boot button on the rp2040 zero:

* **Reset Button**: Hold down the boot button and press the reset button on the board
* **Boot Button**: Hold down the boot button and plug in the USB cable
