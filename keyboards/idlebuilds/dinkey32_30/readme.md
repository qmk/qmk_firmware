# Dinkey 32|30

![Dinkey 32|30 — 30 key config](https://i.imgur.com/L7e2yfP.jpeg)
![Dinkey 32|30 — 32 key config](https://i.imgur.com/iEurnyP.jpeg)

A low-profile split keyboard with 30 or 32 key configuration. Part of the Dinkey keyboard series by Idle Builds.

* Keyboard Maintainer: [IdleBuilds](https://github.com/IdleBuilds)
* Hardware Supported: Dinkey 32|30 PCB, ATmega32U4
* Hardware Availability: [Store](https://www.idlebuilds.com), [Idle Builds GitHub](https://github.com/IdleBuilds/Dinkey)

Make example for this keyboard (after setting up your build environment):

    make idlebuilds/dinkey32_30:default

Flashing example for this keyboard:

    make idlebuilds/dinkey32_30:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key on left half) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
