# Rohde & Schwarze PCA-Z1 keyboard protocol converter

A converter for using Rohde & Schwarze PCA-Z1 keyboards.

Protocole documented by [Mihai Gaitos](https://hawk.ro/stories/rs_kbd/). Ported to QMK by [Kamel Makhloufi](https://github.com/melka).

Keyboard Maintainer: [Kamel Makhloufi](https://github.com/melka)  
Hardware Supported: See hardware section below  
Hardware Availability: self-built

Make example for this keyboard (after setting up your build environment):

    make converter/rs_pca-z1_usb:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.


## Hardware

Target MCU is ATMega32u4 but other USB capable AVR will also work. Tested on an Arduino ProMicro clone.
Supported keyboards: Rohde & Schwarze PCA-Z1

### Connector

6.35mm Mono Jack (TRS)
    
     _____
    |     |______ ___ ___
    |     |  1   | 2 | 3 \
    |     |______|___|___/
    |     |
    |_____|
      | |
      | |
    (plug)

Wiring:

    Pin TRS        MCU
    -------------------
    1   GND        GND
    2   Signal     PD0
    3   5V         VCC

### Protocol

Signal: Asynchronous, 2400baud, No Flow control
Frame format: 1-Start bit, 8-Data bits, No-Parity, 1-Stop bit
    
### Caveats

The MCU inside the keyboard doesn't send modifiers, only modified keys (ASCII code).
ie : "a" is 0x61, "shift+a" or "A" is 0x41
Some key combinations are therefore impossible.
See [protocol documentation](https://hawk.ro/stories/rs_kbd/) for more informations
