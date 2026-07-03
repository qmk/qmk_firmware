# ZeroPad

![ZeroPad](https://i.imgur.com/KBkI4q1.jpeg)

This keyboard is inspired by the scotto9 from Joe Scotto. This keyboard is compatible with via and has 4 layers of keybinds (24 keybinds - 4x8 + 1 per layer for changing the layer).

* Keyboard Maintainer: [Leon Sieber](https://github.com/diffrentGuesser)
* Hardware Supported: Pro Micro, 3 pin switches
* Hardware Availability: [Pro Micro](https://de.aliexpress.com/item/32846843498.html?spm=a2g0o.cart.0.0.146d4ae4kCjqDY&mp=1&gatewayAdapt=glo2deu), [switches](https://de.aliexpress.com/item/1005007135709029.html?spm=a2g0o.cart.0.0.146d4ae4kCjqDY&mp=1&gatewayAdapt=glo2deu)

Make example for this keyboard (after setting up your build environment):

    make handwired/zeropad:default

Flashing example for this keyboard:

    make handwired/zeropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard 
* **Physical reset**: Short the GND and the RST pins on the Pro Micro.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
