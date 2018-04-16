# QMK Hardware Drivers

QMK is used on a lot of different hardware. While support for the most common MCU's and matrix configurations is built-in there are a number of drivers that can be added to a keyboard to support additional hardware. Examples include mice and other pointing devices, i/o expanders for split keyboards, bluetooth modules, and LCD, OLED, and TFT screens.

<!-- FIXME: This should talk about how drivers are integrated into QMK and how you can add your own driver.

# Driver System Overview

-->

# Available Drivers

## ProMicro (AVR Only)

Support for addressing pins on the ProMicro by their Arduino name rather than their AVR name. This needs to be better documented, if you are trying to do this and reading the code doesn't help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) and we can help you through the process.

## SSD1306 (AVR Only)

Support for SSD1306 based OLED displays. This needs to be better documented, if you are trying to do this and reading the code doesn't help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) and we can help you through the process.

## uGFX

You can make use of uGFX within QMK to drive character and graphic LCD's, LED arrays, OLED, TFT, and other display technologies. This needs to be better documented, if you are trying to do this and reading the code doesn't help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) and we can help you through the process.

## WS2812 (AVR Only)

Support for WS2811/WS2812{a,b,c} LED's. For more information see the [RGB Light](feature_rgblight.md) page.
