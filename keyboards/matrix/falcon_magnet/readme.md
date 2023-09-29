# Falcon Magnet Switch keyboard

This was the PCB for Falcon and it supports the gateron magnet switch. Actually the PCB was based on the Falcon EC PCB and not optimized for the magnet switch,
and the matrix scan implementation can be also optimized. But it currently was a POC for the the magnet switch, so let it be.
It support APC(use keymap layer 4 to set the actuation point)and RT (keymap 5 was used). The special keycodes(F1 to F24) were used to set the actuation point.
F1 was the minimum, F24 was the maximum.

Keyboard Maintainer: [astro](https://github.com/yulei)  
Hardware Supported: Matrix Falcon Keyboard
Hardware Availability: Private GB 

Make example for this keyboard (after setting up your build environment):

    make matrix/falcon_magnet:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: *Not enabled by default.* Hold down the top left key and plug in the keyboard. This will also clear the emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Shotcut the BOOT0 socket and plug the USB cable.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the default keymap it is on the second layer, replacing the Tab key.
