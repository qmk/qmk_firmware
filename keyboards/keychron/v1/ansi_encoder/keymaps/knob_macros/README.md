# Keychron V1 Knob Macros Keymap

This custom keymap implements rotary encoder macro cycling functionality for the Keychron V1 ANSI Encoder variant.

## Features

- **Rotary Encoder Macro Cycling**: Turn the knob to cycle through 8 different macros
- **Encoder Press to Execute**: Press the knob to execute the currently selected macro
- **VIA Support**: Full VIA compatibility for easy keymap customization
- **Pre-configured Macros**: 8 useful macros ready to use

## Available Macros

| Macro # | Function | Description |
|---------|----------|-------------|
| 0 | Type "Hello World" | Types the text "Hello World" |
| 1 | Copy | Executes Ctrl+C |
| 2 | Paste | Executes Ctrl+V |
| 3 | Cut | Executes Ctrl+X |
| 4 | Undo | Executes Ctrl+Z |
| 5 | Redo | Executes Ctrl+Y |
| 6 | Select All | Executes Ctrl+A |
| 7 | Save | Executes Ctrl+S |

## How It Works

1. **Rotate the knob clockwise** to cycle forward through macros (0→1→2→...→7→0)
2. **Rotate the knob counter-clockwise** to cycle backward through macros
3. **Press the knob** to execute the currently selected macro

## Customizing Macros

To customize the macros, edit `keymap.c` and modify the `process_record_user()` function. You can change the macro count by modifying `MACRO_COUNT` and adding/removing cases in the switch statement.

### Example: Adding a New Macro

```c
// Change MACRO_COUNT at the top of the file
#define MACRO_COUNT 9  // Increased from 8

// Add a new case in process_record_user()
case 8:
    // Macro 8: Open Task Manager (Ctrl+Shift+Esc)
    SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_ESC))));
    break;
```

### QMK String Macros Reference

- `SEND_STRING("text")` - Types text
- `SS_LCTRL("x")` - Ctrl + X
- `SS_LALT("x")` - Alt + X
- `SS_LSFT("x")` - Shift + X
- `SS_LGUI("x")` - Win/Cmd + X
- `SS_TAP(X_KEY)` - Tap a key (e.g., X_ESC, X_F4)
- `SS_DOWN(X_KEY)` - Hold key down
- `SS_UP(X_KEY)` - Release key

## Compiling the Firmware

### Prerequisites

You need to set up the QMK build environment. There are several options:

#### Option 1: MSYS2 (Windows)

1. Install [MSYS2](https://www.msys2.org/)
2. Open "MSYS2 MinGW 64-bit" terminal
3. Install QMK CLI:
   ```bash
   pip install qmk
   ```
4. Setup QMK:
   ```bash
   qmk setup
   ```

#### Option 2: WSL (Windows Subsystem for Linux)

1. Install WSL with Ubuntu
2. Install QMK:
   ```bash
   python3 -m pip install --user qmk
   qmk setup
   ```

#### Option 3: Docker

```bash
docker run --rm -v ${PWD}:/qmk_firmware ghcr.io/qmk/qmk_cli qmk compile -kb keychron/v1/ansi_encoder -km knob_macros
```

### Compile Command

Once your environment is set up, navigate to the qmk_firmware directory and run:

```bash
qmk compile -kb keychron/v1/ansi_encoder -km knob_macros
```

Or using make:

```bash
make keychron/v1/ansi_encoder:knob_macros
```

This will generate a `.bin` file in the `qmk_firmware` directory.

## Flashing the Firmware

### Using QMK Toolbox (Recommended for Windows)

1. Download [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
2. Open the compiled `.bin` file
3. Put your keyboard in bootloader mode:
   - Unplug the keyboard
   - Hold the `ESC` key
   - Plug in the keyboard while holding `ESC`
   - Release `ESC` after 2 seconds
4. Click "Flash" in QMK Toolbox

### Using QMK CLI

```bash
qmk flash -kb keychron/v1/ansi_encoder -km knob_macros
```

Then put the keyboard in bootloader mode when prompted.

## VIA Configuration

After flashing the firmware with VIA enabled:

1. Download [VIA](https://www.caniusevia.com/)
2. Open VIA and it should automatically detect your keyboard
3. You can now remap keys visually (note: macro cycling is hardcoded in firmware)

## File Structure

```
keyboards/keychron/v1/ansi_encoder/keymaps/knob_macros/
├── keymap.c    # Main keymap and macro logic
├── rules.mk    # Build configuration
└── README.md   # This file
```

## Troubleshooting

### Encoder Not Working
- Make sure you're using the `ansi_encoder` variant, not just `ansi`
- Verify `ENCODER_ENABLE = yes` is in `rules.mk`

### Macros Not Executing
- Check that the knob is mapped to `EXEC_MACRO` in the keymap
- Verify the macro index is within the `MACRO_COUNT` range

### Compilation Errors
- Ensure you have the latest QMK firmware
- Check that all files are in the correct directory
- Make sure your build environment is properly set up

## License

This keymap is based on the default Keychron V1 keymap and follows the same GPL-2.0-or-later license.

Copyright 2021 @ Keychron (https://www.keychron.com)
