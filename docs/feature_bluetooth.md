# Bluetooth

## Bluetooth Known Supported Hardware

Currently Bluetooth support is limited to AVR based chips. For Bluetooth 2.1 Qmk has support for RN-42 HID Firmware and Bluefruit EZ Key the later of which is not produced anymore. For more recent BLE protocols currently only the Adafruit Bluefruit SPI friend is directly supported. BLE is needed to connect to iOS devices. Note iOS does not support Mouse Input.

|Board                                                           |Bluetooth Protocol          |Connection Type |Rules.mk                   |
|----------------------------------------------------------------|----------------------------|----------------|---------------------------|
|[Adafruit EzKey HID]"https://www.adafruit.com/product/1535"     |Bluetooth Classic           | UART           | BLUETOOTH = AdafruitEZKey |
|Rover Networks RN-42 (Sparkfun Bluesmirf)                       |Bluetooth Classic           | UART           | BLUETOOTH = RN42          |
|[Bluefruit LE SPI Friend](https://www.adafruit.com/product/2633)|Bluetooth Low Energy        | SPI            | BLUETOOTH = AdafruitBLE   |

Not Supported Yet but possible:
* [Bluefruit LE UART Friend](https://www.adafruit.com/product/2479). [Possible tmk implementation found in](https://github.com/tmk/tmk_keyboard/issues/514)
* HC-05 boards flashed with RN42 firmware. (This gives it hid support)

### Adafruit BLE SPI Friend
Currently The only bluetooth chipset supported by QMK is the Adafruit Bluefruit SPI Friend. It's a Nordic nRF5182 based chip running Adafruit's custom firmware. Data is transmitted via Adafruit's SDEP over Hardware SPI. The [Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829) is supported as it's an AVR mcu connected via SPI to the Nordic BLE chip with Adafruit firmware. If Building a custom board with the SPI friend it would be easiest to just use the pin selection that the 32u4 feather uses but you can change the pins in the config.h options with the following defines:
* #define AdafruitBleResetPin D4
* #define AdafruitBleCSPin    B4
* #define AdafruitBleIRQPin   E6


<!-- FIXME: Document bluetooth support more completely. -->
## Bluetooth Rules.mk Options
Use only one of these
* BLUETOOTH_ENABLE = yes (Legacy Option)
* BLUETOOTH = RN42
* BLUETOOTH = AdafruitEZKey
* BLUETOOTH = AdafruitBLE

## Bluetooth Keycodes

This is used when multiple keyboard outputs can be selected. Currently this only allows for switching between USB and Bluetooth on keyboards that support both.

|Name      |Description                                   |
|----------|----------------------------------------------|
|`OUT_AUTO`|Automatically switch between USB and Bluetooth|
|`OUT_USB` |USB only                                      |
|`OUT_BT`  |Bluetooth only                                |
