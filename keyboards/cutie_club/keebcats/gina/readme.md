# Gina

![Gina](https://i.imgur.com/YDcBEJ8h.jpg)

Gina, a versatile Macro-Numpad by KeebCats designed to be used in either a right-handed or left-handed configuration.

* Keyboard Maintainer: [Cutie Club](https://github.com/cutie-club/)
* Hardware Supported: ATMega32u4 based PCB which connects to a secondary matrix board through I2C
* Hardware Availability:
  * UK, EU (& worldwide): [KeebCats](https://keebcats.co.uk/products/gina-macro-numpad-by-keebcats-kit)
  * USA & Canada: [Space Cables](https://spaceholdings.net/products/gina-macro-numpad-by-keebcats-kit)
  * Asia: [iLumkb](https://ilumkb.com/products/gina-macro-numpad-by-keebcats-kit)

Make example for this keyboard (after setting up your build environment):

    make cutie_club/keebcats/gina:default

Flashing example for this keyboard:

    make cutie_club/keebcats/gina:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
