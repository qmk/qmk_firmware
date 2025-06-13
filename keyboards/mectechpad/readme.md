# MECTECHPAD

A 3x3 custom macropad designed by [Printronics](https://printronics.gr), powered by the RP2040 MCU, and fully compatible with VIA for real-time key remapping.

## Features

- **3x3 matrix** (9 keys)
- RP2040 microcontroller
- VIA support for easy key remapping
- 4 programmable layers, with hardware-based layer switching via dedicated button
- Layer indicator LEDs (one per layer)
- Designed for makers, productivity, and automation

## Matrix and Pinout

| Row Pins     | Col Pins     |
|--------------|--------------|
| GP26, GP15, GP14 | GP29, GP28, GP27 |

**Diode Direction:** ROW2COL

## Layer Switch & LEDs

- Dedicated layer change button: **GP13**
- Layer indicator LEDs: *specify your pins here* (e.g. GP2, GP3, GP4, GP5)

## How to Flash

1. Hold the **BOOTSEL** button and plug the board into USB.
2. Copy the generated `.uf2` firmware file to the new drive ("RPI-RP2").
3. The board will reboot automatically.

## VIA Support

- Use [VIA](https://usevia.app/) for live key remapping.
- If VIA doesn’t auto-detect, drag and drop `mectechpad_via.json` into VIA’s design tab.

## Maintainer

[jacksaxi](https://github.com/jacksaxi)

---