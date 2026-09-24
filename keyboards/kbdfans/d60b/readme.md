# KBDfans D60B

Customizable 60% Tsangan Hotswap by PCB by [KBDfans](https://kbdfans.com).
This board has also, at times, been referred to as the Sun60, but the name on the PCB is D60 B.

- Keyboard Maintainer: [chrisgve](https://github.com/chrisgve)
- Hardware Supported: KBDfans D60B
- Hardware Availability: no longer available for sale

Make example for this keyboard (after setting up your build environment):

    make kbdfans/d60b:default

The keyboard uses a DFU bootloader. To make a keymap and use dfu to flash it:

    make kbdfans/d60b:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
- **Physical reset button**: Short the two pads close to the position of the caps lock key
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
