# atmega32U4 board for IBM Model M, old LEDs replaces with WS2812 RGB LEDs

![modelm](https://raw.githubusercontent.com/mschwingen/hardware/master/modelm-usb/images/PCB.jpg)

This is a configuration of QMK intended to be used with the [Model M USB PCB](https://github.com/mschwingen/hardware/tree/master/modelm-usb).

* Keyboard Maintainer: [Michael Schwingen](https://github.com/mschwingen/)
* Hardware Supported: [Model M USB PCB](https://github.com/mschwingen/hardware/tree/master/modelm-usb)
* Hardware Availability: need to build your own.

Make example for this keyboard (after setting up your build environment), run one of:

    make ibm/model_m/mschwingen/led_ws2812:default

Flashing example for this keyboard:

    make ibm/model_m/mschwingen/led_ws2812:default:flash

Bootloader: do not use the QMK bootloader, use the bootloader from [here](https://github.com/mschwingen/modelm-lufa-bootloader)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
