# JP60

![JP60](https://github.com/ai03-2725/JP60/raw/main/Render/Front.png)

GH60-compatible JIS-like hotswap keyboard PCB

* Keyboard Maintainer: [ai03](https://github.com/ai03-2725)
* Hardware Supported: [JP60 PCB](https://github.com/ai03-2725/JP60)
* Hardware Availability: To be made available in JP market soon; will be listed in the repo above

Make example for this keyboard (after setting up your build environment):

    make ai03/jp60:default

Flashing example for this keyboard:

    make ai03/jp60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
