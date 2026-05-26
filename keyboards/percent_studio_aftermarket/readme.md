# percent_studio_aftermarket

![percent_studio_aftermarket](https://i.imgur.com/nQAFCH0.png)

*This code is specifically for the aftermarket QMK PCB maintained by Jubakuba that enables QMK for the Volt80 by Percent Studio.  This firmware should NOT be flashed on the stock PCB.  The PCB needs to be ordered using a PCB provider using the hardware link below.  This PCB will fit in the Volt 80 keyboard and work as expected.*

* Keyboard Maintainer: [Mike Tihonovich](https://github.com/Jubakuba)
* Hardware Supported: [Custom PCB](https://github.com/Jubakuba/Volt-80-Kicad)
* Hardware Availability: https://github.com/Jubakuba/Volt-80-Kicad

Make example for this keyboard (after setting up your build environment):

    make percent_studio_aftermarket:default

Flashing example for this keyboard:

    make percent_studio_aftermarket:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
