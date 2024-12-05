# IBE60

PCB mounted 60% PCB for the IBE60 in fixed true HHKB layout

* Keyboard Maintainer: [Stefan Sundin](https://github.com/4pplet)
* Hardware Supported: IBE60 Solder PCB

Make example for this keyboard (after setting up your build environment):

    make 4pplet/ibe60:default

Flashing example for this keyboard:

    make 4pplet/ibe60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical reset button**: Short the reset-header (labled BL/RESET) on the back of the PCB for about 2 seconds for the keyboard to enter bootloader
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
