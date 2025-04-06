# Wireless / Bluetooth

## Bluetooth Known Supported Hardware

Currently Bluetooth support is limited to AVR based chips. For Bluetooth 2.1, QMK has support for RN-42 modules. For more recent BLE protocols, currently only the Adafruit Bluefruit SPI Friend is directly supported. BLE is needed to connect to iOS devices. Note iOS does not support mouse input.

|Board                                                           |Bluetooth Protocol  |Connection Type|rules.mk                         |Bluetooth Chip|
|----------------------------------------------------------------|--------------------|---------------|---------------------------------|--------------|
|Roving Networks RN-42 (Sparkfun Bluesmirf)                      |Bluetooth Classic   |UART           |`BLUETOOTH_DRIVER = rn42`        |RN-42         |
|[Bluefruit LE SPI Friend](https://www.adafruit.com/product/2633)|Bluetooth Low Energy|SPI            |`BLUETOOTH_DRIVER = bluefruit_le`|nRF51822      |

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

<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth Rules.mk Options

The currently supported Bluetooth chipsets do not support [N-Key Rollover (NKRO)](../reference_glossary#n-key-rollover-nkro), so `rules.mk` must contain `NKRO_ENABLE = no`.

Add the following to your `rules.mk`:

```make
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = bluefruit_le # or rn42
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
| `QK_BLUETOOTH_PROFILE_NEXT` | `BT_NEXT` | Move to the next Bluetooth profile **(not yet implemented)**                                  |
| `QK_BLUETOOTH_PROFILE_PREV` | `BT_PREV` | Move to the previous Bluetooth profile **(not yet implemented)**                              |
| `QK_BLUETOOTH_UNPAIR`       | `BT_UNPR` | Un-pair the current Bluetooth profile **(not yet implemented)**                               |
| `QK_BLUETOOTH_PROFILE1`     | `BT_PRF1` | Swap to Bluetooth profile #1 **(not yet implemented)**                                        |
| `QK_BLUETOOTH_PROFILE2`     | `BT_PRF2` | Swap to Bluetooth profile #2 **(not yet implemented)**                                        |
| `QK_BLUETOOTH_PROFILE3`     | `BT_PRF3` | Swap to Bluetooth profile #3 **(not yet implemented)**                                        |
| `QK_BLUETOOTH_PROFILE4`     | `BT_PRF4` | Swap to Bluetooth profile #4 **(not yet implemented)**                                        |
| `QK_BLUETOOTH_PROFILE5`     | `BT_PRF5` | Swap to Bluetooth profile #5 **(not yet implemented)**                                        |
