
# RPK-001

[![p9HNfPg.png](https://s1.ax1x.com/2023/05/25/p9HNfPg.png)](https://imgse.com/i/p9HNfPg)

* Keyboard Maintainer: [JoyLee](https://github.com/itarze)
* Hardware Supported: RPK-001 PCB

Make example for this keyboard (after setting up your build environment):

    make phentech/rpk_001:default

Flashing example for this keyboard:

    make phentech/rpk_001:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
