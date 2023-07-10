# itstleo9

Handwired 3x3 macropad built with Pro Micro compatible microcontrollers

* Keyboard Maintainer: [ItsTLeo](https://github.com/ItsTLeo)
* Hardware Supported: RP2040, Promicro ATmega32u4
* Hardware Availability: [RP2040](https://aliexpress.com/item/1005005616524430.html?gatewayAdapt=glo2vnm),
                         [Promicro](https://aliexpress.com/item/32888212119.html)

Make example for this keyboard (after setting up your build environment):

    make itstleo/itstleo9:default

Flashing example for this keyboard:

    make itstleo/itstleo9:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). Dont know how to make a handwire keyboard, check it out [SkottoKeebs handwire tutorial](https://www.youtube.com/watch?v=hjml-K-pV4E&pp=ygUTaGFuZHdpcmUgYSBtYWNyb3BhZA%3D%3D)

## Matrix pin (RP2040 ver)

*    **cols** :     GP10  ,  GP11   ,  GP12
*    **rows** :     GP21  ,  GP20   ,  GP19

## Matrix pin (Promicro ver)

*    **cols** :     D1  ,  D0   ,  D4
*    **rows** :     F4  ,  F5   ,  F6

## Firmware flash (for RP2040)

When entered the bootloader mode, drag the .uf2 firmware into bootloader folder, wait a little bit and its all set, start using our new macropad

## Bootloader RP2040

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: **Hold boot button** and press **rst button** 2 time, when it's appear the folder of rp2040 you entered the bootloader mode
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Bootloader Promicro

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available