# Flashing Instructions and Bootloader Information

There are quite a few different types of bootloaders that keyboards use, and almost all of them use their own flashing method and tools. Luckily, projects like the [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) aim to support as many of them as possible, but this article will describe the different types of bootloaders, and available methods for flashing them.

For AVR-based keyboards, QMK will automatically calculate if your `.hex` file is the right size to be flashed to the device based on the `BOOTLOADER` value set in `rules.mk`, and output the total size in bytes (along with the max).

You will also be able to use the CLI to flash your keyboard, by running:
```
$ qmk flash -kb <keyboard> -km <keymap>
```
See the [`qmk flash`](cli_commands.md#qmk-flash) documentation for more information.

## Atmel DFU

Atmel's DFU bootloader comes on all USB AVRs by default (except for 16/32U4RC), and is used by many keyboards that have their own ICs on their PCBs (older OLKB boards, Clueboards). Some keyboards may also use LUFA's DFU bootloader, or QMK's fork of it (newer OLKB boards), that adds in additional features specific to that hardware.

To ensure compatibility with the DFU bootloader, make sure this block is present in your `rules.mk` (optionally with `lufa-dfu` or `qmk-dfu` instead):

```make
# Bootloader selection
BOOTLOADER = atmel-dfu
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / `:dfu` target in QMK (recommended command line)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Press the `RESET` keycode
    * Press the `RESET` button on the PCB if available
    * Short RST to GND quickly
2. Wait for the OS to detect the device
3. Erase the flash memory (will be done automatically if using the Toolbox or CLI/`make` command)
4. Flash a .hex file
5. Reset the device into application mode (will be done automatically as above)

### QMK DFU

QMK maintains [a fork of the LUFA DFU bootloader](https://github.com/qmk/lufa/tree/master/Bootloaders/DFU) that additionally performs a simple matrix scan for exiting the bootloader and returning to the application, as well as flashing an LED/making a ticking noise with a speaker when things are happening. To enable these features, add the following defines to your `config.h`:

```c
#define QMK_ESC_OUTPUT F1  // COL pin if COL2ROW
#define QMK_ESC_INPUT  D5  // ROW pin if COL2ROW
// Optional:
//#define QMK_LED E6
//#define QMK_SPEAKER C6
```
Currently we do not recommend making `QMK_ESC` the same key as the one designated for [Bootmagic Lite](feature_bootmagic.md#bootmagic-lite), as holding it down will cause the MCU to loop back and forth between entering and exiting the bootloader.

The manufacturer and product strings are automatically pulled from `config.h`, with " Bootloader" appended to the product string.

To generate this bootloader, use the `bootloader` target, eg. `make planck/rev4:default:bootloader`. To generate a production-ready .hex file (combining QMK and the bootloader), use the `production` target, eg. `make planck/rev4:default:production`.

### `make` Targets

* `:dfu`: Checks every 5 seconds until a DFU device is available, and then flashes the firmware.
* `:dfu-split-left` and `:dfu-split-right`: Flashes the firmware as with `:dfu`, but also sets the handedness setting in EEPROM. This is ideal for Elite-C-based split keyboards.

## Caterina

Arduino boards and their clones use the [Caterina bootloader](https://github.com/arduino/ArduinoCore-avr/tree/master/bootloaders/caterina) or a variant of it (any keyboard built with a Pro Micro or clone, and the Pololu A-Star), and uses the AVR109 protocol to communicate through virtual serial.

To ensure compatibility with the Caterina bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = caterina
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [avrdude](https://www.nongnu.org/avrdude/) with the `avr109` programmer / `:avrdude` target in QMK (recommended command line)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Flashing sequence:

1. Enter the bootloader using any of the following methods (you only have 7 seconds to flash once it enters; some variants may require you to reset twice within 750 milliseconds):
    * Press the `RESET` keycode
    * Press the `RESET` button on the PCB if available
    * Short RST to GND quickly
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Wait for the device to reset automatically

### `make` Targets

* `:avrdude`: Checks every 5 seconds until a Caterina device is available (by detecting a new COM port), and then flashes the firmware.
* `:avrdude-loop`: Flashes the firmware as with `:avrdude`, but after each device is flashed, will attempt to flash again. This is useful for bulk flashing. Hit Ctrl+C to escape the loop.
* `:avrdude-split-left` and `:avrdude-split-right`: Flashes the firmware as with `:avrdude`, but also sets the handedness setting in EEPROM. This is ideal for Pro Micro-based split keyboards.

## HalfKay

HalfKay is a super-slim bootloader developed by PJRC that presents itself as an HID device (which requires no additional driver), and comes preflashed on all Teensys, namely the 2.0. It is currently closed-source, and thus once overwritten (eg. via ISP flashing another bootloader), cannot be restored.

To ensure compatibility with the Halfkay bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = halfkay
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) / `:teensy` target in QMK (recommended command line)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)

Flashing sequence:

1. Enter the bootloader using any of the following methods (you only have 7 seconds to flash once it enters):
    * Press the `RESET` keycode
    * Press the `RESET` button on the Teensy or PCB if available
    * short RST to GND quickly
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

## USBasploader

USBasploader is a bootloader originally by [Objective Development](https://www.obdev.at/products/vusb/usbasploader.html). It emulates a USBasp ISP programmer and is used in some non-USB AVR chips such as the ATmega328P, which run V-USB.

To ensure compatibility with the USBasploader bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = USBasp
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [avrdude](https://www.nongnu.org/avrdude/) with the `usbasp` programmer / `:usbasp` target in QMK (recommended command line)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Press the `RESET` keycode
    * Keep the `BOOT` button held while quickly tapping the `RESET` button on the PCB
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Press the `RESET` button on the PCB or short RST to GND

## BootloadHID

BootloadHID is a USB bootloader for AVR microcontrollers. It presents itself as an HID input device, much like HalfKay, and can therefore be run without installing any driver on Windows.

To ensure compatibility with the bootloadHID bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = bootloadHID
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [bootloadHID CLI](https://www.obdev.at/products/vusb/bootloadhid.html) / `:bootloadHID` target in QMK (recommended command line)
* [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode
    * Hold the salt key while plugging the keyboard in - for PS2AVRGB boards, this is usually the key connected to MCU pins A0 and B0, otherwise it will be documented in your keyboard's readme
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

## STM32/APM32 DFU

All STM32 and APM32 MCUs, except for F103 (see the [STM32duino section](#stm32duino)) come preloaded with a factory bootloader that cannot be modified nor deleted.

To ensure compatibility with the STM32-DFU bootloader, make sure this block is present in your `rules.mk` (optionally with `apm32-dfu` instead):

```make
# Bootloader selection
BOOTLOADER = stm32-dfu
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-util](https://dfu-util.sourceforge.net/) / `:dfu-util` target in QMK (recommended command line)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode (may not work on STM32F042 devices)
    * If a reset circuit is present, tap the `RESET` button on the PCB; some boards may also have a toggle switch that must be flipped
    * Otherwise, you need to bridge `BOOT0` to VCC (via `BOOT0` button or jumper), short `RESET` to GND (via `RESET` button or jumper), and then let go of the `BOOT0` bridge
2. Wait for the OS to detect the device
3. Flash a .bin file
4. Reset the device into application mode (may be done automatically)

### `make` Targets

* `:dfu-util`: Waits until an STM32 bootloader device is available, and then flashes the firmware.
* `:dfu-util-split-left` and `:dfu-util-split-right`: Flashes the firmware as with `:avrdude`, but also sets the handedness setting in EEPROM. This is ideal for Proton-C-based split keyboards.
* `:st-link-cli`: Allows you to flash the firmware via the ST-Link CLI utility, rather than dfu-util. Requires an ST-Link dongle.
* `:st-flash`: Allows you to flash the firmware via the `st-flash` utility from [STLink Tools](https://github.com/stlink-org/stlink), rather than dfu-util. Requires an ST-Link dongle.

## STM32duino

This bootloader is used almost exclusively for STM32F103 boards, as they do not come with a USB DFU bootloader. The source code and prebuilt binaries can be found [here](https://github.com/rogerclarkmelbourne/STM32duino-bootloader).

To ensure compatibility with the STM32duino bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = stm32duino
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-util](https://dfu-util.sourceforge.net/) / `:dfu-util` target in QMK (recommended command line)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode
    * If a reset circuit is present, tap the `RESET` button on the PCB
    * Otherwise, you need to bridge `BOOT0` to VCC (via `BOOT0` button or jumper), short `RESET` to GND (via `RESET` button or jumper), and then let go of the `BOOT0` bridge
2. Wait for the OS to detect the device
3. Flash a .bin file
4. Reset the device into application mode (may be done automatically)

## Kiibohd DFU

Keyboards produced by Input Club use NXP Kinetis microcontrollers rather than STM32, and come with their own [custom bootloader](https://github.com/kiibohd/controller/tree/master/Bootloader), however the process and protocol is largely the same.

The `rules.mk` setting for this bootloader is `kiibohd`, but since this bootloader is limited to Input Club boards, it should not be necessary to set at keymap or user level.

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-util](https://dfu-util.sourceforge.net/) / `:dfu-util` target in QMK (recommended command line)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode (this may only enter the MCU into a "secure" bootloader mode; see https://github.com/qmk/qmk_firmware/issues/6112)
    * Press the `RESET` button on the PCB
2. Wait for the OS to detect the device
3. Flash a .bin file
4. Reset the device into application mode (may be done automatically)
