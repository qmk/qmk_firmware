# Sofle Choc Pro

![sofle_choc_pro](https://i.imgur.com/q9A2HMe.jpeg)

A complete remake of the Sofle Choc Keyboard by Josef Adamčík. Featuring an onboard RP2040 with 128 MB flash
memory and choc-spaced keys for a more compact keyboard.

- Keyboard Maintainer: [Keebart](https://github.com/Keebart)
- Hardware Supported: RP2040
- Hardware Availability: [Keebart Shop](https://keebart.com/products/sofle)

Make example for this keyboard (after setting up your build environment):

    make keebart/sofle_choc_pro:default

Flashing example for this keyboard:

    make keebart/sofle_choc_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the top left key of the left side of the keyboard while connecting the left side to the computer. Similarly, hold down the top right key of the right side of the keyboard while connecting the right side to the computer.
- **Physical reset button**: Briefly press the button on the back of the PCB
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
