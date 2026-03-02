# Mechanical Keyboards Point65

![Mechanical Keyboards Point65](https://i.imgur.com/lTEwGBR.png)
## Description
A 65% keyboard by [Mechanical Keyboards](https://mechanicalkeyboards.com) available as either multi layout hotswap, or hotswap with RGB per key backlight.

* Keyboard Maintainer: [C44Supra](https://github.com/C44Supra)
* Hardware Supported: MK Point65 hotswap, MK Point65 hotswap RGB
* Hardware Availability: [MK Point65 Keyboard Kit](https://mechanicalkeyboards.com/products/mk-point65-keyboard-kit)

## Firmware building
**Hotswap with 6.25U layout:**
    
    make mechanicalkeyboards/point65/hotswap:default

**Hotswap with 7U layout:**
    
    make mechanicalkeyboards/point65/hotswap:default_7u

**Hotswap RGB:**
    
    make mechanicalkeyboards/point65/hotswap_rgb:default

## Bootloader and Flashing:
The keyboard can be flashed with new firmware by entering the bootloader in one of the following ways:
- Bootmagic reset: unplug the keyboard, press and hold the top left key, plug the keyboard back in, and then release the top left key
- Physical reset button: Remove the space bar and double press the reset button twice in short succession

Once the keyboard enters bootloader mode, it will present itself as a removable device called `RPI-RP2`. Copy / drag the new firmware file to the `RPI-RP2` drive to flash the new firmware onto the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).