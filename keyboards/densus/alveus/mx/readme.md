# Alveus

![Alveus PCB](https://i.imgur.com/tZKcLiMh.png)

A MX PCB for Alveus FRL keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://mechlovin.studio/)
* Hardware Supported: Alveus, APM32F103 
* Hardware Availability: [Densus](https://www.instagram.com/densusdesign/)

Make example for this keyboard (after setting up your build environment):

    make densus/alveus/mx:default

Flashing example for this keyboard:

    make densus/alveus/mx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader reset**: Hold down the key at (0,13) in the matrix (Backspace) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Hardware reset**: Press reset button (located on the bottom side of the PCB) 