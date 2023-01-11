# Navi60

![Navi60](https://i.imgur.com/ON9yvP1h.png)

A 60% PCB with standard and tsangan bottom row compatibility, iso enter/left shift, split backspace,right shift, and stepped/standard capslock

* Keyboard Maintainer: [DeskDaily](https://github.com/DeskDaily)
* Hardware Supported: Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make navi60:default
	
Flashing example for this keyboard:

    make navi60:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the upper left key/esc) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
