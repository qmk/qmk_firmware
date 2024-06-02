# QMK Hardware Drivers

QMK is used on a lot of different hardware. While support for the most common MCU's and matrix configurations is built-in there are a number of drivers that can be added to a keyboard to support additional hardware. Examples include mice and other pointing devices, i/o expanders for split keyboards, bluetooth modules, and LCD, OLED, and TFT screens.

<!-- FIXME: This should talk about how drivers are integrated into QMK and how you can add your own driver.

# Driver System Overview

-->

# Available Drivers

## ProMicro (AVR Only)

Support for addressing pins on the ProMicro by their Arduino name rather than their AVR name. This needs to be better documented, if you are trying to do this and reading the code doesn't help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) and we can help you through the process.

## SSD1306 OLED Driver

Support for SSD1306 based OLED displays. For more information see the [OLED Driver Feature](features/oled_driver) page.

## WS2812

Support for WS2811/WS2812{a,b,c} LED's. For more information see the [RGB Light](features/rgblight) page.

## IS31FL3731

Support for up to 2 drivers. Each driver impliments 2 charlieplex matrices to individually address LEDs using I2C. This allows up to 144 same color LEDs or 32 RGB LEDs. For more information on how to setup the driver see the [RGB Matrix](features/rgb_matrix) page.

## IS31FL3733

Support for up to a single driver with room for expansion. Each driver can control 192 individual LEDs or 64 RGB LEDs. For more information on how to setup the driver see the [RGB Matrix](features/rgb_matrix) page.

## 24xx series external I2C EEPROM

Support for an external I2C-based EEPROM instead of using the on-chip EEPROM. For more information on how to setup the driver see the [EEPROM Driver](drivers/eeprom) page.
