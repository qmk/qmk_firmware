# Pikatea Macropad R26 LED Kit

![pikatea](https://i.imgur.com/woHSx3n.jpg)

*8 keys and 1 knob macropad. 3D printed bracket mounted case*

* Keyboard Maintainer: [Jack Kester](https://github.com/JackPikatea)
* Hardware Supported: *M32u4*
* Hardware Availability: *http://www.pikatea.com*

Enter the bootloader in 3 ways:

* **Short Gnd and Rst**: connect the pins labelled GND and RST together while the device is connected.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.
* **bootmagic**: Hold the top left key while plugging in the device.

Make example for this keyboard (after setting up your build environment):

    make pikatea/pikatea_macropad_r26_led_kit:default

Flashing example for this keyboard:

    make pikatea/pikatea_macropad_r26_led_kit:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
