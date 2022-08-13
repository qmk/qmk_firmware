# pikatea/pikatea_macropad_gb4

![pikatea](https://i.imgur.com/UpcSHLih.png)

*3, 5 or 7 keys and a knob mounted to an underside surface*

* Keyboard Maintainer: [Jack Kester](https://github.com/JackPikatea)
* Hardware Supported: *M32u4*
* Hardware Availability: *http://www.pikatea.com*

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Make example for this keyboard (after setting up your build environment):

    make pikatea/pikatea_macropad_gb4:default

Flashing example for this keyboard:

    make pikatea/pikatea_macropad_gb4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
