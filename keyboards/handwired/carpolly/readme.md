# carpolly

![](https://imgur.com/w691sNn)

Keyboard Maintainer: Paul Enrico N. Viola (https://github.com/PollyV1)                                                                                                      Hardware Supported: Teensy 2 controller                                                                                                                                     Hardware Availability: [PollyV1] https://github.com/PollyV1/Carpolly

carpolly - a handwired keyboard on a teensy 2 controller

Make example for this keyboard (after setting up your build environment):

    make carpolly/default:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the controller.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available. (Layer 3 + T)
