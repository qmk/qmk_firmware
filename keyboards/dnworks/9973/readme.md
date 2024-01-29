# 997.3 TKL

![997.3 TKL](https://i.imgur.com/iPPLKg1h.jpeg)

PCB that supports the 997.3 TKL designed by dnworks, including its variants.

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: 997.3 Solder PCB rev1 
* Hardware Availability: dnworks.co

Make example for this keyboard (after setting up your build environment):

    make dnworks/997pt3:default

Flashing example for this keyboard:

    make dnworks/997pt3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the `RESET` button twice or short the `USB_BOOT` and `GND` pads and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available