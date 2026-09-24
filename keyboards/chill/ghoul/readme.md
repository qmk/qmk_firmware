# Ghoul TKL

![image](https://i.imgur.com/Y39mNA4.jpeg)

A modern replacement PCB for Filco TKLs, adding support for PCB-mount stabilizers and popular alternate layouts. In-switch backlight LEDs are also supported.

* Keyboard Maintainer: [chillKB](https://github.com/chillKB)
* Hardware Supported: Ghoul TKL PCB
* Hardware Availability: [Open source on GitHub](https://github.com/chillKB/ghoulTKL)

Make example for this keyboard (after setting up your build environment):

    make chill/ghoul:default

Flashing example for this keyboard:

    make chill/ghoul:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key (usually Escape) and plug in the keyboard
* **Physical reset button**: Hold the boot button and tap the reset button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
