# BunnyGirl65

![BunnyGirl65](https://i.imgur.com/APqNMhc.jpeg)

A Wibu 60% keyboard PCB Design by inspire of Nekomata Okayu and can fit many keyboard case

* Keyboard Maintainer: [Mai The San](https://github.com/maithesan)
* Hardware Supported: BunnyGirl65
* Hardware Availability: [Waifu.Works](https://discord.gg/waifuworks)

Make example for this keyboard (after setting up your build environment):

    make sawnsprojects/bunnygirl65:default

Flashing example for this keyboard:

    make sawnsprojects/bunnygirl65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
