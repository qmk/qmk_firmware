# ZLANT XL

![ZLANT XL](https://imgur.com/Vcmjwro.jpg)
_A unique 50% mechanical keyboard that uses a slanted ortholinear layout_

- Keyboard Maintainer: [chrisgve](https://github.com/chrisgve)
- Hardware Supported: Zlant XL w/Ziptyze's atmega32u2 powered controller [The Rune](https://1upkeyboards.com/shop/controllers/the-rune-by-ziptyze/)
- Hardware Availability: [1UP Keyboards](https://1upkeyboards.com/shop/keyboard-kits/diy-40-kits/zlantxl-50-mechanical-keyboard-kit/)

Make example for this keyboard (after setting up your build environment):

    make zlant_xl:default

Flashing example for this keyboard:

    make zlant_xl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
- **Physical reset button**: Briefly press the button on the back of the board (button on The Rune)
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
