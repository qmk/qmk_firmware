# TS Southpaw Keyboard - Version 2.0

## Overview

The TS Southpaw is a custom mechanical keyboard with a unique southpaw numpad layout (numpad on the left side) optimized for both efficiency and comfort. Built with the QMK firmware on an RP2040 controller, it features full RGB matrix lighting, a rotary encoder for volume control, and customizable RGB effects.

## Version 2.0 Changes

Version 2.0 is a streamlined release focused on core RGB functionality:

- **Removed**: Work timer system (simplified for better performance)
- **Added**: FN+E toggle to enable/disable ESC ripple effect
- **Improved**: Cleaner codebase with no duplicate files
- **Enhanced**: More responsive RGB effects

## Features

- **RP2040 Controller** with 16MB of flash storage
- **Full RGB Matrix** with 104 individually addressable LEDs
- **Rotary Encoder** for volume control (4 steps per detent)
- **Dynamic Macros** for recording and playing custom key sequences
- **Caps Word** functionality for typing in UPPERCASE
- **Comprehensive RGB Effects** including reactive typing and heatmap
- **Customizable ESC Ripple Effect** with toggle control

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
│   │   │   │   │   │   │   │   │   │   │EsT│   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │V- │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │V+ │   │   │   │CWd│   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │H+ │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
│   │   │   │   │RM-│H- │RM+│   │   │   │   │   │   │   │   │   │   │   │   │   │   │
└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘

Legend:
  EsT = ESC Ripple Toggle
  CWd = Caps Word Toggle
  V+/V- = RGB Brightness Up/Down
  H+/H- = RGB Hue Up/Down
  RM+/RM- = RGB Mode Next/Previous
```

## RGB Effects & Indicators

The TS Southpaw includes several special RGB effects:

### Built-in Effects

- **ESC Ripple Effect**: Visual red ripple emanating from the ESC key when pressed
  - Toggle on/off with FN+E (enabled by default)
  - Expanding/contracting animation for visual feedback
- **Arrow Key Highlighting**: Blue highlighting for arrow keys in solid color mode
- **Caps Lock Indicator**: Orange pulse when Caps Lock is active
- **Num Lock Indicator**: Orange pulse when Num Lock is OFF
- **Microphone Mute**: Red pulse when microphone is muted (MS Teams compatible)

### QMK RGB Matrix Effects

The keyboard includes multiple built-in QMK RGB effects:
- Solid Color
- Breathing
- Gradient
- Rainbow modes
- Reactive typing
- Digital rain
- Raindrop effects
- Typing heatmap

## Special Functions

### Custom Keycodes

| Keycode | Function | Location |
|---------|----------|----------|
| KC_MICMUTE | Toggle microphone mute (Ctrl+Shift+M for MS Teams) | Top row |
| KC_ESC_TOG | Toggle ESC ripple effect on/off | FN + E |
| KC_CPSWRD | Toggle Caps Word mode | FN + Caps Lock |

### Rotary Encoder

The keyboard features a rotary encoder with 4 steps per detent for precise control:

- **Default Function**: Volume control (clockwise for volume up, counter-clockwise for volume down)
- **Position**: Located near the arrow keys for easy access
- **Implementation**: Uses hardware interrupts for reliable operation

## Layers

The keyboard has two main layers:

1. **Base Layer**: Standard QWERTY layout with southpaw numpad
2. **Function Layer (FN)**: Accessed by holding the key to the left of right Control
   - Contains RGB controls and special functions

## Dynamic Macros

Record dynamic macros using:
- **DM_REC1, DM_REC2**: Start recording to slot 1 or 2
- **DM_RSTP**: Stop recording
- **DM_PLY1, DM_PLY2**: Play back macro in slot 1 or 2

Macro recording locations on the base layer:
- Record slots: Upper left area (Rc1, Rc2)
- Playback slots: Middle left area (Pl1, Pl2)

## RGB Matrix Control

Use RGB keycodes on the FN layer:
- **RM+** (RGB_MOD): Next RGB mode
- **RM-** (RGB_RMOD): Previous RGB mode
- **V+** (RGB_VAI): RGB value up (brightness ↑)
- **V-** (RGB_VAD): RGB value down (brightness ↓)
- **H+** (RGB_HUI): RGB hue up
- **H-** (RGB_HUD): RGB hue down

## Getting Started

### Building the Firmware

1. Clone the QMK firmware repository
2. Navigate to `keyboards/tssouthpaw`
3. Compile with `qmk compile -kb tssouthpaw -km default`
4. Flash using QMK Toolbox or command line

### Flashing

- **Bootloader Mode**: Double-tap the reset button (GP25) within 500ms
- **Alternative**: Hold BOOTSEL button while plugging in the keyboard

## Technical Specifications

- **MCU**: RP2040 (Raspberry Pi)
- **Firmware Version**: 2.0.0
- **USB**: Type-C connector
- **RGB**: WS2812B LEDs (104 individually addressable)
- **Matrix**: 6×21 (126 keys)
- **Rotary Encoder**: Resolution 4 steps per detent
- **Memory**: 16MB flash storage
- **Debounce**: 5ms
- **RGB Timeout**: 10 minutes (600 seconds)
- **Max Brightness**: 250/255

## LED Mapping

Key indicator LEDs:
- **LED 62**: Caps Lock (orange pulse when active)
- **LED 2**: Num Lock (orange pulse when OFF)
- **LED 3**: Microphone Mute (red pulse when muted)
- **LEDs 78, 94, 95, 96**: Arrow keys (blue in solid color mode)

## Troubleshooting

### Common Issues

- **RGB Not Working**: Check if RGB matrix is enabled in your QMK build
- **Rotary Encoder Issues**: Verify pin assignments in keyboard.json (GP0, GP1)
- **ESC Ripple Not Working**: Check if it's enabled with FN+E toggle

### Reset Options

- **Bootloader Mode**: Double-tap reset button (500ms window)
- **EEPROM Reset**: Hold ESC while plugging in the keyboard to reset all settings to default

## Development Notes

### Code Organization

- **config.h**: Hardware configuration and LED indices
- **keyboard.json**: Layout and RGB matrix LED positions
- **rules.mk**: Build system configuration
- **tssouthpaw.c/h**: Keyboard initialization and power management
- **rgb_effects/**: RGB effects system
  - **rgb_effects.c/h**: All RGB effects implementation
- **keymaps/default/**: Default keymap configuration

### Customization

To customize RGB effects, modify:
- Color definitions in `rgb_effects/rgb_effects.c`
- Effect behavior in the respective handler functions
- Keymap in `keymaps/default/keymap.c`

## License

This keyboard firmware is released under the GPL v2 license.

## Credits

Created by TS Design Works LLC

---

**Version**: 2.0.0
**Last Updated**: December 2025
**Maintainer**: ts_design_works_llc
