# iso85k

*A 85-key ISO keyboard*

* Keyboard Maintainer: [Fredrik A. Kristiansen](https://github.com/FredrikAleksander)
* Hardware Supported: Custom PCB using STM32F072
* Hardware Availability: PCB gerbers available upon request (fredrikaxk@gmail.com)

Make example for this keyboard (after setting up your build environment):

    make handwired/iso85k:via

Flashing example for this keyboard:

    make handwired/iso85k:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB, while shorting the pins marked BOOT0
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
