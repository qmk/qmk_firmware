# dnworks TKL (F12)

![997.3 TKL](https://i.imgur.com/iPPLKg1h.jpeg)

PCB that supports the F12 TKLs designed by dnworks.

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: 997.3 Solder PCB rev1, 765LT Solder PCB rev1 and Best Friend Solder PCB Rev1.
* Hardware Availability: https://dnworks.co/products

Make example for this keyboard (after setting up your build environment):

    make dnworks/tkl87:default

Flashing example for this keyboard:

    make dnworks/tkl87:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down escape and plug in the keyboard
* **Physical reset button**: Short the 'USB_BOOT' button and plug in keyboard or press the 'RESET' button twice with the keyboard plugged in.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available