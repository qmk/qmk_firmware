# ADB-to-USB Keyboard Converter (RP2040)

This is an RP2040 port of the ADB-to-USB keyboard converter, specifically designed for the **RP2040-Zero** board.

## Overview

This firmware converts Apple Desktop Bus (ADB) keyboard protocol to USB, allowing you to use vintage ADB keyboards (like the Apple Extended Keyboard, Apple Standard Keyboard, etc.) on modern computers using an RP2040 microcontroller.

## Hardware Requirements

- **RP2040-Zero** (or compatible RP2040 board)
- ADB keyboard
- **1K-10K pull-up resistor** (required!)
- Optional: Bidirectional level shifter (recommended for long-term reliability)

## Pin Configuration

| Signal | RP2040 Pin | Notes |
|--------|------------|-------|
| ADB Data | GP15 | Directly connected via pull-up resistor |
| VCC | 5V | Powers the ADB keyboard |
| GND | GND | Common ground |

## Wiring

### Basic Wiring (with pull-up to 3.3V)

```
ADB Keyboard          RP2040-Zero
┌────────┐            ┌──────────┐
│  VCC   │────────────│ 5V       │
│  GND   │────────────│ GND      │
│  DATA  │──[1kΩ]─┬───│ GP15     │
│        │        │   │          │
│        │       [R]  │          │
│        │        │   │          │
│        │        └───│ 3.3V     │
└────────┘            └──────────┘

R = 1K-10K pull-up resistor (REQUIRED!)
```

### ADB Socket Pinout

ADB female socket from the front:

```
      ,--_--.
     / o4 3o \      1: DATA
    | o2   1o |     2: Power SW (unused)
     -  ===  -      3: VCC (5V)
      `-___-'       4: GND
```

## Important Notes

### Voltage Tolerance Warning

⚠️ **The RP2040's GPIO pins are NOT 5V tolerant!**

The ADB protocol uses 5V logic levels, but the RP2040 can only handle 3.3V on its GPIO pins. The wiring configuration above works because:

1. **ADB uses open-drain signaling** - devices only pull the line LOW, never drive it HIGH
2. **The pull-up resistor is connected to 3.3V** - when the line is released, it only goes to 3.3V (safe for RP2040)
3. **The RP2040 can safely pull the line LOW** - the ADB keyboard will still see this as a valid low signal

### Recommended: Level Shifter

For maximum safety and long-term reliability, consider using a **bidirectional level shifter**:

```
ADB Keyboard          Level Shifter     RP2040-Zero
┌────────┐            ┌──────────┐      ┌──────────┐
│  VCC   │────────────│ HV (5V)  │──────│ 5V       │
│  GND   │────────────│ GND      │──────│ GND      │
│  DATA  │────────────│ HV1   LV1│──────│ GP15     │
│        │            │ LV (3.3V)│──────│ 3.3V     │
└────────┘            └──────────┘      └──────────┘
```

### Pull-up Resistor

A pull-up resistor is **required** for reliable operation. The RP2040's internal pull-up may be too weak, especially with long or coiled cables. A 1K-10K external pull-up resistor is strongly recommended.

## Building the Firmware

```bash
qmk compile -kb converter/adb_usb/rp2040 -km default
```

## Flashing

1. Hold the BOOT button on your RP2040-Zero while connecting USB (or double-tap reset if configured)
2. The RP2040 will appear as a USB mass storage device
3. Copy the `.uf2` file to the device
4. The device will automatically reboot with the new firmware

Alternatively, use QMK Toolbox or:

```bash
qmk flash -kb converter/adb_usb/rp2040 -km default
```

## Supported Keyboards

This converter should work with most ADB keyboards, including:

- Apple Standard Keyboard (M0116)
- Apple Extended Keyboard (M0115)
- Apple Extended Keyboard II (M3501)
- Apple Adjustable Keyboard (M1242)
- And many third-party ADB keyboards

## Features

- Full keyboard support with all standard keys
- LED support (Num Lock, Caps Lock, Scroll Lock)
- Locking Caps Lock support for vintage keyboards with mechanical locking switches
- ISO keyboard layout support

## Troubleshooting

1. **Keyboard not responding**: Check wiring and ensure pull-up resistor is connected
2. **Intermittent issues**: Try a lower value pull-up resistor (1K instead of 10K)
3. **Can't enter bootloader**: Double-tap the reset button quickly (within 200ms)

## Resources

- [QMK Firmware Documentation](https://docs.qmk.fm/)
- [RP2040 Platform Documentation](https://docs.qmk.fm/platformdev_rp2040)
- [Original ADB Protocol Documentation](http://developer.apple.com/legacy/mac/library/#technotes/hw/hw_01.html)

