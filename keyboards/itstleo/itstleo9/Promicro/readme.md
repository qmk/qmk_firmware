# itstleo/handwired/it9_32u4

Handwired 3x3 macropad built with Pro Micro compatible microcontrollers

* Keyboard Maintainer: [Its TLeo](https://github.com/Its TLeo)
* Hardware Supported: Promicro ATmega32u4
* Hardware Availability: [Promicro](https://aliexpress.com/item/32888212119.html)

Make example for this keyboard (after setting up your build environment):

    make itstleo/handwired/it9_32u4:default

Flashing example for this keyboard:

    make itstleo/handwired/it9_32u4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).  Dont know how to make a handwire keyboard, check it out [SkottoKeebs handwire tutorial](https://www.youtube.com/watch?v=hjml-K-pV4E&pp=ygUTaGFuZHdpcmUgYSBtYWNyb3BhZA%3D%3D)

## Matrix pin

*    **cols** :     D1  ,  D0   ,  D4
*    **rows** :     F4  ,  F5   ,  F6

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
