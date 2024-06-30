# MacroPad 10 RP2040

A RP2040-powered Macropad with a 2x5 layout.

Make example for this board (after setting up your build environment):

```sh
qmk compile -kb handwired/set_st/rp2040 -km via
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Features

- Raspberry Pi RP2040 Zero or Plus.
- 2x10 Mechanical key switch sockets - accepts any Cherry MX-compatible switches. Individually tied to GPIO pins (not matrix wired)
- One NeoPixel RGB LED per switch, on north side.
- Rotary encoder, 20 detents per rotation, with push-switch on GPIO pin.
- 128x64 SH1306 Monochrome OLED i2c display.

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key just below the rotary encoder push-button on power-up.
* **Physical reset button**: Press twice the button on the side while the board is connected.
* **BOOT button** Hold down the rotary encoder push-button on power-up or reset.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
