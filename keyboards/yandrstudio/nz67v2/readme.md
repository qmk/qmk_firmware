# nz67v2

![nz67v2](https://i.imgur.com/AHmBuAqh.png)

A 67 keys keyboard with rgb (key and underground).
This keyboard use 16mhz HSE and APM32F103 as MCU.

- Keyboard Maintainer: https://github.com/jiaxin96
- Hardware Supported: nz67v2
- Hardware Availability: [Y&R Works](https://shop417111022.taobao.com/?spm=2013.1.1000126.2.6aea6fa3Uxufe5), [5162](https://shop294487007.taobao.com/?spm=a230r.7195193.1997079397.2.763853eeeaoRl4)

Make example for this keyboard (after setting up your build environment):

    make yandrstudio/nz67v2:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
