# System76 Launch Configurable Keyboard (launch_1)

![System76 Launch Configurable Keyboard](https://images.prismic.io/system76/b71307ac-dae6-4863-b7ca-804cd61c7ef8_launch_overhead.png?auto=compress,format&w=750)

The Launch Configurable Keyboard is engineered to be comfortable, fully customizable, and make your workflow more efficient.

- High-speed USB Hub
- Works on Linux, Windows and macOS
- 100% Open Source
- Made in Colorado

Additional Launch Keyboard resources:

- Keyboard Maintainer: [System76](https://github.com/system76)
- Hardware Supported: [System76 Launch GitHub Repository](https://github.com/system76/launch)
- Hardware Availability: [Shop System76](https://system76.com/accessories/launch)

## Building Firmware

To build the firmware using `make` (after setting up the build environment), e.g.:

```bash
make -r system76/launch_1:default
```

Equivalently, using the QMK CLI:

```bash
qmk compile -kb system76/launch_1 -km default
```

## Flashing Firmware (DFU)

To build and flash the firmware on the keyboard, e.g.:

```bash
make -r system76/launch_1:default:flash
```

Equivalently, using the QMK CLI:

```bash
qmk flash -kb system76/launch_1 -km default
```

## Flashing Firmware (ISP)

To flash the firmware (and/or bootloader) using ISP refer to the [_ISP Flashing Guide_](https://docs.qmk.fm/#/isp_flashing_guide).

> **Factory fuse values** => Low: `0x5E`, High: `0x99`, Extended: `0xF3`, Lock Bits: `0xFF`

## Environment Setup

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. If new to QMK, start with the [_Complete Newbs Guide_](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard.
- **Keycode in layout**: Press the key mapped to `QK_BOOT` in the second layer (Escape).
- **Electrical reset**: Briefly short AVR ISP's GND (6) and RST (5) pads on the back of the PCB.
