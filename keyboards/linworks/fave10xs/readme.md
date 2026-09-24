# fave10xs

![fave10xs](https://i.imgur.com/o4pq0mV.png)

Dolphin max PCB solder version Fave10xs

* Keyboard Maintainer: [Freather](https://github.com/Freather)
* Hardware Supported: STM32F072 Linworks Fave10xs PCB
* Hardware Availability: small gb ran in Asia

Make example for this keyboard (after setting up your build environment):

    make linworks/fave10xs:default

Flashing example for this keyboard:

    make linworks/fave10xs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the button on the back of the PCB then plug in the PCB with USB cable
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
