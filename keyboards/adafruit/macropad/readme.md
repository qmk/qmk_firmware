# Adafruit MacroPad RP2040

![AdafruitMacropad](https://i.imgur.com/dSBSwcJh.jpeg)

A RP2040-powered Macropad with a 3x4 layout.

- Keyboard Maintainer: [Jpe230](https://github.com/jpe230/) 
- Hardware Supported: Adafruit MacroPad RP2040
- Hardware Availability: [Barebones kit](https://www.adafruit.com/product/5100) [Starter Kit](https://www.adafruit.com/product/5128)

Make example for this board (after setting up your build environment):

```sh
qmk compile -kb adafruit/macropad -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Features

- Raspberry Pi RP2040 Chip + 8MB Flash memory - Dual-core Cortex M0+ at ~130MHz with 264KB of RAM.
- 3x4 Mechanical key switch sockets - accepts any Cherry MX-compatible switches. Individually tied to GPIO pins (not matrix wired)
- One NeoPixel RGB LED per switch, on north side.
- Rotary encoder, 20 detents per rotation, with push-switch on GPIO pin. Push switch is also used for entering bootloader mode when held down on power-up or reset.
- 128x64 SH1106 Monochrome OLED display - On high-speed hardware SPI port for quick updates.
- 8mm Speaker/Buzzer - With Class D amplifier and RC filter, can be used to make simple beeps and sounds effects. (Unsupported for now)
- STEMMA QT Connector - Allows adding any I2C sensors/displays/devices with plug-and-play cables.
- Reset button - On the side, for quick restarting, press it twice to enter bootloader.
- Four M3 mounting bosses - Make custom enclosures easily.

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key just bellow the rotary encoder push-button on power-up.
* **Physical reset button**: Press twice the button on the side while the board is connected.
* **BOOT button** Hold down the rotary encoder push-button on power-up or reset.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
