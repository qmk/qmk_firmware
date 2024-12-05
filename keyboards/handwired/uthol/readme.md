# Uthol

![Uthol](https://i.imgur.com/weFwdhfh.jpeg)

A handwired 50% (12x5) ortholinear keyboard made by Uthol

* Keyboard Maintainer: [Uthol](https://github.com/Uthol)
* Hardware Supported: Pro Micro ATMega32u4, Blackpill STM32F4x1 
* Hardware Availability: [Pro Micro](https://www.sparkfun.com/products/12640), [Blackpill STM32F4x1 ](https://www.aliexpress.com/item/1005001456186625.html)

Make example for this keyboard (after setting up your build environment):

    make handwired/uthol/rev2:default

Flashing example for this keyboard:

    make handwired/uthol/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: On the Pro Micro, short the `GND` and `RST` pins. On the Blackpill, press `BOOT0` key and the `RST` key, then release the `RST` key, and release the `BOOT0` key 
* **Keycode in layout**: Press the key mapped to `Settings + Backspace`
