# %KEYBOARD%

![%KEYBOARD%](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [%YOUR_NAME%](https://github.com/yourusername)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make %KEYBOARD%:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make %KEYBOARD%:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:
* Bootmagic reset: hold down the top left key (usually escape) and plugin the keyboard
* Physical reset button: If there is a button on the back of the PCB, please press it briefly.
* Keycode in layout: Specifically, if there is a `RESET` keycode, and it's location. 
