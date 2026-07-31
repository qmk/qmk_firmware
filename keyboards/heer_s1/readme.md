# HEER S1

![HEER S1](https://www.heerelectronics.com/product/side.png)

A 4x4 RP2040 macropad with two EC11 rotary encoders and a 128x64 SH1106 OLED.

* Keyboard Maintainer: [Heer Electronics](https://github.com/heerelectronics)
* Hardware Supported: HEER S1 PCB (RP2040 QFN-56)
* Hardware Availability: https://www.heerelectronics.com

## Pinout

Taken from the PCB netlist, not guessed. RP2040 package pins (`U2.x`) are
translated to GPIO numbers per the QFN-56 pin table in the RP2040 datasheet.

| Net | Package pin | GPIO |
|-----|-------------|------|
| ROW0..ROW3 | U2.6 .. U2.9 | GP4, GP5, GP6, GP7 |
| ROW4 (scan-only, see below) | — | GP15 |
| COL0..COL3 | U2.11 .. U2.14 | GP8, GP9, GP10, GP11 |
| ENC1_CLK / ENC1_DT / ENC1_SW | U2.2 / U2.3 / U2.4 | GP0 / GP1 / GP2 |
| ENC2_CLK / ENC2_DT / ENC2_SW | U2.15 / U2.16 / U2.17 | GP12 / GP13 / GP14 |
| SDA / SCL (OLED, header H1) | U2.27 / U2.28 | GP16 / GP17 |

**Diode direction is `ROW2COL`.** The netlist runs `ROW -> switch -> D(anode,
pin 2) -> D(cathode, pin 1) -> COL`, so current flows row to col. Setting this
to `COL2ROW` makes every one of the 16 keys go dead while the encoders and OLED
keep working perfectly — the diodes block the scan current, so QMK sees nothing.

The two encoder push-switches are **not in the key matrix**. They short to GND
directly (`SW3.D` / `SW4.D`), so QMK's matrix scanner cannot see them; they are
polled in `matrix_scan_user()` in the keymap. C22/C23 debounce them in hardware.

### Row 4 is scan-only

The 16 physical keys fill a 4x4 matrix exactly. Row 4 (`GP15`) has **no switches
on it** — the pin is unconnected, and because `ROW2COL` reads rows as pull-up
inputs, it always scans inactive and can never produce a keypress.

It exists so the VIA definition has two spare matrix cells (`4,0` and `4,1`) to
anchor the encoders to. VIA identifies an encoder by a matrix position, and all
16 real cells are occupied. The encoder keycodes are stored in VIA's encoder-map
region rather than the keymap, so row 4 is never read back — it is an addressing
placeholder, not a claim about the hardware.

Make example for this keyboard (after setting up your build environment):

    make heer_s1:default

Flashing example for this keyboard:

    make heer_s1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (bottom row of the SYSTEM layer)
