# TS-Southpaw-Rev-1.6

![TS-Southpaw-Rev-1.6](https://imgur.com/a/pUxQAhL)

*A full-sized southpaw mechanical keyboard with RGB lighting and rotary encoder*

* Keyboard Maintainer: [TS Design Works LLC](https://github.com/tsdesignworks)
* Hardware Supported: TS-Southpaw-Rev-1.6 PCB
* Hardware Availability: [TS Design Works LLC](https://github.com/tsdesignworks)

## Features

- Full-sized southpaw layout (numpad on left side)
- 104 hot-swappable switch positions
- Per-key RGB lighting (104 LEDs)
- Rotary encoder with dual-mode functionality
- RP2040 microcontroller (USB-C connectivity)
- QMK firmware with dynamic macros
- Custom RGB indicators for keyboard state
- Visual ESC key ripple effect
- 8-hour work timer with progress bar

## Keyboard Layout

### Base Layer
Standard QWERTY layout with numpad on the left side. Function key for accessing additional layers.

### Function Layer (Fn)
RGB controls, keyboard configuration, and additional functions.

### Media Layer
Media control keys and alternative encoder mode.

## Firmware Building

Make example for this keyboard (after setting up your build environment):

```shell
qmk compile -kb tssouthpaw -km default
```

Flashing example for this keyboard:

```shell
qmk flash -kb tssouthpaw -km default
```

## Bootloader

Enter the bootloader in 1 of 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB
* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## RGB Lighting

Default startup color is green. Special indicators include:
- Caps Lock: Orange pulsing when active
- Num Lock: Orange pulsing when inactive
- Mic Mute: Red pulsing when active
- ESC key: Red ripple effect on press
- Arrow keys: Blue highlighting in solid color mode

## Work Timer

The keyboard features an 8-hour work timer with visual indicators:
- F1-F12 keys serve as a progress bar, showing elapsed work time
- Colors fade from green (start) through yellow (middle) to red (end)
- Blue flash at 4 hours for lunch break
- Blue warning flash 5 minutes before lunch break ends
- Red warning flash for the last 5 minutes of the workday

To use the work timer:
- Start/Stop: Press `Fn + DM_PLY1`
- Pause/Resume: Press `Fn + DM_PLY2`

The timer automatically shuts off after 8 hours have elapsed.

## Rotary Encoder

The rotary encoder has two modes:
- Default mode: Volume control (rotate for volume up/down)
- Media mode: Track control (rotate for next/previous track)

## Dynamic Macros

To record and play macros:
- Record: Press `Fn + DM_REC1` or `Fn + DM_REC2`, input sequence, press `Fn + DM_REC1/2` again
- Playback: Press `Fn + DM_PLY1` or `Fn + DM_PLY2`