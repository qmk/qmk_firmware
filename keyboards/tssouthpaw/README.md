# TS Southpaw Keyboard

## Overview

The TS Southpaw is a custom mechanical keyboard with a unique southpaw numpad layout (numpad on the left side) optimized for both efficiency and comfort. Built with the QMK firmware on an RP2040 controller, it features full RGB matrix lighting, a rotary encoder for volume control, and specialized features like a work timer system.

## Features

- **RP2040 Controller** with 16MB of flash storage
- **Full RGB Matrix** with 104 individually addressable LEDs
- **Rotary Encoder** for volume control (4 steps per detent)
- **Customizable Work Timer** with visual notifications
- **Dynamic Macros** for recording and playing custom key sequences
- **Caps Word** functionality for typing in UPPERCASE
- **Comprehensive RGB Effects** including reactive typing and heatmap

### Keyboard Layout Diagram

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│Esc│Del│Num│Mic│   │   │   │Mut│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│Lck│
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│Bsp│ / │ * │ - │Rc1│Rc2│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │   │Bsp│
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│ 7 │ 8 │ 9 │   │Cal│PtS│   │Tab│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│ 4 │ 5 │ 6 │ + │Pl1│Pl2│   │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   │Ent│
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│ 1 │ 2 │ 3 │   │   │ ↑ │   │Sft│   │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Sft│   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │ 0 │ . │Ent│ ← │ ↓ │ → │   │Ctl│Alt│   │   │   │Spc│   │   │Alt│   │Win│Fn │Ctl│
└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
```

### FN Layout Diagram

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │V- │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │8hr│10h│   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│4hr│   │   │V+ │   │   │   │CWd│   │Tmr│   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│1hr│   │30m│   │   │H+ │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │RM-│H- │RM+│   │   │   │   │   │   │P/R│   │   │   │   │   │   │   │
└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
```

## Work Timer System

The TS Southpaw includes a sophisticated work timer system that helps manage work/break cycles and promotes productive habits.

### Work Timer Types

The keyboard supports multiple timer durations with customized behavior:

| Timer | Duration | Mid-Point | End Warning | 
|-------|----------|-----------|-------------|
| 30MIN | 30 minutes | 30-second blue pulse at 15 minutes | 5-minute red pulse before end |
| 1HR | 1 hour | 45-second blue pulse at 30 minutes | 5-minute red pulse before end |
| 4HR | 4 hours | 60-second blue pulse at 2 hours | 5-minute red pulse before end |
| 8HR | 8 hours | 1-hour lunch break at 4 hours with blue indicator | 5-minute red pulse before end |
| 10HR | 10 hours | 1-hour lunch break at 5 hours with blue indicator | 5-minute red pulse before end |

### Visual Feedback

The work timer provides visual feedback through the function row LEDs (F1-F12):
- Green-to-yellow-to-orange-to-red gradient shows overall progress
- Blue pulses indicate breaks or lunch periods
- Red pulses warn when a timer is about to end

### Wake-on-Pulse Feature

The keyboard will automatically wake from sleep mode when important timer notifications are active, ensuring you don't miss break reminders or end-of-timer warnings even when the keyboard's RGB lighting is normally turned off due to inactivity. This feature works by checking if any timer pulse is active before entering full power-down mode, and keeps the RGB system partially active to display notifications.

### Work Timer Controls

The following keycodes control the work timer system:

| Keycode | Function | Location on FN Layer |
|---------|----------|----------------------|
| KC_WRKTMR | Start default 8-hour timer | S key |
| KC_30MIN | Start 30-minute timer | Numpad 3 |
| KC_1HR | Start 1-hour timer | Numpad 1 |
| KC_4HR | Start 4-hour timer | Numpad 4 |
| KC_8HR | Start 8-hour timer | Numpad 8 |
| KC_10HR | Start 10-hour timer | Numpad 9 |
| KC_WRKPAU | Pause/resume current timer | Space Bar key |

### Timer State Persistence

The work timer state is saved to EEPROM, allowing it to persist across power cycles. When the keyboard powers back on, it will restore the active timer and adjust the elapsed time accordingly.

## RGB Effects & Indicators

The TS Southpaw includes several special RGB effects:

- **ESC Ripple Effect**: Visual ripple emanating from the ESC key when pressed
- **Arrow Key Highlighting**: Blue highlighting for arrow keys
- **Caps Lock Indicator**: Orange pulse when Caps Lock is active
- **Num Lock Indicator**: Orange pulse when Num Lock is OFF
- **Microphone Mute**: Red pulse when microphone is muted
- **Work Timer Indicators**: Color gradient on function row to show progress
- **Typing Heatmap**: Dynamic color effect showing recently pressed keys
- **RGB Matrix Effects**: Multiple built-in QMK RGB effects including:
  - Solid Color
  - Breathing
  - Gradient
  - Rainbow modes
  - Reactive typing
  - Digital rain
  - Raindrop effects

## Rotary Encoder

The keyboard features a rotary encoder with 4 steps per detent for precise control:

- **Default Function**: Volume control (clockwise for volume up, counter-clockwise for volume down)
- **Position**: Located near the arrow keys for easy access
- **Implementation**: Uses hardware interrupts for reliable operation

## Layers

The keyboard has three main layers:

1. **Base Layer**: Standard QWERTY layout with numpad
2. **Function Layer (FN)**: Accessed by holding the key to the left of right Control
   - Contains RGB controls, work timer controls, and special functions

## Dynamic Macros

Record dynamic macros using:
- DM_REC1, DM_REC2: Start recording to slot 1 or 2
- DM_RSTP: Stop recording
- DM_PLY1, DM_PLY2: Play back macro in slot 1 or 2

## Getting Started

1. Clone the QMK firmware repository
2. Navigate to `keyboards/tssouthpaw`
3. Compile with `qmk compile -kb tssouthpaw -km default`
4. Flash using QMK Toolbox or command line

## RGB Matrix Control

Use RGB keycodes on the FN layer:
- RM+, RGB_MOD: next RGB mode
- RM-, RGB_RMOD: previous RGB mode
- V+,  RGB_VAI: RGB value up (brightness ↑)
- V-,  RGB_VAD: RGB value down (brightness ↓)
- H+,  RGB_HUI: RGB hue up
- H-,  RGB_HUD: RGB hue down

## Technical Specifications

- **MCU**: RP2040 (Raspberry Pi)
- **USB**: Type-C connector
- **RGB**: WS2812B LEDs (104 individually addressable)
- **Matrix**: 6×21 (126 keys)
- **Rotary Encoder**: Resolution 4 steps per detent
- **Memory**: 16MB flash storage

## Troubleshooting

### Common Issues

- **RGB Not Working**: Check if RGB matrix is enabled in your QMK build
- **Timer Not Persisting**: Ensure EEPROM is properly initialized
- **Rotary Encoder Issues**: Verify pin assignments in config.h

### Reset Options

- **Bootloader Mode**: To enter bootloader mode, press the reset button while plugging in the keyboard
- **EEPROM Reset**: Hold ESC while plugging in the keyboard to reset all settings to default

## License

This keyboard firmware is released under the GPL v2 license.

## Credits

Created by TS Design Works LLC  
Work Timer inspiration from https://unnecessaryinventions.com/ = https://youtu.be/UTSBCMNLqcw?si=LyVwGeiBSx44G1sk