# ISP Flashing Guide

In order to flash a microcontroller over USB, it needs something called a bootloader. This bootloader lives in a specific section of the flash memory, and allows you to load the actual application firmware (in this case, QMK) into the rest of the flash.

However, it can sometimes happen that the bootloader becomes corrupted and needs reflashing, or you may want to change the bootloader to another one. It's not possible to do this with the existing bootloader, because, of course, it is already running, and cannot overwrite itself. Instead, you will need to ISP flash the microcontroller.

There are several different kinds of bootloaders available for AVR microcontrollers. Most STM32 ARM-based microcontrollers already have a USB-capable bootloader in ROM, so generally do not need to be ISP flashed.

## Hardware

One of the following devices is required to perform the ISP flashing. The product links are to the official versions, however you can certainly source them elsewhere.

You'll also need some jumper wires to connect the ISP flasher and the target board. Some boards have an ISP header with the necessary pins broken out. If not, then you will need to temporarily solder the wires to the PCB -- usually to switch pins or directly to the MCU.
The wiring is fairly straightforward; for the most part, you'll be connecting like to like. Refer to the target MCU's datasheet for the exact `RESET`, `SCLK`, `MOSI` and `MISO` pins.

### Pro Micro as ISP

[SparkFun Pro Micro](https://www.sparkfun.com/products/12640)

To use a 5V/16MHz Pro Micro as an ISP flashing tool, you will first need to load a [special firmware](https://github.com/qmk/qmk_firmware/blob/master/util/pro_micro_ISP_B6_10.hex) onto it that emulates a hardware ISP flasher.

**AVRDUDE Programmer**: `avrisp`  
**AVRDUDE Port**: Serial

#### Wiring

|Pro Micro  |Keyboard|
|-----------|--------|
|`VCC`      |`VCC`   |
|`GND`      |`GND`   |
|`10` (`B6`)|`RESET` |
|`15` (`B1`)|`SCLK`  |
|`16` (`B2`)|`MOSI`  |
|`14` (`B3`)|`MISO`  |

!> Note that the `10` pin on the Pro Micro should be wired to the `RESET` pin on the keyboard's controller. ***DO NOT*** connect the `RESET` pin on the Pro Micro to the `RESET` on the keyboard.

### Teensy 2.0 as ISP

[PJRC Teensy 2.0](https://www.pjrc.com/store/teensy.html)

To use a Teensy 2.0 as an ISP flashing tool, you will first need to load a [special firmware](https://github.com/qmk/qmk_firmware/blob/master/util/teensy_2.0_ISP_B0.hex) onto it that emulates a hardware ISP flasher.

**AVRDUDE Programmer**: `avrisp`  
**AVRDUDE Port**: Serial

#### Wiring

|Teensy|Keyboard|
|------|--------|
|`VCC` |`VCC`   |
|`GND` |`GND`   |
|`B0`  |`RESET` |
|`B1`  |`SCLK`  |
|`B2`  |`MOSI`  |
|`B3`  |`MISO`  |

!> Note that the `B0` pin on the Teensy should be wired to the `RESET` pin on the keyboard's controller. ***DO NOT*** connect the `RESET` pin on the Teensy to the `RESET` on the keyboard.

### SparkFun PocketAVR / USBtinyISP / USBasp

[SparkFun PocketAVR](https://www.sparkfun.com/products/9825)  
[Adafruit USBtinyISP](https://www.adafruit.com/product/46)  
[Thomas Fischl's USBasp](https://www.fischl.de/usbasp/)

**AVRDUDE Programmer**: `usbtiny` / `usbasp`  
**AVRDUDE Port**: `usb`

#### Wiring

|ISP      |Keyboard|
|---------|--------|
|`VCC`    |`VCC`   |
|`GND`    |`GND`   |
|`RST`    |`RESET` |
|`SCLK`   |`SCLK`  |
|`MOSI`   |`MOSI`  |
|`MISO`   |`MISO`  |


### Bus Pirate

[Adafruit Bus Pirate](https://www.adafruit.com/product/237)

!> The 5-pin "ICSP" header is for ISP flashing the PIC microcontroller of the Bus Pirate. Connect your target board to the 10-pin header opposite the USB connector instead.

**AVRDUDE Programmer**: `buspirate`  
**AVRDUDE Port**: Serial

#### Wiring

|Bus Pirate|Keyboard|
|----------|--------|
|`+5V`     |`VCC`   |
|`GND`     |`GND`   |
|`RST`     |`RESET` |
|`CLK`     |`SCLK`  |
|`MOSI`    |`MOSI`  |
|`MISO`    |`MISO`  |

## Software

[QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) supports flashing both the ISP firmware and bootloader, but note that it cannot (currently) set the AVR fuse bytes for the actual ISP flashing step, so you may want to work with `avrdude` directly instead.

Setting up the [QMK environment](newbs.md) is highly recommended, as it automatically installs `avrdude` along with a host of other tools.

## Bootloader Firmware

One of these files is what you will be ISP flashing onto the board. The default fuses are also listed.

If you're not sure what your board uses, look in the `rules.mk` file for the keyboard in QMK. The `MCU` and `BOOTLOADER` lines will have the values you need. It may differ between different versions of the board.

### Atmel DFU

These are the [factory default bootloaders](https://www.microchip.com/content/dam/mchp/documents/OTH/ProductDocuments/SoftwareLibraries/Firmware/megaUSB_DFU_Bootloaders.zip) shipped by Atmel (now Microchip). Note that the AT90USB64 and AT90USB128 bootloaders are [slightly modified](https://github.com/qmk/qmk_firmware/pull/14064), due to a bug causing them to not enumerate properly in Windows 8 and later.

|MCU                                                                                               |Low   |High                           |Extended|USB ID     |
|--------------------------------------------------------------------------------------------------|------|-------------------------------|--------|-----------|
|[ATmega16U4](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega16u4_1.0.1.hex)|`0x5E`|`0x99` / `0xD9` (JTAG disabled)|`0xF3`  |`03EB:2FF3`|
|[ATmega32U4](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega32u4_1.0.0.hex)|`0x5E`|`0x99` / `0xD9` (JTAG disabled)|`0xF3`  |`03EB:2FF4`|
|[AT90USB64](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb64_1.0.0.hex)  |`0x5E`|`0x9B` / `0xDB` (JTAG disabled)|`0xF3`  |`03EB:2FF9`|
|[AT90USB128](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb128_1.0.1.hex)|`0x5E`|`0x99` / `0xD9` (JTAG disabled)|`0xF3`  |`03EB:2FFB`|

### Caterina

This is the default Arduino-style bootloader derived from the [LUFA CDC bootloader](https://github.com/abcminiuser/lufa/tree/master/Bootloaders/CDC), and is only for the ATmega32U4.

There are several variants depending on the vendor, but they all mostly work the same way. The SparkFun variants, for example, require the `RESET` pin to be [grounded twice quickly](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide#ts-reset) in order to stay in bootloader mode for more than 750 ms.

|MCU                                                                                                                                                              |Low   |High  |Extended|USB ID     |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|------|------|--------|-----------|
|[SparkFun Pro Micro (3V3/8MHz)](https://github.com/sparkfun/Arduino_Boards/blob/master/sparkfun/avr/bootloaders/caterina/Caterina-promicro8.hex)                 |`0xFF`|`0xD8`|`0xFE`  |`1B4F:9203`|
|[SparkFun Pro Micro (5V/16MHz)](https://github.com/sparkfun/Arduino_Boards/blob/master/sparkfun/avr/bootloaders/caterina/Caterina-promicro16.hex)                |`0xFF`|`0xD8`|`0xFB`  |`1B4F:9205`|
|[SparkFun LilyPadUSB (and some Pro Micro clones)](https://github.com/sparkfun/Arduino_Boards/blob/main/sparkfun/avr/bootloaders/caterina/Caterina-lilypadusb.hex)|`0xFF`|`0xD8`|`0xFE`  |`1B4F:9207`|
|[Pololu A-Star 32U4](https://github.com/pololu/a-star/blob/master/bootloaders/caterina/Caterina-A-Star.hex)*                                                     |`0xFF`|`0xD0`|`0xF8`  |`1FFB:0101`|
|[Adafruit Feather 32U4](https://github.com/adafruit/Caterina-Bootloader/blob/master/Built%20Firmwares/Caterina-Feather32u4.hex)                                  |`0xFF`|`0xD8`|`0xFB`  |`239A:000C`|
|[Adafruit ItsyBitsy 32U4 (3V3/8MHz)](https://github.com/adafruit/Caterina-Bootloader/blob/master/Caterina_itsybitsy3V.hex)*                                      |`0xFF`|`0xD8`|`0xFB`  |`239A:000D`|
|[Adafruit ItsyBitsy 32U4 (5V/16MHz)](https://github.com/adafruit/Caterina-Bootloader/blob/master/Caterina_itsybitsy5V.hex)                                       |`0xFF`|`0xD8`|`0xFB`  |`239A:000E`|
|[Arduino Leonardo](https://github.com/arduino/ArduinoCore-avr/blob/master/bootloaders/caterina/Caterina-Leonardo.hex)*                                           |`0xFF`|`0xD8`|`0xFB`  |`2341:0036`|
|[Arduino Micro](https://github.com/arduino/ArduinoCore-avr/blob/master/bootloaders/caterina/Caterina-Micro.hex)*                                                 |`0xFF`|`0xD8`|`0xFB`  |`2341:0037`|

?> Files marked with a * have combined Arduino sketches, which runs by default and also appears as a serial port. However, this is *not* the bootloader device.

### BootloadHID (PS2AVRGB)

This bootloader is primarily for keyboards originally designed for the PS2AVRGB firmware and Bootmapper Client. It is not recommended for use in new designs.

|MCU                                                                                                        |Low   |High  |USB ID     |
|-----------------------------------------------------------------------------------------------------------|------|------|-----------|
|[ATmega32A](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_ps2avrgb_bootloadhid_1.0.1.hex)|`0x0F`|`0xD0`|`16C0:05DF`|

### USBaspLoader

USBaspLoader is a bootloader based on V-USB that emulates a hardware USBasp device. It runs on ATmega32A and ATmega328P MCUs.

Precompiled `.hex` files are generally not available, but you can compile it yourself by setting up the QMK environment and following Coseyfannitutti's guide for the appropriate MCU:

|MCU                                                                                  |Low   |High  |Extended|USB ID     |
|-------------------------------------------------------------------------------------|------|------|--------|-----------|
|[ATmega32A](https://github.com/coseyfannitutti/discipline/tree/master/doc/bootloader)|`0x1F`|`0xC0`|*n/a*   |`16C0:05DC`|
|[ATmega328P](https://github.com/coseyfannitutti/discipad/tree/master/doc/bootloader) |`0xD7`|`0xD0`|`0x04`  |`16C0:05DC`|

Note that some boards may have their own specialized build of this bootloader in a separate repository. This will usually be linked to in the board's readme.

## Flashing the Bootloader

Open a new Terminal window - if you are on Windows, use MSYS2 or QMK MSYS, not the Command Prompt. Navigate to the directory your bootloader `.hex` is in. Now it's time to run the `avrdude` command.

The syntax of `avrdude` is:

```
avrdude -c <programmer> -P <port> -p <mcu> -U flash:w:<filename>:i
```

 * `<programmer>` corresponds to the programmer type listed for each ISP flasher in the [Hardware](#hardware) section, for example `avrisp`.
 * `<port>` is the serial port that appears when you plug the ISP flasher in, if any. For some programmers this is simply `usb` (or you can omit the `-P` argument completely) since they do not operate as a serial device.
   * Windows: `COMx` - check Device Manager, under the "Ports (COM & LPT)" section
   * Linux: `/dev/ttyACMx`
   * macOS: `/dev/tty.usbmodemXXXXXX`
 * `<mcu>` should be the lowercase name of the target AVR microcontroller, for example `atmega32u4`.
 * `<filename>` is the absolute or relative path to the bootloader to be flashed, for example `Caterina-Micro.hex`.

You can also run `man avrdude` for more information.

If all goes well, you should get output similar to the following:

```
avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e9587 (probably m32u4)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "Caterina-Micro.hex"
avrdude: writing flash (32730 bytes):

Writing | ################################################## | 100% 11.58s

avrdude: 32730 bytes of flash written
avrdude: verifying flash memory against Caterina-Micro.hex:
avrdude: load data flash data from input file Caterina-Micro.hex:
avrdude: input file Caterina-Micro.hex contains 32730 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 10.33s

avrdude: verifying ...
avrdude: 32730 bytes of flash verified

avrdude: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude done.  Thank you.
```

### Setting the Fuses

This is a slightly more advanced topic, but may be necessary if you are switching from one bootloader to another (for example, Caterina to Atmel/QMK DFU on a Pro Micro). Fuses control some of the low-level functionality of the AVR microcontroller, such as clock speed, whether JTAG is enabled, and the size of the section of flash memory reserved for the bootloader, among other things. You can find a fuse calculator for many AVR parts [here](https://www.engbedded.com/conffuse/).

!> **WARNING:** Setting incorrect fuse values, in particular the clock-related bits, may render the MCU practically unrecoverable without high voltage programming (not covered here)! Make sure to double check the commands you enter before you execute them.

To set the fuses, add the following to the `avrdude` command:

```
-U lfuse:w:0xXX:m -U hfuse:w:0xXX:m -U efuse:w:0xXX:m
```

where the `lfuse`, `hfuse` and `efuse` arguments represent the low, high and extended fuse bytes as listed in the [Hardware](#hardware) section.

?> You may get a warning from `avrdude` that the extended fuse byte does not match what you provided when reading it back. If the second hex digit matches, this can usually be safely ignored, because the top four bits of this fuse do not actually exist on many AVR parts, and may read back as anything.

## Creating a "Production" Firmware

For mass production purposes, it is possible to join the bootloader and QMK firmware together into a single file, due to the way the [Intel Hex format](https://en.wikipedia.org/wiki/Intel_HEX) works:

 1. Open the QMK firmware and bootloader `.hex` files in a text editor.
 2. Remove the last line of the QMK firmware (which should be `:00000001FF` - this is just an "end of file" marker).
 3. Paste the contents of the bootloader `.hex` file onto a new line at the end of the QMK firmware file, with no empty lines between.
 4. Save it as a new file, for example `<keyboard>_<keymap>_production.hex`.

You can then ISP flash this combined firmware instead, which allows you to skip the extra step of flashing the QMK firmware over USB.
