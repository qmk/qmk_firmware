<<<<<<< HEAD
# 3-Key-Ecosystem - 2key devices (2key/noled, 2key/rgb)

![2key devices](https://i.imgur.com/IJ1Zyc7.jpeg)

This is a 2x1 macro keyboard.
It's designed for a modular keyboard mount using an ATmega32U4.
There are two versions: 2key/noled (no controlled LEDs), and 2key/rgb (uses WS2812B LEDs).

* Keyboard Maintainer: [softplus](https://github.com/softplus)
* Hardware Supported: [3keyecosystem 2key/noled](https://github.com/softplus/3keyecosystem/tree/main/2key/2key1) and [2key/rgb](https://github.com/softplus/3keyecosystem/tree/main/2key/2key2)
=======
# 3-Key-Ecosystem - 6key devices (6key/rgb, 6key/noled)

![6key devices](https://i.imgur.com/AQfIblM.jpg)

This is a 3x2 macro keyboard.
It's designed for a modular keyboard mount using an ATmega32U4.
There are two versions: 6key2 (uses WS2812B & kbmount), and kai6 (uses individual LEDs).

* Keyboard Maintainer: [softplus](https://github.com/softplus)
* Hardware Supported: [3keyecosystem-6key/rgb](https://github.com/softplus/3keyecosystem/tree/main/6key/6key2) and [6key/noled](https://github.com/softplus/3keyecosystem/tree/main/6key/kai6)
>>>>>>> 6cace2269f (refactored 2key2->2key)
* Hardware Availability: Open-Source files at above link

Make example for this keyboard (after setting up your build environment):

<<<<<<< HEAD
    make 3keyecosystem/2key/rgb:default

Flashing example for this keyboard:

    make 3keyecosystem/2key/rgb:default:flash
=======
    make 3keyecosystem/6key/rgb:default

Flashing example for this keyboard:

    make 3keyecosystem/6key/rgb:default:flash
>>>>>>> 6cace2269f (refactored 2key2->2key)

## Bootloader

To Enter the bootloader, click reset button on the main board.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
