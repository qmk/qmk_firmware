# subrezon/lancer

The [Lancer](https://github.com/subrezon/lancer) is a 36-key ortholinear keyboard with a light split and a focus on compact footprint and portability. It is a direct successor to [la_nc](https://github.com/subrezon/la_nc), and is very much inspired by other keyboards like Planck, Lumberjack and Lesovoz. Powered by a Pro Micro compatible MCU board and featuring battery and nice!view support, it offers a simple and productive typing experience, both with and without the wire.

![subrezon/lancer](https://i.imgur.com/W41Vx4rh.jpg)

* Keyboard Maintainer: [Daniel Osipishin](https://github.com/subrezon)
* Hardware Supported: Lancer PCB, with a ProMicro or other compatible MCU board
* Hardware Availability: https://github.com/subrezon/lancer

Make example for this keyboard (after setting up your build environment):

    make subrezon/lancer:default

Flashing example for this keyboard:

    make subrezon/lancer:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
