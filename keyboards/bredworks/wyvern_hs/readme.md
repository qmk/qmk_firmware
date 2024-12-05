# Bredworks Wyvern HS

* Keyboard Maintainer: [DeskDaily](https://github.com/DeskDaily)
* Hardware Supported: Atmega32u4
* Hardware Availability: [BredWorks](https://bredworks.com/products/wyvern-hotswap-pcb)

Make example for this keyboard (after setting up your build environment):

    make bredworks/wyvern_hs:default
	
Flashing example for this keyboard:

    make bredworks/wyvern_hs:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the upper left key/esc) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
