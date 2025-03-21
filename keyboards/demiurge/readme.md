# Demiurge

![demiurge-img-1](https://i.imgur.com/gnQ2Pj6h.jpeg)

# Keyboard Info

- 60% XT
- Keyboard Maintainer: [ojthetiny](https://github.com/ojthetiny)
- Hardware Supported: Demiurge PCB
- Hardware Availability: Through group-buy

Make example for this keyboard (after setting up your build environment):

    make demiurge:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
