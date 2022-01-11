# carpolly

![carpool](https://i.imgur.com/w691sNnh.jpg)

* Keyboard Maintainer: Paul Enrico N. Viola (https://github.com/PollyV1)
* Hardware Supported: Teensy 2 controller
* Hardware Availability: [PollyV1] https://github.com/PollyV1/Carpolly

carpolly - a handwired keyboard on a teensy 2 controller

## Make 

Make example for this keyboard (after setting up your build environment):

    make handwired/carpolly:default

## Flashing

Flashing example for this keyboard:

    make handwired/carpolly:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the RESET button on the controller.
* **Keycode in layout**: Longpress ALT + ESC
