# YMDK ONI Tsangan

![ONI Tsangan PCB, Hotswap Tsangan/HHKB-like PCB with RGB Matrix and backlight](https://i.imgur.com/DB87on8.jpeg)

Customizable 60% Tsangan/HHKB-like Hotswap PCB by [YMDK](https://ymdkey.com).

- Keyboard Maintainer: [chrisgve](https://github.com/chrisgve)
- Hardware Supported: YMDK ONI Tsangan/HHKB-like
- Hardware Availability: [YMDK ONI Tsangan/HHKB-like](https://ymdkey.com/products/ymdk-gh60-hhkb-style-tsangan-oni-hot-swappable-both-underglow-switch-rgb-via-programmable-pcb-compatible-with-tokyo-60)

Make example for this keyboard (after setting up your build environment):

    make ymdk/oni_tsangan:default

The keyboard uses a DFU bootloader. To make a keymap and use dfu to flash it:

    make ymdk/oni_tsangan:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
- **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
