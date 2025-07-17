# ATSET ATR1

![ATSET AT1](https://imgur.com/fu0iXD0.jpg)

A 9% macropad.

* Keyboard Maintainer: [atset]
* Hardware Supported: ATR1 R1 PCB with STM32F103
* Hardware Availability: [https://atsetmediscience.com](https://atsetmediscience.com)

Make example for this keyboard (after setting up your build environment):

    make atset/atr1/r1:default
	    
Flashing example for this keyboard:
	
	make atset/atr1/r1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button under the small hole on the back of the macropad
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
