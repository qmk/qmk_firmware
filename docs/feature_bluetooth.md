# Bluetooth

## Bluetooth Known Supported Hardware

Currently Bluetooth support is limited to AVR based chips. For Bluetooth 2.1, QMK has support for RN-42 modules. For more recent BLE protocols, currently only the Adafruit Bluefruit SPI Friend is directly supported. BLE is needed to connect to iOS devices. Note iOS does not support mouse input.

|Board                                                           |Bluetooth Protocol  |Connection Type|rules.mk                        |Bluetooth Chip|
|----------------------------------------------------------------|--------------------|---------------|--------------------------------|--------------|
|Roving Networks RN-42 (Sparkfun Bluesmirf)                      |Bluetooth Classic   |UART           |`BLUETOOTH_DRIVER = RN42`       |RN-42         |
|[Bluefruit LE SPI Friend](https://www.adafruit.com/product/2633)|Bluetooth Low Energy|SPI            |`BLUETOOTH_DRIVER = AdafruitBLE`|nRF51822      |

Not Supported Yet but possible:
* [Bluefruit LE UART Friend](https://www.adafruit.com/product/2479). [Possible tmk implementation found in](https://github.com/tmk/tmk_keyboard/issues/514)
* HC-05 boards flashed with RN-42 firmware. They apparently both use the CSR BC417 Chip. Flashing it with RN-42 firmware gives it HID capability.
* Sparkfun Bluetooth Mate
* HM-13 based boards

### Adafruit BLE SPI Friend
Currently The only bluetooth chipset supported by QMK is the Adafruit Bluefruit SPI Friend. It's a Nordic nRF5182 based chip running Adafruit's custom firmware. Data is transmitted via Adafruit's SDEP over Hardware SPI. The [Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829) is supported as it's an AVR mcu connected via SPI to the Nordic BLE chip with Adafruit firmware. If Building a custom board with the SPI friend it would be easiest to just use the pin selection that the 32u4 feather uses but you can change the pins in the config.h options with the following defines:
* `#define ADAFRUIT_BLE_RST_PIN D4`
* `#define ADAFRUIT_BLE_CS_PIN  B4`
* `#define ADAFRUIT_BLE_IRQ_PIN E6`

A Bluefruit UART friend can be converted to an SPI friend, however this [requires](https://github.com/qmk/qmk_firmware/issues/2274) some reflashing and soldering directly to the MDBT40 chip.

<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth Rules.mk Options

The currently supported Bluetooth chipsets do not support [N-Key Rollover (NKRO)](reference_glossary.md#n-key-rollover-nkro), so `rules.mk` must contain `NKRO_ENABLE = no`.

Add the following to your `rules.mk`:

```make
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = AdafruitBLE # or RN42
```

## Bluetooth Keycodes

This is used when multiple keyboard outputs can be selected. Currently this only allows for switching between USB and Bluetooth on keyboards that support both.

|Name      |Description                                   |
|----------|----------------------------------------------|
|`OUT_AUTO`|Automatically switch between USB and Bluetooth|
|`OUT_USB` |USB only                                      |
|`OUT_BT`  |Bluetooth only                                |
