# 3w6 Pro

![3w6_pro](TODO_IMAGE_URL)

The Keebart 3w6 Pro is a compact 36-key split keyboard with an integrated
RP2040 microcontroller on each half. The halves communicate over full-duplex
serial, and either half can act as the USB master.

- Keyboard Maintainer: [Keebart](https://github.com/Keebart)
- Hardware Supported: RP2040
- Hardware Availability: [Keebart Shop](https://keebart.com/products/3w6)

Make example for this keyboard (after setting up your build environment):

    make keebart/3w6_pro:default

Flashing example for this keyboard:

    make keebart/3w6_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for
more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

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
