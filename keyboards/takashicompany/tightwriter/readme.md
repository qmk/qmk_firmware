# takashicompany/tightwriter

![Tightwriter](https://i.imgur.com/evVMdSRh.jpg)

Tightwriter is a 35-key keyboard.
The PCB is compatible with Cherry MX compatible key switches and Kailh Choc v1 key switches.
It can be equipped with backlight LEDs and a TRRS socket.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/tightwriter

Make example for this keyboard (after setting up your build environment):

caterina:
    make takashicompany/tightwriter:default

Many popular Pro Micro alternatives like the Elite-C, Bit-C, Sea-Micro, Puchi-C etc...
    make takashicompany/tightwriter:default:dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- Bootmagic reset: Hold down the top-left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
- Physical reset button: Briefly press the button on the back of the PCB.
- Keycode in layout: Press the key mapped to QK_BOOT. In the pre-supplied keymaps it is on the ninth layer, replacing the N key.
