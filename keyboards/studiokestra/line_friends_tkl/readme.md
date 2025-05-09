# studiokestra/line_friends_tkl

![studiokestra/line_friends_tkl](https://i.imgur.com/3MmRQkh.png)

PCB developed for Mino Keys in collaboration with Line Friends (C).

* Keyboard Maintainer: [Studio Kestra](https://github.com/studiokestra/)
* Hardware Supported: LINE FRIENDS TKL
* Hardware Availability: https://minokeys.com/collections/line-friends

Make example for this keyboard (after setting up your build environment):

    make studiokestra/line_friends_tkl:default

Flashing example for this keyboard:

    make studiokestra/line_friends_tkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
