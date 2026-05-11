# Wireless / Bluetooth

## Bluetooth Known Supported Hardware

Currently Bluetooth support is limited to AVR based chips. For Bluetooth 2.1, QMK has support for RN-42 modules. For more recent BLE protocols, currently only the Adafruit Bluefruit SPI Friend is directly supported. BLE is needed to connect to iOS devices. Note iOS does not support mouse input.

|Board                                                           |Bluetooth Protocol  |Connection Type|rules.mk                         |Bluetooth Chip|
|----------------------------------------------------------------|--------------------|---------------|---------------------------------|--------------|
|Roving Networks RN-42 (Sparkfun Bluesmirf)                      |Bluetooth Classic   |UART           |`BLUETOOTH_DRIVER = rn42`        |RN-42         |
|[Bluefruit LE SPI Friend](https://www.adafruit.com/product/2633)|Bluetooth Low Energy|SPI            |`BLUETOOTH_DRIVER = bluefruit_le`|nRF51822      |
|Freqchip FR8003A (FR800x family)                                |Bluetooth Low Energy|UART (framed)  |`BLUETOOTH_DRIVER = fr800x`      |FR8003A       |

Not Supported Yet but possible:
* [Bluefruit LE UART Friend](https://www.adafruit.com/product/2479). [Possible tmk implementation found in](https://github.com/tmk/tmk_keyboard/issues/514)
* HC-05 boards flashed with RN-42 firmware. They apparently both use the CSR BC417 Chip. Flashing it with RN-42 firmware gives it HID capability.
* Sparkfun Bluetooth Mate
* HM-13 based boards

### Adafruit BLE SPI Friend
Currently The only bluetooth chipset supported by QMK is the Adafruit Bluefruit SPI Friend. It's a Nordic nRF51822 based chip running Adafruit's custom firmware. Data is transmitted via Adafruit's SDEP over Hardware SPI. The [Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829) is supported as it's an AVR mcu connected via SPI to the Nordic BLE chip with Adafruit firmware. If Building a custom board with the SPI friend it would be easiest to just use the pin selection that the 32u4 feather uses but you can change the pins in the config.h options with the following defines:
* `#define BLUEFRUIT_LE_RST_PIN D4`
* `#define BLUEFRUIT_LE_CS_PIN  B4`
* `#define BLUEFRUIT_LE_IRQ_PIN E6`

A Bluefruit UART friend can be converted to an SPI friend, however this [requires](https://github.com/qmk/qmk_firmware/issues/2274) some reflashing and soldering directly to the MDBT40 chip.

### Freqchip FR800x

Freqchip FR8003A and other FR800x-family chips are self-contained BLE HID transmitters that speak a length-prefixed framed UART protocol to the host MCU. The driver supports up to three Bluetooth profiles (`BT_PRF1`..`BT_PRF3`), NKRO via the chip's 6KRO+overflow HID descriptor, and a battery-percentage query path. The same driver core can also be selected as a `WIRELESS_2P4GHZ_DRIVER`; see [2.4 GHz Wireless Driver](../drivers/wireless_2p4ghz#fr800x-driver).

```make
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = fr800x
```

`UART_FRAME` is pulled in automatically. Boards must call `fr800x_post_init()` from `keyboard_post_init_kb()`.

<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth Rules.mk Options

The `rn42` and `bluefruit_le` drivers do not support [N-Key Rollover (NKRO)](../reference_glossary#n-key-rollover-nkro); with either, `rules.mk` must contain `NKRO_ENABLE = no`. The `fr800x` driver supports NKRO.

Add the following to your `rules.mk`:

```make
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = bluefruit_le # or rn42, fr800x
```

## Bluetooth Keycodes

This is used when multiple keyboard outputs can be selected. Currently this only allows for switching between USB and Bluetooth on keyboards that support both.

| Key                         | Aliases   | Description                                                                                   |
|-----------------------------|-----------|-----------------------------------------------------------------------------------------------|
| `QK_OUTPUT_AUTO`            | `OU_AUTO` | Automatically switch to USB when plugged in, otherwise use wireless                           |
| `QK_OUTPUT_NEXT`            | `OU_NEXT` | Cycle forwards through USB, Bluetooth, and 2.4GHz (when available) **(not yet implemented)**  |
| `QK_OUTPUT_PREV`            | `OU_PREV` | Cycle backwards through USB, Bluetooth, and 2.4GHz (when available) **(not yet implemented)** |
| `QK_OUTPUT_NONE`            | `OU_NONE` | Disable all output **(not yet implemented)**                                                  |
| `QK_OUTPUT_USB`             | `OU_USB`  | Output to USB only                                                                            |
| `QK_OUTPUT_2P4GHZ`          | `OU_2P4G` | Output to 2.4GHz only **(not yet implemented)**                                               |
| `QK_OUTPUT_BLUETOOTH`       | `OU_BT`   | Output to Bluetooth only                                                                      |
| `QK_BLUETOOTH_PROFILE_NEXT` | `BT_NEXT` | Move to the next Bluetooth profile                                                            |
| `QK_BLUETOOTH_PROFILE_PREV` | `BT_PREV` | Move to the previous Bluetooth profile                                                        |
| `QK_BLUETOOTH_UNPAIR`       | `BT_UNPR` | Un-pair the current Bluetooth profile                                                         |
| `QK_BLUETOOTH_PROFILE1`     | `BT_PRF1` | Swap to Bluetooth profile #1                                                                  |
| `QK_BLUETOOTH_PROFILE2`     | `BT_PRF2` | Swap to Bluetooth profile #2                                                                  |
| `QK_BLUETOOTH_PROFILE3`     | `BT_PRF3` | Swap to Bluetooth profile #3                                                                  |
| `QK_BLUETOOTH_PROFILE4`     | `BT_PRF4` | Swap to Bluetooth profile #4                                                                  |
| `QK_BLUETOOTH_PROFILE5`     | `BT_PRF5` | Swap to Bluetooth profile #5                                                                  |
| `QK_2P4GHZ_UNPAIR`          | `WL_UNPR` | Drop the 2.4 GHz dongle's pairing                                                             |

## Bluetooth Profiles

A Bluetooth driver may store multiple profiles. It reports its supported profile count via `bluetooth_get_max_profile()`.

* `BT_PRF1`..`BT_PRF5` swap to Bluetooth and select the matching profile (`BT_PRF1` is profile 0).
* `BT_NEXT` / `BT_PREV` cycle through the profiles.
* `BT_UNPR` un-pairs the current profile.

The selected profile persists across reboots.

A driver that does not implement the multi-profile API behaves as single-profile: only `BT_PRF1` is honored; the other profile keycodes and `BT_UNPR` are no-ops. The `rn42` and `bluefruit_le` drivers are currently single-profile.

To add multi-profile support, override these from `drivers/bluetooth/bluetooth.h`:

|Function                                  |Purpose                                                  |
|------------------------------------------|---------------------------------------------------------|
|`uint8_t bluetooth_get_max_profile(void)` |Supported profile count (>=1)                            |
|`bool bluetooth_set_profile(uint8_t)`     |Swap to the given profile; `false` if out of range       |
|`uint8_t bluetooth_get_profile(void)`     |The current profile                                      |
|`void bluetooth_unpair(void)`             |Un-pair the current profile                              |
