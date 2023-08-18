# DeskDaily Octopad+

![Octopad+](https://i.imgur.com/Sa83N0Gh.jpg)

Aluminum version of the Octopad. An 8 key macropad with 2 rotary encoders.

* Keyboard Maintainer: [DeskDaily](https://github.com/DeskDaily)
* Hardware Supported: atmega32u4

Make example for this keyboard (after setting up your build environment):

    make nightly_boards/octopadplus:default
	
Flashing example for this keyboard:

    make nightly_boards/octopadplus:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key among the 8 keys) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
