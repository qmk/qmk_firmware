# transition80

![transition80](https://i.imgur.com/2A0AWs2h.jpg)
A 80% keyboard.

- Keyboard Maintainer: https://github.com/jiaxin96
- Hardware Supported: APM32F103 16MHZ
- Hardware Availability: [swagkeys](https://swagkeys.com/)

Make example for this keyboard (after setting up your build environment):

    make yandrstudio/transition80:default

Flashing example for this keyboard:

    make yandrstudio/transition80:default:flash


See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
