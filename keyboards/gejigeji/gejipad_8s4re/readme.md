# Gejipad 8S4RE

![Gejipad 8S4RE](https://i.imgur.com/26ZNlLf.jpeg)

A custom controller with 8 switches and 4 rotary encoders based on the ATmega32U4 (Pro Micro).

* Keyboard Maintainer: [gejigeji-com](https://github.com/gejigeji-com)
* Hardware Supported: Gejipad 8S4RE PCB (ATmega32U4 / Pro Micro)
* Hardware Availability: Open source (KiCad design files available at [gejigeji-com/gejipad_8s4re](https://github.com/gejigeji-com/gejipad_8s4re))

Make example for this keyboard (after setting up your build environment):

    make gejigeji/gejipad_8s4re:default

Flashing example for this keyboard:

    make gejigeji/gejipad_8s4re:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key (SW6) and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on the Pro Micro
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is present in your keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
