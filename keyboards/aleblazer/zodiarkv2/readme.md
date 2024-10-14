# Zodiark-V2 Keyboard

![Zodiark-V2 Split](https://i.imgur.com/49O8aowl.jpg)

A split keyboard with 5x7 including a thumbcluster, encoders on each side, per key RGB, and 2x I2C headers per side, supporiting 1.3"/.96" 128x64 OLEDs (the 1.3" is an SSH1106 OLED, refer to QMK documentation for limitations), .91" 128x32 OLEDs.

The V2 updates the platform with dedicated left and right PCBs, [an updated all-in-one Pro Micro footprint](https://github.com/Aleblazer/TheOneProMicro) to take advantage of the extra pins, a VIK connector and an optional dual axis encoder when using the generic 35 pin RP2040 Pro Micro, and 10 additional underglow LEDs. The V2 also supports normal AVR/RP2040 Pro Micros using original Zodiark Firmware.

* Keyboard Maintainer: [Aleblazer](https://github.com/Aleblazer/), [Discord Link](https://discord.gg/BCSbXwskVt)
* Hardware Supported: Generic 35 pin RP2040 Pro Micro
* Hardware Availability: [Split Logic Keyboards](https://www.splitlogic.xyz/shop/pcb-kit/p/zodiark-7fyc5)

Make example for this keyboard (after setting up your build environment):

    make aleblazer/zodiarkv2:default

Flashing example for this keyboard:

    make aleblazer/zodiarkv2:default:flash

Remove TRRS cable from halves, plug into one side, press reset button when asked. Repeat process on the other side.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **BOOT Button**: Hold down the BOOT button on the top of the PCB and plug in the keyboard 
* **Physical reset button**: Double tap the button RESET on the top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
