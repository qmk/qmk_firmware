# itstleo9

Handwired 3x3 macropad built with Pro Micro compatible microcontrollers

* Keyboard Maintainer: [ItsTLeo](https://github.com/ItsTLeo)
* Hardware Supported: RP2040/ATmega32U4 Pro Micro
* Hardware Availability: [RP2040](https://aliexpress.com/item/1005005616524430.html), [ATmega32U4](https://aliexpress.com/item/32888212119.html)

Make example for this keyboard (after setting up your build environment):

    make handwired/itstleo9/promicro:default
    make handwired/itstleo9/rp2040:default
    
Flashing example for this keyboard:

    make handwired/itstleo9/promicro:default:flash
    make handwired/itstleo9/rp2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). Dont know how to make a handwire keyboard, check it out [SkottoKeebs handwire tutorial](https://www.youtube.com/watch?v=hjml-K-pV4E&pp=ygUTaGFuZHdpcmUgYSBtYWNyb3BhZA%3D%3D)

## Matrix pin (RP2040 ver)

*    **cols** :     GP10  ,  GP11   ,  GP12
*    **rows** :     GP21  ,  GP20   ,  GP19

## Matrix pin (Promicro ver)

*    **cols** :     D1  ,  D0   ,  D4
*    **rows** :     F4  ,  F5   ,  F6

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Double-press reset button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available