# Sofle Pico Keyboard

![Sofle Pico](https://i.imgur.com/9VBj3T5.jpeg)
![Sofle Pico PCB](https://i.imgur.com/8SDTm4h.jpeg)
Sofle Pico is a 60% Raspberry Pi Pico powered split keyboard boasting a 4x6 layout with an aggressive columnar stagger. It has 5 "thumb" keys on either side, support for 2-4 rotary encoders, per-key RGB lighting, 128x64 OLEDs and a tenting puck mount.

- Keyboard Maintainer: [Ryan Neff](https://github.com/JellyTitan)
- Hardware Supported: Sofle Pico PCB v3.5.x, Raspberry Pi Pico
- Hardware Availability: [PCB, Case, Parts List](https://github.com/JellyTitan/Sofle-Pico)

Remember you have to flash both halves of the keyboard for it to work!

Make example for this keyboard (after setting up your build environment):

    make sofle_pico:default

Flashing example for this keyboard:

    make sofle_pico:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset** (works after you have flashed once): Hold down the top far corner key while plugging in the keyboard (`~` left half, `-` right half). This will also clear the EEPROM.
- **Physical reset button**: Hold the `BOOT` button on the Pico and press the `RST` button on the Pico, release the the `RST` button before the `BOOT` button.
- **Keycode in layout**: In the default layout, the `Bootloader` keycode is above home row pinky on the right side's adjust layer.

Once you enter the bootloader, the keyboard will show up as a USB device on your computer, you could drag and drop a `.uf2` firmware file to flash it.
