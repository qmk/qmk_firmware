# 🎹 NineKey - RP2040 Macro Pad

A compact 3x3 ortholinear macro keyboard powered by the Raspberry Pi RP2040 microcontroller.

---

## 📋 Quick Start

### Basic Setup
- **Keyboard Layout**: 3x3 ortholinear grid
- **Microcontroller**: Raspberry Pi RP2040
- **Flash Method**: UF2 bootloader (drag & drop)

### How to Trigger a Keypress
Short together pins **`GP4`** and **`GP5`** to simulate a connection (useful for testing).

### Flashing Firmware
1. Double-tap the reset button to enter bootloader mode
2. Your device will appear as a USB mass storage device
3. Drag and drop the compiled `.uf2` file onto the device
4. Wait for the file to transfer and the keyboard will reset automatically

---

## 🎯 Default Keymap

```
┌─────────────┬──────────┬─────────────┐
│   PrtScn    │   CSM    │     CSH     │
├─────────────┼──────────┼─────────────┤
│  PREV_TRK   │  TD_01   │  NEXT_TRK   │
├─────────────┼──────────┼─────────────┤
│  Vol Down   │  Vol Up  │    Mute     │
└─────────────┴──────────┴─────────────┘
```

### Key Functions

| Key | Tap | Hold (500ms) | Notes |
|-----|-----|--------------|-------|
| **PREV_TRK** | Previous Track | Rewind | Media control |
| **NEXT_TRK** | Next Track | Fast Forward | Media control |
| **TD_01** | Play/Pause | Stop (2x) | Tap dance; 5+ taps = Bootloader |
| **CSM** | Ctrl+Shift+M | — | Mute toggle in Microsoft Teams |
| **CSH** | Ctrl+Shift+H | — | Close call in Microsoft Teams |
| **Vol Down** | Volume Down | — | System volume control |
| **Vol Up** | Volume Up | — | System volume control |
| **Mute** | Audio Mute | — | System mute |

### Special Combos

| Combo | Action |
|-------|--------|
| **Vol Down + Mute** (held) | Enter Bootloader |

---

## 🔧 Hardware

This keyboard is built for the **RP2040 Zero Mini** microcontroller board.

---

## 🛠️ Building & Flashing

### Compile the Firmware

To build the keyboard firmware, use the following command:

```bash
qmk compile -kb handwired/ninekey/rp2040 -km default
```

This generates a `.uf2` file ready to deploy on your device.

### Customizing Keymaps

To customize keymaps or features:

1. Edit `keymaps/default/keymap.c`
2. Modify key assignments in the `keymaps[]` array
3. Rebuild using the compile command above
4. Flash the generated `.uf2` file to your device

---

## 📚 Resources

- [QMK Firmware Documentation](https://docs.qmk.fm/)
- [RP2040 Support in QMK](https://docs.qmk.fm/hardware_drivers/drivers_mcu)
- [Keycode Reference](https://docs.qmk.fm/keycodes)

---

## 💡 Tips

- **Tap Dance**: The center key uses tap dance for media control with multiple behaviors
- **Hold Detection**: PREV/NEXT tracks support 500ms hold detection for rewinding/fast-forwarding
- **Teams Integration**: CSM and CSH keys are optimized for Microsoft Teams workflows
- **Debugging**: Use GPIO pins GP4/GP5 to test keyboard detection without physical switches
