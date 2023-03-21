# ms_sculpt

![ms_sculpt_with_cold_dry_joints](https://user-images.githubusercontent.com/105235786/168012266-4e235bf5-8d34-4731-ab17-2308a9d9a29e.jpg)

MS Sculpt Keyboard ISO-layout wired to STM32F401 / blackpill

* Keyboard Maintainer: [Jean Bernard](https://github.com/jn-bernard)
* Hardware Supported: MS Sculpt Keyboard ISO-layout, STM32F401
* Hardware Availability: Ebay

Make example for this keyboard (after setting up your build environment):

    make ms_sculpt:default

Flashing example for this keyboard:

    make ms_sculpt:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
