# sdrakb00

![sdrakb00](https://i.imgur.com/0HfpFqW.jpeg)

11 keys hot-swap macropad with rotary encoder.

Macropad features:
- 11 hot-swap keys
- Rotary encoder with push button
- AtMega32U4 MCU
- Per-key RGB led for backlighting
- USB-C connector
- On PCB SPI header
- MCU reset button
- Switch mounting plate
- Power LED indicator

* Keyboard Maintainer: [Diego Andres Rabaioli](https://github.com/drabaioli)
* Hardware Supported: Pro Micro Atmega32u4 based macropad with 11 keys, RGB LED chain and rotary encoder
* Hardware Availability: [Get the gerbers and have fun building it your self ;)](https://github.com/drabaioli/SdraKb00)

Build SdraKb00 firmware:

    make sdrakbs/sdrakb00:default

Flashing SdraKb00 firmware, execute:

    make sdrakbs/sdrakb00:default:flash

Then press the reset button on the back side of the PCB.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button** (preferred): Briefly press the button on the back of the PCB
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard

## Default Keymap

### Base Layer (0)
- NumPad layout (1-9, 0)
- Encoder: Volume Up/Down
- Encoder Push: Mute
- Layer Switch: Hold (1,3) key for function layer

### Function Layer (1)
- NumPad operators (+, -, *, /)
- Enter, "=" and backspace keys
- Decimal point
