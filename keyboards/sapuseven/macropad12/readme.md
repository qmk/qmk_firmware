# macropad

![macropad12](https://i.imgur.com/StqDhH8h.png)

A simple, configurable 12-key MacroPad.

* Keyboard Maintainer: [SapuSeven](https://github.com/SapuSeven)
* Hardware Supported: MacroPad12 PCB v2.0
* Hardware Availability: *coming soon*

Make example for this keyboard (after setting up your build environment):

    make sapuseven/macropad12:default

Flashing example for this keyboard:

    make sapuseven/macropad12:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB using a thin long object while the keyboard is connected
* **Keycode in layout**: Press the key mapped to `BOOTLOADER` if it is available
