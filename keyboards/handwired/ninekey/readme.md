# NineKey

NineKey is a compact handwired 3x3 macropad reference keyboard for QMK.
It is designed as a simple nine-switch ortholinear matrix that is easy to
wire, test, and customize.

In the default keymap, the top row is focused on desktop/meeting controls (`K00` screenshot, `K01` mute toggle via `Ctrl+Shift+M`, `K02` hang up via `Ctrl+Shift+H`), the middle row is media transport (`K10` previous track, `K11` tap-dance play/pause with extra taps for stop and bootloader, `K12` next track), and the bottom row is volume control (`K20` volume down, `K21` volume up, `K22` mute). This layout puts frequent call controls on top, playback in the center, and audio level controls on the bottom for quick muscle-memory access.

This folder contains shared keyboard logic plus board-specific targets
(currently an RP2040 implementation under `rp2040/`).

## Keyboard Overview

- Layout: 3x3 ortholinear (`LAYOUT_ortho_3x3`)
- Matrix size: 3 rows x 3 columns
- Diode direction: `COL2ROW`
- Primary use cases: macro pad, test rig, small media/control pad

The matrix positions are mapped left-to-right, top-to-bottom:

| Row/Col | 0   | 1   | 2   |
|---------|-----|-----|-----|
| 0       | K00 | K01 | K02 |
| 1       | K10 | K11 | K12 |
| 2       | K20 | K21 | K22 |


## RP2040 Target

The `rp2040` target is intended for RP2040-based boards such as Raspberry Pi
Pico, KB2040, and similar compatible controllers.

Default matrix pins:

- Columns: `GP3`, `GP2`, `GP1`
- Rows: `GP4`, `GP5`, `GP6`
- Backlight pin: `GP28`
- WS2812 data pin: `GP29`

For board-specific behavior and notes, see `rp2040/readme.md`.

## Build

qmk compile -kb handwired/ninekey/rp2040 -km default
