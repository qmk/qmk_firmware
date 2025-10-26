# yacobo

![yacobo](https://i.imgur.com/1nfuWoa.jpeg)

*A replacement qmk-compatible control board for the 101-key Model M keyboards.
Inspired by and based on the ModelH by jhawthorn, in comparison this design uses 100% through-hole components, including the widely available STM32F103C8T6 "Blue Pill" development board, for ease of assembly.*

* Keyboard Maintainer: [Stephen Edwards](https://github.com/sje-mse)
* Hardware Supported: IBM 101-key Model M with Yacobo replacement control boards.
* Hardware Availability: [Yacobo PCB](https://github.com/sje-mse/yacobo).

Make example for this keyboard (after setting up your build environment):

    make yacobo:default

Flashing example for this keyboard:

    make yacobo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press the "Reset" button on the Blue Pill daughterboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
