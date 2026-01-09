# Raw HID Menu - Keychron V1 Encoder Macro System

Custom QMK firmware keymap that enables host-controlled macro menu system using the rotary encoder and Raw HID communication.

## Features

- **Encoder Gesture Detection**: Clockwise, counterclockwise, press, release, long-press, double-tap
- **Raw HID Communication**: Bidirectional protocol for encoder events and LED control
- **VIA Compatible**: Keeps VIA enabled for basic key remapping
- **LED Feedback**: Host can control RGB patterns based on menu state
- **Firmware-Side Gestures**: Reliable gesture detection using MCU timers

## Build Instructions

### Prerequisites
- QMK Toolbox installed
- QMK CLI configured (`qmk setup`)
- Keychron V1 ANSI Encoder variant

### Compile Firmware

```bash
cd C:\CLIPALS\qmk_firmware
qmk compile -kb keychron/v1/ansi_encoder -km raw_hid_menu
```

Output: `keychron_v1_ansi_encoder_raw_hid_menu.bin`

### Flash Firmware

1. Put keyboard in bootloader mode:
   - Hold ESC while plugging in USB, OR
   - Press physical reset button on PCB
2. Open QMK Toolbox
3. Select the compiled `.bin` file
4. Click "Flash"
5. Wait for completion

## Raw HID Protocol

### Device → Host (Encoder Events)

**Packet Structure (32 bytes):**
```
[0x01][EventType][EncoderID][Value][TimestampLSB][TimestampMSB][...padding...]
```

| Byte | Field | Description |
|------|-------|-------------|
| 0 | Report Marker | Always `0x01` |
| 1 | Event Type | See table below |
| 2 | Encoder ID | Always `0` for main knob |
| 3 | Value | Event-specific payload (typically `1` for rotation) |
| 4-5 | Timestamp | 16-bit timer value (ms) |
| 6-31 | Padding | Zeros |

**Event Types:**
| Value | Name | Description |
|-------|------|-------------|
| 0x01 | CW | Clockwise rotation |
| 0x02 | CCW | Counter-clockwise rotation |
| 0x03 | PRESS | Button pressed (down) |
| 0x04 | RELEASE | Button released (up) |
| 0x05 | LONG | Long-press detected (>500ms) |
| 0x06 | DOUBLE | Double-tap detected (<300ms between presses) |

### Host → Device (LED Commands)

**Packet Structure (32 bytes):**
```
[0x02][SubCommand][Arg1][Arg2][Arg3][...padding...]
```

| Byte | Field | Description |
|------|-------|-------------|
| 0 | Command Marker | Always `0x02` |
| 1 | Sub-Command | See table below |
| 2-4 | Arguments | Command-specific data |
| 5-31 | Padding | Zeros |

**Sub-Commands:**
| Value | Name | Arguments | Description |
|-------|------|-----------|-------------|
| 0x10 | SET_MODE | `[ModeID][0][0]` | Set LED animation mode |
| 0x11 | SET_COLOR | `[R][G][B]` | Set RGB color (0-255 each) |

**LED Modes:**
| Value | Name | Description |
|-------|------|-------------|
| 0 | DEFAULT | Normal RGB matrix behavior |
| 1 | VOLUME | Volume control mode |
| 2 | MEDIA | Media control mode |
| 3 | VOICEMEETER | Voicemeeter mode |
| 4 | WINDOW_MGMT | Window management mode |
| 5 | APP_LAUNCH | Application launcher mode |

## Gesture Timing Configuration

Default timing values (can be modified in `keymap.c`):

```c
#define LONG_PRESS_MS 500    // Long-press threshold
#define DOUBLE_TAP_MS 300    // Double-tap window
```

## VIA Compatibility Notes

This keymap has **both VIA and Raw HID enabled**. To minimize conflicts:

1. **Protocol Differentiation**: Uses `0x01` and `0x02` markers to distinguish from VIA packets
2. **Selective Processing**: The `raw_hid_receive()` function checks packet markers before processing
3. **Flash Space**: LTO (Link Time Optimization) is enabled to fit everything in 128KB

### If VIA Conflicts Occur

If you experience issues with VIA intercepting Raw HID packets:

1. **Option A**: Disable VIA in `rules.mk`:
   ```makefile
   VIA_ENABLE = no
   ```

2. **Option B**: Define custom usage page in `config.h`:
   ```c
   #define RAW_USAGE_PAGE 0xFF61
   #define RAW_USAGE_ID 0x62
   ```

## LED Indicators

The firmware can control individual LEDs based on host commands:

- **LED 67**: Encoder knob area (primary indicator)
- **LEDs 7-9**: Media control keys (MPRV, MPLY, MNXT)
- Additional LEDs can be mapped in `rgb_matrix_indicators_user()`

## Python Host Software

See `python_host/` directory for:
- HID communication library
- Menu state machine
- Overlay UI
- Command execution backends

## Troubleshooting

### Firmware Won't Compile
- Ensure QMK is up to date: `qmk update`
- Check for syntax errors in `keymap.c`
- Try disabling some RGB effects in `config.h` if flash space is exceeded

### Encoder Not Responding
- Verify correct variant: `ansi_encoder` (not `ansi`)
- Check encoder is working in VIA first
- Ensure firmware was flashed successfully

### Raw HID Not Detected
- Check USB VID/PID in Python code matches keyboard
- Windows: May need to install HID drivers
- Verify `RAW_ENABLE = yes` in `rules.mk`

### VIA Conflicts
- Try disabling VIA (see VIA Compatibility Notes)
- Check Python code is filtering packets by marker byte
- Monitor QMK logs for debug output

## Development Roadmap

- [x] Phase A: Firmware with Raw HID + encoder gestures
- [ ] Phase B: Python HID reader with reconnection
- [ ] Phase C: Overlay UI with proper Windows flags
- [ ] Phase D: Menu state machine
- [ ] Phase E: Command execution (volume, Voicemeeter, media, window mgmt)
- [ ] Phase F: Polish and optimization

## License

GPL v2 or later (same as QMK)

## Credits

- Based on Keychron V1 default keymap
- QMK Firmware: https://qmk.fm
- Raw HID implementation guidance from QMK community
