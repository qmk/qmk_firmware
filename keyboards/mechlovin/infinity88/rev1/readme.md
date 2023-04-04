# infinity88 Rev. 1

![infinity88](https://i.imgur.com/9JGxJjVl.png)

A replacement PCB for TKL keyboard. South-facing stabilisers.  

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Infinity88 Rev.1 STM32F303.
* Hardware Availability: [Mechlovin Store](https://mechlove.com).

Make example for this keyboard (after setting up your build environment):

    make mechlovin/infinity88/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
