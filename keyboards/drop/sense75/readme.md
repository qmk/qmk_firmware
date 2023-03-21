# SENSE75

![SENSE75](https://massdrop-s3.imgix.net/img_thread/1660887363422.771277068120058315243585-5419copycrop.jpg?auto=format&fm=jpg&fit=max&w=500&h=868&dpr=2)

* Keyboard Maintainer: [zvecr](https://github.com/zvecr)
* Hardware Availability: <https://drop.com/buy/drop-sense75-mechanical-keyboard>

Make example for this keyboard (after setting up your build environment):

    make drop/sense75:default

Flashing example for this keyboard:

    make drop/sense75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press and hold the button under the space bar
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
