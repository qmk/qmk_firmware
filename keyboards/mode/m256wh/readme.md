# Mode M256-WH PCB QMK Firmware

![m256wh](https://imgur.com/97KRZCrh.jpg)

The M256-WH is the hotswap version PCB support for the Mode Envoy.

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: proprietary PCBs using the STM32F401 microcontroller;
* Hardware Availability: as of april 18, these PCBs are on the verge of being sold with the first kits of the Mode Envoy.

## How to flash

In order to flash this PCB, first build the default layout (after setting up your build environment):

    make mode/m256wh:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the back of the PCB for at least five seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (escape key, layer 1 of the default keymap)
