# morisoba/bitdeck10

![morisoba/bitdeck10](https://imgur.com/ca8egkz.jpg)
BitDeck10 is a 5x2 keys + 1 rotary encoder macro keyboard with OLED.

* Keyboard Maintainer: [morisoba](https://github.com/morisobaR)
* Hardware Supported: BitDeck10 PCB, XIAO RP2040
* Hardware Availability: [morisoba-hi.booth.pm](https://morisoba-hi.booth.pm/)

Make example for this keyboard (after setting up your build environment):

    make morisoba/bitdeck10:default

Flashing example for this keyboard:

    make morisoba/bitdeck10:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double press the Reset button on the XIAO RP2040, or hold the Boot button and tap the Reset button. 
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
