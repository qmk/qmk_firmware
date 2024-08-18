
# Replicazeron

This is a config to run a 3dprinted keyboard controller with qmk based on this project:

https://sites.google.com/view/alvaro-rosati/azeron-keypad-diy-tutorial

Some additional and redesigned files (i.e. for the OLED-display) can be found in [this repo](https://github.com/9R/replicazeron).

![Replicazeron](https://i.imgur.com/WTys4SM.jpg)

[Gallery](https://imgur.com/a/2qlEPVl)

## Features

 * 23 keys
 * analog stick with WASD emulation
 * 5way dpad
 * 2 status LEDS
 * 6x WS2812 RGB-LED lighting

## Supported MCUs

Currently configs for STM32F103 and atmega32U4 are available, but STM32 is recommended, since the atmega may run out of flash with all features enabled.

With minor adjustments to Pinconfig it should be possible to use other MCUs that are supported by QMK


## Wirering

Full schematics can be found in this repo:

https://github.com/9R/replicazeron_schematics

### Rows
|row| promiro gpios | promicro pin | stm32F103 gpios |   color |
|---|---------------|--------------|-----------------|---------|
| 0 |          B1   |          15  |          B15    |  red    |
| 1 |          B3   |          14  |           A8    |  blue   |
| 2 |          B2   |          16  |           A9    |  yellow |
| 3 |          B6   |          10  |          A10    |  brown  |
| 4 |          B5   |           9  |          A15    |  orange |
| 5 |          B4   |           8  |           B3    |  green  |

### Columns
|col| promiro gpios | promicro pin | stm32F103 gpios |  color  |
|---|---------------|--------------|-----------------|---------|
| 0 |         C6    |            5 |          A7     |  white  |
| 1 |         D4    |            4 |          A6     |  grey   |
| 2 |         D7    |            6 |          A5     |  violet |
| 3 |         E6    |            7 |          A4     |  grey   |
| 4 |         F7    |           A0 |          B4     |  white  |

### Analog
| promicro gpio | stm32F103 gpio | pin | color |
|---------------|----------------|-----|-------|
|          GND  |           GND  | GND | white |
|          VCC  |           VCC  | VCC | red   |
|          F4   |           B1   | VRx | brown |
|          F5   |           B0   | VRy | yellow|
|               |                | SW  | blue  |

### OLED
| promicro gpio | stm32F103 gpio | pin | color |
|---------------|----------------|-----|-------|
|          GND  |           GND  | GND | white |
|          VCC  |           VCC  | VCC | red   |
|           D4  |           B10  | SDA | green |
|           C6  |           B11  | SCL | yellow|
