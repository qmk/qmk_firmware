# lefishe

firmware for the 65xt keyboard designed around the symmetrical blocker 65% layout.
This pcb cab also be used as a replacement pcb for the revoKmini/kmacmini with some modification to the design

* Keyboard Maintainer: [Lyso1](https://github.com/lyso1)
* Hardware Supported: LeFishe, atmega32u4
* Hardware Availability: [/u/TheLysol_27](https://www.reddit.com/user/TheLysol_27)

Make example for this keyboard (after setting up your build environment):

    make lyso1/lefishe:default

Enter into the bootloader to flash new firmware in 3 ways:

	* **Bootmagic reset**: Hold down the key at (0,0) in the matrix(The F1 key in this case) and plug the the keyboard in. 
	* **Physical reset button**: Briefly press the button on the back and left side of the PCB(exactly under where the "2" key would be located) while the PCB is plugged in.
	* **Keycode in layout**: Press the key mapped to `RESET` (RALT + E in this case) while the keyboard is plugged in. 

Flashing example for this keyboard:

    make lyso1/lefishe:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
