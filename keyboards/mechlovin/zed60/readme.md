# zed60

![zed60](https://i.imgur.com/KyTpfmMl.png)

Zed60 PCB, 60% keyboard PCB.
* Keyboard Maintainer: [Mechlovin'](https://mechlovin.studio)
* Hardware Supported: Zed60, APM32F103
* Hardware Availability: [Mechlovin'](https://mechlovin.studio)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/zed60:default

Flashing example for this keyboard:

    make mechlovin/zed60:default:flash

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Bootloader**: Hold down the key at (0,13) in the matrix (Backspace) and plug in the keyboard 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
