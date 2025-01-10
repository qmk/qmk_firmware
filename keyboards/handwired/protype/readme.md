# Cherry Protype Display Typewriter

![handwired/protype](https://i.imgur.com/hcFikid.jpeg)

Handwired RP2040 Pro Micro (Community Edition) on Cherry Protype Display Typewriter PCB.

* Keyboard Maintainer: [nooges](https://github.com/nooges)
* Hardware Supported: RP2040 Pro Micro Controller

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/protype -km default

Flashing example for this keyboard:

    qmk flash -kb handwired/protype -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the Boot button on the microcontroller and then press Reset
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
