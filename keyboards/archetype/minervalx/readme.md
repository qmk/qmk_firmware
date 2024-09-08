# Minerva LX

![Minerva LX](https://i.imgur.com/f97nsrx.jpg)

The following is the QMK Firmware for the Minerva LX PCB.

* Keyboard Maintainer: [Archetype](https://github.com/archetype-made)
* Hardware Supported: RP2040-based proprietary PCB.
* Hardware Availability: https://archetypemade.com/minerva-is-here/

Make example for this keyboard (after setting up your build environment):

    make archetype/minervalx:default

Flashing example for this keyboard:

    make archetype/minervalx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available
* **Physical Reset Button**: With the PCB unplugged, hold down the button labled `RESET` on the back of the PCB while pluggin in the USB.