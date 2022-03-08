# zhou65 version 1.0

A 65% keys keyboard with rgb (keys).
This keyboard use 8mhz HSE and STM32F401 as MCU.

- Keyboard Maintainer: https://github.com/jiaxin96
- Hardware Supported: zhou65
- Hardware Availability: https://github.com/Oh-My-Mechanical-Keyboard 

Make example for this keyboard (after setting up your build environment):

    make yandrstudio/zhou65:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
* **Physical reset pins**: Short circuit the `bt0` and `vcc` pins on the back of the PCB and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.
