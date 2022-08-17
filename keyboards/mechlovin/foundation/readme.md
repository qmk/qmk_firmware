# Foundation

![Foundation](https://i.imgur.com/6VaQ8zml.jpeg)

A PCB for Foundation FRL keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Foundation, APM32F103 
* Hardware Availability: [Protozoa Studio](https://protozoa.studio/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/foundation:default

Flashing example for this keyboard:

    make mechlovin/foundation:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader reset**: Hold down the key at (0,13) in the matrix (Backspace) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
* **Hardware reset**: Press reset button (located on the bottom side of the PCB) 