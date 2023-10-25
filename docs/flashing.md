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
  ```
  dfu-programmer <mcu> erase --force
  dfu-programmer <mcu> flash --force <filename>
  dfu-programmer <mcu> reset
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Press the `QK_BOOT` keycode
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
Currently we do not recommend making `QMK_ESC` the same key as the one designated for [Bootmagic Lite](feature_bootmagic.md), as holding it down will cause the MCU to loop back and forth between entering and exiting the bootloader.

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
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)
* [avrdude](https://www.nongnu.org/avrdude/) with the `avr109` programmer / `:avrdude` target in QMK (recommended command line)
  ```
  avrdude -p <mcu> -c avr109 -P <serialport> -U flash:w:<filename>:i
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods (you only have 7 seconds to flash once it enters; some variants may require you to reset twice within 750 milliseconds):
    * Press the `QK_BOOT` keycode
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
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) / `:teensy` target in QMK (recommended command line)
  ```
  teensy_loader_cli -v -mmcu=<mcu> <filename>
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods (you only have 7 seconds to flash once it enters):
    * Press the `QK_BOOT` keycode
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
BOOTLOADER = usbasploader
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)
* [avrdude](https://www.nongnu.org/avrdude/) with the `usbasp` programmer / `:usbasp` target in QMK (recommended command line)
  ```
  avrdude -p <mcu> -c usbasp -U flash:w:<filename>:i
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Press the `QK_BOOT` keycode
    * Keep the `BOOT` button held while quickly tapping the `RESET` button on the PCB
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Press the `RESET` button on the PCB or short RST to GND

## BootloadHID

BootloadHID is a USB bootloader for AVR microcontrollers. It presents itself as an HID input device, much like HalfKay, and can therefore be run without installing any driver on Windows.

To ensure compatibility with the bootloadHID bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = bootloadhid
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash)
* [bootloadHID CLI](https://www.obdev.at/products/vusb/bootloadhid.html) / `:bootloadhid` target in QMK (recommended command line)
  ```
  bootloadHID -r <filename>
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Hold the salt key while plugging the keyboard in - for PS2AVRGB boards, this is usually the key connected to MCU pins A0 and B0, otherwise it will be documented in your keyboard's readme
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

### QMK HID

QMK maintains [a fork of the LUFA HID bootloader](https://github.com/qmk/lufa/tree/master/Bootloaders/HID), which uses a USB HID Endpoint for flashing in the way that the PJRC's Teensy Loader flasher and HalfKay bootloader work. Additionally, it performs a simple matrix scan for exiting the bootloader and returning to the application, as well as flashing an LED/making a ticking noise with a speaker when things are happening.

To ensure compatibility with the QMK HID bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = qmk-hid
```

To enable the additional features, add the following defines to your `config.h`:

```c
#define QMK_ESC_OUTPUT F1  // COL pin if COL2ROW
#define QMK_ESC_INPUT  D5  // ROW pin if COL2ROW
// Optional:
//#define QMK_LED E6
//#define QMK_SPEAKER C6
```

Currently we do not recommend making `QMK_ESC` the same key as the one designated for [Bootmagic Lite](feature_bootmagic.md), as holding it down will cause the MCU to loop back and forth between entering and exiting the bootloader.

The manufacturer and product strings are automatically pulled from `config.h`, with " Bootloader" appended to the product string.

To generate this bootloader, use the `bootloader` target, eg. `make planck/rev4:default:bootloader`. To generate a production-ready .hex file (combining QMK and the bootloader), use the `production` target, eg. `make planck/rev4:default:production`.

Compatible flashers:

* TBD
  * Currently, you need to either use the [Python script](https://github.com/qmk/lufa/tree/master/Bootloaders/HID/HostLoaderApp_python), or compile [`hid_bootloader_cli`](https://github.com/qmk/lufa/tree/master/Bootloaders/HID/HostLoaderApp), from the LUFA repo. Homebrew may (will) have support for this directly (via `brew install qmk/qmk/hid_bootloader_cli`).

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Press the `QK_BOOT` keycode
    * Press the `RESET` button on the PCB if available
    * short RST to GND quickly
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

### `make` Targets

* `:qmk-hid`: Checks every 5 seconds until a DFU device is available, and then flashes the firmware.

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
  ```
  dfu-util -a 0 -d 0483:DF11 -s 0x8000000:leave -D <filename>
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode (may not work on STM32F042 devices)
    * If a reset circuit is present, tap the `RESET` button on the PCB; some boards may also have a toggle switch that must be flipped
    * Otherwise, you need to bridge `BOOT0` to VCC (via `BOOT0` button or jumper), short `RESET` to GND (via `RESET` button or jumper), and then let go of the `BOOT0` bridge
2. Wait for the OS to detect the device
3. Flash a .bin file
4. Reset the device into application mode (may be done automatically)

### `make` Targets

* `:dfu-util`: Waits until an STM32 bootloader device is available, and then flashes the firmware.
* `:dfu-util-split-left` and `:dfu-util-split-right`: Flashes the firmware as with `:dfu-util`, but also sets the handedness setting in EEPROM. This is ideal for Proton-C-based split keyboards.
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
  ```
  dfu-util -a 2 -d 1EAF:0003 -D <filename>
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
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
  ```
  dfu-util -a 0 -d 1C11:B007 -D <filename>
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Press the `RESET` button on the PCB
2. Wait for the OS to detect the device
3. Flash a .bin file
4. Reset the device into application mode (may be done automatically)

## WB32 DFU

Some keyboards produced for several commercial brands (GMMK, Akko, MonsGeek, Inland) use this bootloader. The `wb32-dfu-updater` utility is bundled with [QMK MSYS](https://msys.qmk.fm/) and [Glorious's build of QMK Toolbox](https://www.gloriousgaming.com/blogs/guides-resources/gmmk-2-qmk-installation-guide). If neither of these flashing methods is available for your OS, you will likely need to [compile the CLI version from source](https://github.com/WestberryTech/wb32-dfu-updater).

The `info.json` setting for this bootloader is `wb32-dfu`.

Compatible flashers:

* [Glorious's build of QMK Toolbox](https://www.gloriousgaming.com/blogs/guides-resources/gmmk-2-qmk-installation-guide) (recommended GUI)
* [wb32-dfu-updater_cli](https://github.com/WestberryTech/wb32-dfu-updater) / `:flash` target in QMK (recommended command line)
  ```
  wb32-dfu-updater_cli -t -s 0x8000000 -D <filename>
  ```

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Press the `RESET` button on the PCB
2. Wait for the OS to detect the device
3. Flash a .bin file
4. Reset the device into application mode (may be done automatically)

## tinyuf2

Keyboards may opt into supporting the tinyuf2 bootloader. This is currently only supported on F303/F401/F411.

The `rules.mk` setting for this bootloader is `tinyuf2`, and can be specified at the keymap or user level.

To ensure compatibility with the tinyuf2 bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = tinyuf2
```

Compatible flashers:

* Any application able to copy a file from one place to another, such as _macOS Finder_ or _Windows Explorer_.

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Double-tap the `nRST` button on the PCB.
2. Wait for the OS to detect the device
3. Copy the .uf2 file to the new USB disk
4. Wait for the keyboard to become available

or

CLI Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Double-tap the `nRST` button on the PCB.
2. Wait for the OS to detect the device
3. Flash via QMK CLI eg. `qmk flash --keyboard handwired/onekey/blackpill_f411_tinyuf2 --keymap default`
4. Wait for the keyboard to become available

### `make` Targets

* `:uf2-split-left` and `:uf2-split-right`: Flashes the firmware but also sets the handedness setting in EEPROM by generating a side specific firmware.

## uf2boot

Keyboards may opt into supporting the uf2boot bootloader. This is currently only supported on F103.

The `rules.mk` setting for this bootloader is `uf2boot`, and can be specified at the keymap or user level.

To ensure compatibility with the uf2boot bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = uf2boot
```

Compatible flashers:

* Any application able to copy a file from one place to another, such as _macOS Finder_ or _Windows Explorer_.

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Double-tap the `nRST` button on the PCB.
2. Wait for the OS to detect the device
3. Copy the .uf2 file to the new USB disk
4. Wait for the keyboard to become available

or

CLI Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Double-tap the `nRST` button on the PCB.
2. Wait for the OS to detect the device
3. Flash via QMK CLI eg. `qmk flash --keyboard handwired/onekey/bluepill_uf2boot --keymap default`
4. Wait for the keyboard to become available

### `make` Targets

* `:uf2-split-left` and `:uf2-split-right`: Flashes the firmware but also sets the handedness setting in EEPROM by generating a side specific firmware.

## Raspberry Pi RP2040 UF2

The `rules.mk` setting for this bootloader is `rp2040`, and can be specified at the keymap or user level.

To ensure compatibility with the rp2040 bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
BOOTLOADER = rp2040
```

Compatible flashers:

* Any application able to copy a file from one place to another, such as _macOS Finder_ or _Windows Explorer_.

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Hold the `BOOTSEL` button on the PCB while plugin in the usb cable.
    * Double-tap the `RESET` button on the PCB<sup>1</sup>.
2. Wait for the OS to detect the device
3. Copy the .uf2 file to the new USB disk
4. Wait for the keyboard to become available

or

CLI Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `QK_BOOT` keycode
    * Hold the `BOOTSEL` button on the PCB while plugin in the usb cable.
    * Double-tap the `RESET` button on the PCB<sup>1</sup>.
2. Wait for the OS to detect the device
3. Flash via QMK CLI eg. `qmk flash --keyboard handwired/onekey/rpi_pico --keymap default`
4. Wait for the keyboard to become available

<sup>1</sup>: This works only if QMK was compiled with `RP2040_BOOTLOADER_DOUBLE_TAP_RESET` defined.
