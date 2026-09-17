# splaytoraid

![splaytoraid](https://i.imgur.com/N85DPHGh.png)

A 40% ergonomic keyboard with a stacked acrylic case and RGB underglow.

* Keyboard Maintainer: [freya](https://github.com/freya-irl)
* Hardware Supported: PCB kit and Pro Micro compatible controller
* Hardware Availability: [here](https://keeb.supply/products/splaytoraid-messenger-edition)

Make example for this keyboard (after setting up your build environment):

    make 0xcb/splaytoraid:default
    
Flashing example for this keyboard:

    make 0xcb/splaytoraid:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the left top 4. col key (usually Escape) and plug in the keyboard
* **Physical reset button**: Press the button on the controller (Helios) for more than 500ms or just press it (Pluto)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

When using an AVR microcontroller with this keyboard, the bootloader is configured to be QMK DFU for compatibility with [0xCB Pluto](https://github.com/0xCB-dev/0xCB-Pluto). If your microcontroller does not use this bootloader, ensure to set this parameter appropriately in your keymap's `rules.mk` file.
