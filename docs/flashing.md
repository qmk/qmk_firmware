# Flashing Instructions and Bootloader Information

There are quite a few different types of bootloaders that keyboards use, and just about all of the use a different flashing method. Luckily, projects like the [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) aim to be compatible with all the different types without having to think about it much, but this article will describe the different types of bootloaders, and available methods for flashing them.

If you have a bootloader selected with the `BOOTLOADER` variable in your `rules.mk`, QMK will automatically calculate if your .hex file is the right size to be flashed to the device, and output the total size in bytes (along with the max). To run this process manually, compile with the target `check-size`, eg `make planck/rev4:default:check-size`.

## DFU

Atmel's DFU bootloader comes on all atmega32u4 chips by default, and is used by many keyboards that have their own ICs on their PCBs (Older OLKB boards, Clueboards). Some keyboards may also use LUFA's DFU bootloader (or QMK's fork) (Newer OLKB boards) that adds in additional features specific to that hardware.

To ensure compatibility with the DFU bootloader, make sure this block is present your `rules.mk` (optionally with `lufa-dfu` or `qmk-dfu` instead):

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / `:dfu` in QMK (recommended command line)
* [Atmel's Flip](http://www.microchip.com/developmenttools/productdetails.aspx?partno=flip) (not recommended)

Flashing sequence:

1. Press the `RESET` keycode, or tap the RESET button (or short RST to GND).
2. Wait for the OS to detect the device
3. Erase the memory (may be done automatically)
4. Flash a .hex file
5. Reset the device into application mode (may be done automatically)

or:

    make <keyboard>:<keymap>:dfu

### QMK DFU

QMK has a fork of the LUFA DFU bootloader that allows for a simple matrix scan for exiting the bootloader and returning to the application, as well as flashing an LED/making a ticking noise with a speaker when things are happening. To enable these features, use this block in your `config.h` (The key that exits the bootloader needs to be hooked-up to the INPUT and OUTPUT defined here):

    #define QMK_ESC_OUTPUT F1 // usually COL
    #define QMK_ESC_INPUT D5 // usually ROW
    #define QMK_LED E6
    #define QMK_SPEAKER C6

The Manufacturer and Product names are automatically pulled from your `config.h`, and "Bootloader" is added to the product.

To generate this bootloader, use the `bootloader` target, eg `make planck/rev4:default:bootloader`.

To generate a production-ready .hex file (containing the application and the bootloader), use the `production` target, eg `make planck/rev4:default:production`.

### DFU commands

There are a number of DFU commands that you can use to flash firmware to a DFU device:

* `:dfu` - This is the normal option and waits until a DFU device is available, and then flashes the firmware. This will check every 5 seconds, to see if a DFU device has appeared.
* `:dfu-ee` - This flashes an `eep` file instead of the normal hex.  This is uncommon. 
* `:dfu-split-left` - This flashes the normal firmware, just like the default option (`:dfu`). However, this also flashes the "Left Side" EEPROM file for split keyboards. _This is ideal for Elite C based split keyboards._
* `:dfu-split-right` - This flashes the normal firmware, just like the default option (`:dfu`). However, this also flashes the "Right Side" EEPROM file for split keyboards. _This is ideal for Elite C based split keyboards._

## Caterina

Arduino boards and their clones use the [Caterina bootloader](https://github.com/arduino/ArduinoCore-avr/tree/master/bootloaders/caterina) (any keyboard built with a Pro Micro, or clone), and uses the avr109 protocol to communicate through virtual serial. Bootloaders like [A-Star](https://www.pololu.com/docs/0J61/9) are based on Caterina.

To ensure compatibility with the Caterina bootloader, make sure this block is present your `rules.mk`:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [avrdude](http://www.nongnu.org/avrdude/) with avr109 / `:avrdude` (recommended command line)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Flashing sequence:

1. Press the `RESET` keycode, or short RST to GND quickly (you only have 7 seconds to flash once it enters)
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Wait for the device to reset automatically

or

    make <keyboard>:<keymap>:avrdude


#### Caterina commands

There are a number of DFU commands that you can use to flash firmware to a DFU device:

* `:avrdude` - This is the normal option which waits until a Caterina device is available (by detecting a new COM port), and then flashes the firmware.
* `:avrdude-loop` - This runs the same command as `:avrdude`, but after each device is flashed, it will attempt to flash again.  This is useful for bulk flashing. _This requires you to manually escape the loop by hitting Ctrl+C._
* `:avrdude-split-left` - This flashes the normal firmware, just like the default option (`:avrdude`). However, this also flashes the "Left Side" EEPROM file for split keyboards. _This is ideal for Pro Micro based split keyboards._
* `:avrdude-split-right` - This flashes the normal firmware, just like the default option (`:avrdude`). However, this also flashes the "Right Side" EEPROM file for split keyboards. _This is ideal for Pro Micro based split keyboards._



## Halfkay

Halfkay is a super-slim protocol developed by PJRC that uses HID, and come on all Teensys (namely the 2.0).

To ensure compatibility with the Halfkay bootloader, make sure this block is present your `rules.mk`:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = halfkay
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Teensy Loader Command Line](https://www.pjrc.com/teensy/loader_cli.html) (recommended command line)

Flashing sequence:

1. Press the `RESET` keycode, or short RST to GND quickly (you only have 7 seconds to flash once it enters)
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

## USBasploader

USBasploader is a bootloader developed by matrixstorm. It is used in some non-USB AVR chips such as the ATmega328P, which run V-USB.

To ensure compatibility with the USBasploader bootloader, make sure this block is present in your `rules.mk`:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = USBasp
```

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [avrdude](http://www.nongnu.org/avrdude/) with the `usbasp` programmer
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Flashing sequence:

1. Press the `RESET` keycode, or keep the boot pin shorted to GND while quickly shorting RST to GND
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

## BootloadHID

BootloadHID is a USB bootloader for AVR microcontrollers. The uploader tool requires no kernel level driver on Windows and can therefore be run without installing any DLLs.

To ensure compatibility with the bootloadHID bootloader, make sure this block is present your `rules.mk`:

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = bootloadHID
```

Compatible flashers:

* [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash) (recommended Windows GUI)
* [bootloadhid Command Line](https://www.obdev.at/products/vusb/bootloadhid.html) / `:BootloadHID` in QMK (recommended command line)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode (may not work on all devices)
    * Hold the salt key while plugging the keyboard in (usually documented within keyboard readme) 
2. Wait for the OS to detect the device
3. Flash a .hex file
4. Reset the device into application mode (may be done automatically)

or:

    make <keyboard>:<keymap>:bootloadHID

## STM32

All STM32 chips come preloaded with a factory bootloader that cannot be modified nor deleted. Some STM32 chips have bootloaders that do not come with USB programming (e.g. STM32F103) but the process is still the same.

At the moment, no `BOOTLOADER` variable is needed on `rules.mk` for STM32.

Compatible flashers:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (recommended GUI)
* [dfu-util](https://github.com/Stefan-Schmidt/dfu-util) / `:dfu-util` (recommended command line)

Flashing sequence:

1. Enter the bootloader using any of the following methods:
    * Tap the `RESET` keycode (may not work on STM32F042 devices)
    * If a reset circuit is present, tap the RESET button
    * Otherwise, you need to bridge BOOT0 to VCC (via BOOT0 button or bridge), short RESET to GND (via RESET button or bridge), and then let go of the BOOT0 bridge
2. Wait for the OS to detect the device
3. Flash a .bin file
    * You will receive a warning about the DFU signature; Just ignore it
4. Reset the device into application mode (may be done automatically)
    * If you are building from command line (e.g. `make planck/rev6:default:dfu-util`), make sure that `:leave` is passed to the `DFU_ARGS` variable inside your `rules.mk` (e.g. `DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave`) so that your device resets after flashing

### STM32 Commands

There are a number of DFU commands that you can use to flash firmware to a STM32 device:

* `:dfu-util` - The default command for flashing to STM32 devices, and will wait until an STM32 bootloader device is present.
* `:dfu-util-split-left` - This flashes the normal firmware, just like the default option (`:dfu-util`). However, this also configures the "Left Side" EEPROM setting for split keyboards.
* `:dfu-util-split-right` - This flashes the normal firmware, just like the default option (`:dfu-util`). However, this also configures the "Right Side" EEPROM setting for split keyboards.
* `:st-link-cli` - This allows you to flash the firmware via ST-LINK's CLI utility, rather than dfu-util. 
