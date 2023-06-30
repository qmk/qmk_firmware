# gl516/xr63gl

![gl516/xr63gl](https://i.imgur.com/zSbrTmIh.jpg)

Layout with only the Arrow key added to the 60% keyboard.

* Keyboard Maintainer: [gachiham](https://github.com/gachiham)
* Hardware Supported: XR63GL PCB, XIAO RP2040
* Hardware Availability: [PCB Data](https://github.com/gachiham/XR63GL)

Make example for this keyboard (after setting up your build environment):

    make gl516/xr63gl:default

Flashing example for this keyboard:

    make gl516/xr63gl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,1) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
