# ISP Flashing Guide

If you're having trouble flashing/erasing your board, and running into cryptic error messages like any of the following:

    libusb: warning [darwin_transfer_status] transfer error: timed out
    dfu.c:844: -ETIMEDOUT: Transfer timed out, NAK 0xffffffc4 (-60)
    atmel.c:1627: atmel_flash: flash data dfu_download failed.
    atmel.c:1629: Expected message length of 1072, got -60.
    atmel.c:1434: Error flashing the block: err -2.
    ERROR
    Memory write error, use debug for more info.
    commands.c:360: Error writing memory data. (err -4)

    dfu.c:844: -EPIPE: a) Babble detect or b) Endpoint stalled 0xffffffe0 (-32)
    Device is write protected.
    dfu.c:252: dfu_clear_status( 0x7fff4fc2ea80 )
    atmel.c:1434: Error flashing the block: err -2.
    ERROR
    Memory write error, use debug for more info.
    commands.c:360: Error writing memory data. (err -4)

You're likely going to need to ISP flash your board/device to get it working again. Luckily, this process is pretty straight-forward, provided you have any extra programmable keyboard, Pro Micro, or Teensy 2.0/Teensy 2.0++. There are also dedicated ISP flashers available for this, but most cost >$15, and it's assumed that if you are googling this error, this is the first you've heard about ISP flashing, and don't have one readily available (whereas you might have some other AVR board). __We'll be using a Teensy 2.0 or Pro Micro with Windows 10 in this guide__ - if you are comfortable doing this on another system, please consider editing this guide and contributing those instructions!   

## Software Needed

* [Teensy Loader](https://www.pjrc.com/teensy/loader.html) (if using a Teensy)
* QMK Toolbox (flash as usual - be sure to select the correct MCU) or `avrdude` via [WinAVR](http://www.ladyada.net/learn/avr/setup-win.html) (for Teensy & Pro Micro)

## Wiring

This is pretty straight-forward - we'll be connecting like-things to like-things in the following manner:

### Teensy 2.0

    Teensy B0  <-> Keyboard RESET
    Teensy B1  <-> Keyboard B1 (SCLK)
    Teensy B2  <-> Keyboard B2 (MOSI)
    Teensy B3  <-> Keyboard B3 (MISO)
    Teensy VCC <-> Keyboard VCC
    Teensy GND <-> Keyboard GND
    
### Pro Micro

    Pro Micro 10 (B6)  <-> Keyboard RESET
    Pro Micro 15 (B1)  <-> Keyboard B1 (SCLK)
    Pro Micro 16 (B2)  <-> Keyboard B2 (MOSI)
    Pro Micro 14 (B3)  <-> Keyboard B3 (MISO)
    Pro Micro VCC      <-> Keyboard VCC
    Pro Micro GND      <-> Keyboard GND

## The ISP Firmware (now pre-compiled)

The only difference between the .hex files below is which pin is connected to RESET. You can use them on other boards as well, as long as you're aware of the pins being used. If for some reason neither of these pins are available, [create an issue](https://github.com/qmk/qmk_firmware/issues/new), and we can generate one for you!

* Teensy 2.0: [`util/teensy_2.0_ISP_B0.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/teensy_2.0_ISP_B0.hex) (`B0`)
* Pro Micro: [`util/pro_micro_ISP_B6_10.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/pro_micro_ISP_B6_10.hex) (`B6/10`)

**Flash your Teenys/Pro Micro with one of these and continue - you won't need the file after flashing your ISP device.**

## Just the Bootloader File

If you just want to get things back to normal, you can flash only a bootloader from [`util/` folder](https://github.com/qmk/qmk_firmware/tree/master/util), and use your normal process to flash the firmware afterwards. Be sure to flash the correct bootloader for your chip:

* [`atmega32u4`](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega32u4_1_0_0.hex) - Most keyboards, Planck Rev 1-5, Preonic Rev 1-2
* [`at90usb1286`](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_at90usb128x_1_0_1.hex) - Planck Light Rev 1
* [`atmega32a`](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega32a_1_0_0.hex) - jj40

If you're not sure what your board uses, look in the `rules.mk` file for the keyboard in QMK. The `MCU =` line will have the value you need. It may differ between different versions of the board.

### Advanced/Production Techniques

If you'd like to flash both the bootloader **and** the regular firmware at the same time, you need to combine the files. 

1. Open the original firmware .hex file in a text editor
2. Remove the last line (which should be `:00000001FF` - this is an EOF message)
3. Copy the entire bootloader's contents onto a new line (with no empty lines between) and paste it at the end of the original file
4. Save it as a new file by naming it `<keyboard>_<keymap>_production.hex`

It's possible to use other bootloaders here in the same way, but __you need a bootloader__, otherwise you'll have to use ISP again to write new firmware to your keyboard.

## Flashing Your Bootloader/Production File

Make sure your keyboard is unplugged from any device, and plug in your Teensy.

### QMK Toolbox

1. `AVRISP device connected` will show up in yellow
2. Select the correct bootloader/production .hex file with the `Open` dialog (spaces can't be in the path)
3. Be sure the correct `Microcontroller` option is selected
4. Hit `Flash`
5. Wait, as nothing will output for a while, especially with production files

If the verification and fuse checks are ok, you're done! Your board may restart automatically, otherwise, unplug your Teensy and plug in your keyboard - you can leave your Teensy wired to your keyboard while testing things, but it's recommended that you desolder it/remove the wiring once you're sure everything works.

### Command Line

Open `cmd` and navigate to your where your modified .hex file is. We'll pretend this file is called `main.hex`, and that your Teensy 2.0 is on the `COM3` port - if you're unsure, you can open your Device Manager, and look for `Ports > USB Serial Device`. Use that COM port here. You can confirm it's the right port with:

    avrdude -c avrisp -P COM3 -p atmega32u4

and you should get something like the following output:

    avrdude: AVR device initialized and ready to accept instructions

    Reading | ################################################## | 100% 0.02s

    avrdude: Device signature = 0x1e9587

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

Since our keyboard uses an `atmega32u4` (common), that is the chip we'll specify. This is the full command:

    avrdude -c avrisp -P COM3 -p atmega32u4 -U flash:w:main.hex:i

If your board uses an `atmega32a` (e.g. on a jj40), the command is this (the extra code at the end sets the fuses correctly):

	avrdude -c avrisp -P COM3 -p atmega32 -U flash:w:main.hex:i -U hfuse:w:0xD0:m -U lfuse:w:0x0F:m

You should see a couple of progress bars, then you should see:

    avrdude: verifying ...
    avrdude: 32768 bytes of flash verified

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

Which means everything should be ok! Your board may restart automatically, otherwise, unplug your Teensy and plug in your keyboard - you can leave your Teensy wired to your keyboard while testing things, but it's recommended that you desolder it/remove the wiring once you're sure everything works.

If you have any questions/problems, feel free to [open an issue](https://github.com/qmk/qmk_firmware/issues/new)!
