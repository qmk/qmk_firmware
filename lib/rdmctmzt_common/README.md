# rdmctmzt_common Library Documentation

A shared library for QMK firmware providing three-mode wireless keyboard functionality (USB, Bluetooth, 2.4GHz) for keyboards using the ES32/FS026 MCU (Cortex M0).

## Table of Contents

- [Overview](#overview)
- [Supported Keyboards](#supported-keyboards)
- [Features](#features)
- [Configuration Options](#configuration-options)
- [LED Indicators](#led-indicators)
- [Battery Management](#battery-management)
- [Connection Modes](#connection-modes)
- [Custom Keycodes](#custom-keycodes)
- [Logo LED Feature](#logo-led-feature)
- [Integration Guide](#integration-guide)

---

## Overview

This library provides a unified codebase for three-mode wireless keyboards, handling:

- **USB wired mode** - Full USB HID support with NKRO
- **Bluetooth mode** - 3 independent BLE channels for pairing with different devices
- **2.4GHz wireless mode** - Low-latency wireless via dedicated dongle

The library manages power states, battery monitoring, LED indicators, mode switching, and communication with the wireless SPI module.

---

## Supported Keyboards

| Keyboard  | Manufacturer | Features             |
| --------- | ------------ | -------------------- |
| Luma40    | Epomaker     | 40% layout ortho     |
| TH40      | Epomaker     | 40% layout           |
| EVO80     | Evoworks     | 80% layout, Logo LED |
| Geonix r2 | Chosfox      | 40% layout ortho     |
| Galaxy 68 | Epomaker     | 65% layout           |

---

## Features

### Core Features

- Three-mode connectivity (USB/BLE/2.4G)
- Hardware mode switch detection
- Battery level monitoring and display
- Sleep mode for power saving
- EEPROM settings persistence
- VIA compatibility

### LED Features

- RGB Matrix support with custom driver
- Per-key lighting effects
- Status indicators (Caps Lock, Win Lock, Battery)
- Mode indicators (connection type display)
- Optional Logo LED with independent effects

---

## Configuration Options

Define these in your keyboard's `config.h` to customize behavior:

### Feature Toggles

| Define                            | Default   | Description                                               |
| --------------------------------- | --------- | --------------------------------------------------------- |
| `USB_AUTO_SWITCH_ENABLE`          | `1` (on)  | Automatically switch to USB mode when cable is plugged in |
| `LED_CONNECTION_INDICATOR_ENABLE` | `0` (off) | Always show connection type on `LED_CONNECTION_INDEX`     |
| `LOGO_LED_ENABLE`                 | `0` (off) | Enable Logo LED feature with independent effects          |

### Required LED Index Definitions

Each keyboard **must** define these LED indices in `config.h`:

```c
// Status indicator LEDs
#define LED_CONNECTION_INDEX  0   // Connection type indicator
#define LED_CAP_INDEX        52   // Caps Lock indicator
#define LED_WIN_L_INDEX      81   // Win Lock indicator
#define LED_BATT_INDEX       86   // Battery status indicator

// Mode indicator LEDs (shown when switching modes)
#define LED_BLE_1_INDEX      18   // Bluetooth channel 1 key
#define LED_BLE_2_INDEX      19   // Bluetooth channel 2 key
#define LED_BLE_3_INDEX      20   // Bluetooth channel 3 key
#define LED_2P4G_INDEX       21   // 2.4GHz mode key
#define LED_USB_INDEX        17   // USB mode key
```

### Battery Display Configuration

| Define                  | Default | Description                                      |
| ----------------------- | ------- | ------------------------------------------------ |
| `BATTERY_LED_COUNT`     | `12`    | Number of LEDs used for battery level display    |
| `BATTERY_LOW_THRESHOLD` | `20`    | Battery percentage for low (red) warning         |
| `BATTERY_MED_THRESHOLD` | `50`    | Battery percentage threshold for medium (yellow) |

### Logo LED Configuration (when `LOGO_LED_ENABLE = 1`)

| Define           | Default | Description                   |
| ---------------- | ------- | ----------------------------- |
| `LED_LOGO_INDEX` | `0`     | First LED index for Logo LEDs |
| `LOGO_LED_COUNT` | `1`     | Number of Logo LEDs           |

---

## LED Indicators

### Status Indicators

| LED                              | Color | Meaning               |
| -------------------------------- | ----- | --------------------- |
| **Caps Lock** (`LED_CAP_INDEX`)  | White | Caps Lock is active   |
| **Win Lock** (`LED_WIN_L_INDEX`) | White | Windows key is locked |

### Connection Indicator (when `LED_CONNECTION_INDICATOR_ENABLE = 1`)

The `LED_CONNECTION_INDEX` LED shows current connection type:

| Color   | Connection Mode         |
| ------- | ----------------------- |
| 🔵 Blue  | Bluetooth (any channel) |
| 🟢 Green | 2.4GHz wireless         |
| ⚪ White | USB wired               |

### Battery Level Display

When battery level is checked (hold `QK_BAT` key):

| Battery Level | LED Color | LEDs Lit          |
| ------------- | --------- | ----------------- |
| ≤ 20%         | 🔴 Red     | Proportional to % |
| 21-50%        | 🟡 Yellow  | Proportional to % |
| > 50%         | 🟢 Green   | Proportional to % |

**Special states:**

- **Charging**: Green wave animation across battery LEDs
- **Fully charged**: All battery LEDs solid green
- **Critical low**: `LED_BATT_INDEX` blinks red, all other LEDs off

### Mode Switch Indicators

When switching connection modes, the corresponding key LED lights up for 1 second:

| Mode          | LED               | Color   |
| ------------- | ----------------- | ------- |
| Bluetooth Ch1 | `LED_BLE_1_INDEX` | 🔵 Blue  |
| Bluetooth Ch2 | `LED_BLE_2_INDEX` | 🔵 Blue  |
| Bluetooth Ch3 | `LED_BLE_3_INDEX` | 🔵 Blue  |
| 2.4GHz        | `LED_2P4G_INDEX`  | 🟢 Green |
| USB           | `LED_USB_INDEX`   | ⚪ White |

### Pairing/Reconnection Indicators

| Status           | LED Behavior                           |
| ---------------- | -------------------------------------- |
| **Pairing**      | Fast blink (10 ticks on, 10 ticks off) |
| **Reconnecting** | Slow blink (25 ticks on, 25 ticks off) |
| **Connected**    | Solid for ~2.4 seconds, then off       |

---

## Battery Management

### Battery Thresholds

The battery system uses ADC readings to determine battery percentage:

| ADC Value | Voltage  | Status              |
| --------- | -------- | ------------------- |
| > 2555    | ~4.2V    | Full                |
| 2065-2555 | 3.4-4.2V | Normal              |
| 1865-2065 | 3.1-3.4V | Low                 |
| < 1865    | < 3.1V   | Critical (shutdown) |

### Charging Detection

The library monitors the `ES_BATT_STDBY_IO` pin for charging status:

| `es_stdby_pin_state` | Status                    |
| -------------------- | ------------------------- |
| `0`                  | Not charging              |
| `1`                  | Charging (wave animation) |
| `2`                  | Fully charged             |

### Power Saving

- Sleep mode activates after inactivity
- RGB LEDs turn off during sleep
- Wireless module enters low-power state

---

## Connection Modes

### Mode Switch Hardware

The library supports a physical 3-position mode switch:

| Switch Position | GPIO States        | Mode               |
| --------------- | ------------------ | ------------------ |
| USB             | Both HIGH          | `MODE_SWITCH_USB`  |
| 2.4G            | `MODE_2P4G_IO` LOW | `MODE_SWITCH_2P4G` |
| BT              | `MODE_BLE_IO` LOW  | `MODE_SWITCH_BT`   |

### USB Auto-Switch Feature

When `USB_AUTO_SWITCH_ENABLE = 1` (default):

- Keyboard automatically switches to USB mode when cable is connected
- Works regardless of physical switch position
- Previous wireless mode is restored when cable is unplugged

To disable, add to `config.h`:

```c
#define USB_AUTO_SWITCH_ENABLE 0
```

### Bluetooth Channels

Three independent Bluetooth channels allow pairing with different devices:

- **Channel 1**: First paired device
- **Channel 2**: Second paired device
- **Channel 3**: Third paired device

Each channel maintains its own pairing information.

---

## Custom Keycodes

### Mode Switching

| Keycode            | Short     | Description                   |
| ------------------ | --------- | ----------------------------- |
| `QMK_KB_MODE_USB`  | `MD_USB`  | Switch to USB mode            |
| `QMK_KB_MODE_2P4G` | `MD_24G`  | Switch to 2.4GHz mode         |
| `QMK_KB_MODE_BLE1` | `MD_BLE1` | Switch to Bluetooth channel 1 |
| `QMK_KB_MODE_BLE2` | `MD_BLE2` | Switch to Bluetooth channel 2 |
| `QMK_KB_MODE_BLE3` | `MD_BLE3` | Switch to Bluetooth channel 3 |

### Status & Settings

| Keycode            | Short     | Description                |
| ------------------ | --------- | -------------------------- |
| `QMK_BATT_NUM`     | `QK_BAT`  | Hold to show battery level |
| `QMK_WIN_LOCK`     | `QK_WLO`  | Toggle Windows key lock    |
| `QMK_KB_SIX_N_CH`  | `SIX_N`   | Toggle 6KRO/NKRO           |
| `QMK_MAC_WIN_CH`   | `MW_CH`   | Toggle Mac/Windows mode    |
| `QMK_TEST_COLOUR`  | `TEST_CL` | Enter LED test mode        |
| `QMK_DEBUG_SWITCH` | `DBG_SW`  | Debug mode switch position |

### LED Test Mode

Press `TEST_CL` to enter LED test mode. Then:

- Press `Space` to cycle through colors: Red → Green → Blue → White
- Press any other key to exit test mode

---

## Logo LED Feature

### Enabling Logo LED

Add to your keyboard's `config.h`:

```c
#define LOGO_LED_ENABLE 1
#define LED_LOGO_INDEX 91   // First Logo LED index
#define LOGO_LED_COUNT 5    // Number of Logo LEDs
```

### Logo LED Keycodes

| Keycode     | Short     | Description               |
| ----------- | --------- | ------------------------- |
| `LOGO_TOG`  | `LG_TOG`  | Toggle Logo LED on/off    |
| `LOGO_MOD`  | `LG_MOD`  | Cycle effect mode forward |
| `LOGO_RMOD` | `LG_RMOD` | Cycle effect mode reverse |
| `LOGO_HUI`  | `LG_HUI`  | Increase hue              |
| `LOGO_HUD`  | `LG_HUD`  | Decrease hue              |
| `LOGO_SAI`  | `LG_SAI`  | Increase saturation       |
| `LOGO_SAD`  | `LG_SAD`  | Decrease saturation       |
| `LOGO_VAI`  | `LG_VAI`  | Increase brightness       |
| `LOGO_VAD`  | `LG_VAD`  | Decrease brightness       |
| `LOGO_SPI`  | `LG_SPI`  | Increase effect speed     |
| `LOGO_SPD`  | `LG_SPD`  | Decrease effect speed     |

### Logo LED Effect Modes

| Mode                    | Value | Description                |
| ----------------------- | ----- | -------------------------- |
| `LOGO_MODE_NONE`        | 0     | Off                        |
| `LOGO_MODE_WAVE`        | 1     | Wave animation (default)   |
| `LOGO_MODE_WAVE1`       | 2     | Wave variant 1             |
| `LOGO_MODE_WAVE2`       | 3     | Wave variant 2             |
| `LOGO_MODE_FIXED_WAVE`  | 4     | Fixed wave                 |
| `LOGO_MODE_WAVE_RGB`    | 5     | Wave with RGB cycling      |
| `LOGO_MODE_SPECTRUM`    | 6     | Spectrum/rainbow cycle     |
| `LOGO_MODE_BREATHE`     | 7     | Breathing effect           |
| `LOGO_MODE_BREATHE_RGB` | 8     | Breathing with RGB cycling |
| `LOGO_MODE_LIGHT`       | 9     | Solid color                |

### VIA Integration

Logo LED settings are available in VIA under the "Lighting" tab using channel 2 (rgblight channel).

---

## Integration Guide

### Adding to a New Keyboard

1. **Create keyboard files** with the following structure:

   ```sh
   keyboards/your_keyboard/
   ├── config.h        # LED indices and configuration
   ├── keyboard.json   # Keyboard definition
   ├── your_keyboard.c # Thin wrapper calling kb_* functions
   ├── rules.mk        # Include library source files
   └── keymaps/
   ```

2. **Define required LED indices** in `config.h`:

   ```c
   #define LED_CONNECTION_INDEX  0
   #define LED_CAP_INDEX        52
   #define LED_WIN_L_INDEX      81
   #define LED_BATT_INDEX       86
   #define LED_BLE_1_INDEX      18
   #define LED_BLE_2_INDEX      19
   #define LED_BLE_3_INDEX      20
   #define LED_2P4G_INDEX       21
   #define LED_USB_INDEX        17
   ```

3. **Include the library** in `rules.mk`:

   ```makefile
   SRC += lib/rdmctmzt_common/keyboard_common.c
   ```

4. **Implement keyboard file** with thin wrappers:

   ```c
   #include "keyboard_common.h"

   // Battery indicator LED indices
   const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {0, 1, 2, ...};

   // LED matrix configuration
   led_config_t g_led_config = { ... };

   // QMK callbacks - delegate to library
   bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
       return kb_rgb_matrix_indicators_common(led_min, led_max);
   }

   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
       return kb_process_record_common(keycode, record);
   }

   void board_init(void) {
       kb_board_init();
   }

   // ... other callback wrappers
   ```

### Library Files Overview

| File                  | Purpose                                  |
| --------------------- | ---------------------------------------- |
| `rdmctmzt_common.h/c` | Main library header and core functions   |
| `keyboard_common.h/c` | Shared keyboard callback implementations |
| `three_mode.h/c`      | USB/BLE/2.4G mode management             |
| `user_battery.h/c`    | Battery monitoring and ADC               |
| `user_eeprom.h/c`     | Settings persistence                     |
| `user_led_custom.h/c` | RGB Matrix driver for ES32               |
| `user_logo_led.h/c`   | Logo LED effects (optional)              |
| `user_spi.h/c`        | SPI communication with wireless module   |
| `user_system.h/c`     | System management and sleep              |
| `user_emi.h/c`        | EMI testing functions                    |

---

## Troubleshooting

### Common Issues

| Issue                   | Solution                                     |
| ----------------------- | -------------------------------------------- |
| LEDs not working        | Check `g_led_config` matches your PCB layout |
| Battery not showing     | Verify `Led_Batt_Index_Tab` array            |
| Mode switch not working | Check GPIO pin definitions match hardware    |
| Settings not saving     | Ensure EEPROM size is correctly configured   |

### Resetting to Defaults

Use the `EE_CLR` keycode (usually Fn+Backspace) to clear EEPROM and reset all settings to defaults.

---

## License

This library is licensed under the GNU General Public License v2 or later.

Copyright 2024-2025 Various Contributors (see individual file headers).
