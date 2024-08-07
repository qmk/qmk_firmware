# Varys

![varys](https://i.imgur.com/XDd9HKF.jpeg)

Varys is a mechanical split keyboard with custom designed PCB's, embedded ATmega32U4 microcontroller, EC11 encoders, USB-C connectors(for both power and communication), Serial/I2C communication, 132x32 Oled and per-key RGB. Keyboard layout is based on the lily58 layout.

Due to limited firmware space, RGB features have been disabled.

* Keyboard Maintainer: [Vinay Komaravolu](https://github.com/VinayKomaravolu)
* Hardware Supported: Varys PCB (Atmega32u4)
* Hardware Availability: [Varys Keyboard](https://github.com/vinaykomaravolu/varys)


Make example for this keyboard (after setting up your build environment):

    make varys:default

Flashing example for this keyboard:

    make varys:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button beside the USB-C connector on the pcb near the oled screen - if you haven't installed one, short the pads instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Disconnect the first half, connect the second one and repeat the process.
