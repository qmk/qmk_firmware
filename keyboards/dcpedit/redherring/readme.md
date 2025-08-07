# Red Herring

![Red Herring](https://i.imgur.com/b6lKmW0h.jpg)

Unibody ergonomic orthilinar keyboard with through-hole components.  Supports standard keycaps, a 64x128 OLED, large rotary encoder knob, and a solenoid.

* Keyboard Maintainer: [dcpedit](https://github.com/dcpedit)
* Hardware Supported: ATMEGA32A
* Hardware Availability: https://github.com/dcpedit/redherring

Make example for this keyboard (after setting up your build environment):

    make dcpedit/redherring:default

Flashing example for this keyboard:

    make dcpedit/redherring:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the ESC key (top-left key) and plug in the keyboard
* **Physical reset button**: On the PCB, while holding down the BOOT button, press and release the RESET button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available