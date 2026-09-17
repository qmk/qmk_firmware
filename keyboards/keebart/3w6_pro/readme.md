# 3w6 Pro

The Keebart 3w6 Pro is a compact 36-key split keyboard with an integrated
RP2040 microcontroller on each half. The halves communicate over full-duplex
serial, and either half can act as the USB master.

- Maintainer: [Keebart](https://github.com/Keebart)
- Processor: RP2040
- Layout: Split 3x5+3
- Split transport: Full-duplex serial
- Lighting: 36-key RGB Matrix
- Hardware availability: [Keebart Shop](https://keebart.com/products/3w6)

## Building

Precompiled firmware files can be downloaded from the
[3w6 Pro product page](https://keebart.com/products/3w6).

Set up a [QMK build environment](https://docs.qmk.fm/newbs_getting_started)
and run the following command from the QMK firmware directory:

```sh
qmk compile -kb keebart/3w6_pro -km default
```

The resulting UF2 file is written to the QMK firmware directory.

## Flashing

Each half contains its own RP2040 and must be flashed separately. Build the
desired keymap once, enter the bootloader on one half, and copy the generated
UF2 file to the RP2040 mass-storage device. Repeat the process for the other
half using the same firmware.

The bootloader can be entered in any of these ways:

- **Bootmagic:** Hold the outer key of the top row while connecting that half
  to USB.
- **BOOT and RESET buttons:** Both buttons are accessible through the two small
  holes on the underside of the keyboard. Hold **BOOT**, briefly press and
  release **RESET**, then release **BOOT**.
- **Keycode:** Use a key mapped to `QK_BOOT`, when available in the active
  keymap.

## Split communication

The keyboard uses separate UART lines for transmit and receive:

- TX: `GP8`
- RX: `GP9`
- Hand detection: `GP21`

The connection between halves must cross the serial signals: TX on one half
connects to RX on the other half.

## RGB Matrix

The keyboard supports one per-key RGB LED for each of its 36 keys, divided
equally between the halves. RGB data uses `GP10`. The default effect is a
solid blue color (`#0284c7`) with a maximum brightness of 75.

Lighting settings are stored independently in each half's EEPROM. When using
either half as the USB master, configure or reset the lighting state on that
half as required.
