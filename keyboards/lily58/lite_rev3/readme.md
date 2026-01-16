# Lily58 Lite Rev3

![lily58_lite](https://i.imgur.com/RCx5Xym.jpeg)
![lily58_lite_rev3_pcb](https://i.imgur.com/rIjVjCE.png)


* Keyboard Maintainer: [yuchi](https://github.com/kata0510)
* Hardware Supported: RP2040-Zero
* Hardware Availability: [PCB Link](https://github.com/kata0510/Lily58/tree/master/Lite_Rev3)
* Other Information(ja) [Link](https://docs.liliums.net/lily58-lite-rev3/about/)

Make example for this keyboard (after setting up your build environment):

    make lily58/lite_rev3:default

Flashing example for this keyboard:

    make lily58/lite_rev3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
