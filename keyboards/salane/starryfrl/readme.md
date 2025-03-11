# Starry FRL

![Starry FRL](https://i.imgur.com/eRYlEe7.jpeg)

 This firmware support for both Solder and Hotswap PCB of Starry FRL

 **Firmware files are SPECIFIC to each board. Firmware files from one, will not work on the other.** Please use the `uf2` appropriate for your board.

* Keyboard Maintainer: [Mai The San](https://github.com/MaiTheSan) 
* Hardware Supported: Starry FRL 
* Hardware Availability: [Waifu.works Discord](https://discord.gg/waifuworks)

Make examples for this keyboard (after setting up your build environment):

    make salane/starryfrl:default

Flashing example for this keyboard:

    make salane/starryfrl:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press the key `BOOT` in the back of PCB and plug in keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).