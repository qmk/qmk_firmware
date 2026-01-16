# Scorpio Rev2

![Scorpio Rev2](https://i.imgur.com/pfSLX67h.jpeg)

This keyboard use 8MHz HSE and STM32F103 as MCU.

* Keyboard Maintainer: https://github.com/khchen2004
* Hardware Supported: Scorpio Rev2 PCB
* Hardware Availibility: Private GB

Make example for this keyboard (after setting up your build environment):
    
    make kwstudio/scorpio_rev2:default
    
Flashing example for this keyboard:

    make kwstudio/scorpio_rev2:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available