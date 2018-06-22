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

You're likely going to need to ISP flash your board/device to get it working again. Luckily, this process is pretty straight-forward, provided you have any extra programmable keyboard, Arduino, or Teensy 2.0/Teensy 2.0++. There are also dedicated ISP flashers available for this, but most cost >$15, and it's assumed that if you are googling this error, this is the first you've heard about ISP flashing, and don't have one readily available (whereas you might have some other AVR board). __We'll be using a Teensy 2.0 with Windows 10 in this guide__ - if you are comfortable doing this on another system, please consider editing this guide and contributing those instructions!   

## Software Needed

* [Teensy Loader](https://www.pjrc.com/teensy/loader.html) (to program the Teensy)
* [WinAVR](http://www.ladyada.net/learn/avr/setup-win.html) (Windows)

## Wiring

This is pretty straight-forward - we'll be connecting like-things to like-things in the following manner:

    Flasher B0  <-> Keyboard RESET
    Flasher B1  <-> Keyboard B1 (SCLK)
    Flasher B2  <-> Keyboard B2 (MOSI)
    Flasher B3  <-> Keyboard B3 (MISO)
    Flasher VCC <-> Keyboard VCC
    Flasher GND <-> Keyboard GND

## The ISP Firmware (now pre-compiled)

Download the [`util/teensy_2.0_ISP_B0.hex`](https://github.com/qmk/qmk_firmware/blob/master/util/teensy_2.0_ISP_B0.hex) file from the repo, and load it onto your Teensy 2.0 using the Teensy Loader GUI or command line application.

## The `.hex` File

Before flashing your firmware, you're going to need to and do a little preparation. We'll be appending [this bootloader (also a .hex file)](https://github.com/qmk/qmk_firmware/blob/master/util/bootloader_atmega32u4_1_0_0.hex) (atmega32u4 only - other bootloaders are available in the [`util/` folder](https://github.com/qmk/qmk_firmware/tree/master/util)) to the end of our firmware by opening the original .hex file in a text editor, and removing the last line, which should be `:00000001FF` (this is an EOF message). After that's been removed, copy the entire bootloader's contents and paste it at the end of the original file, and save it.

It's possible to use other bootloaders here in the same way, but __you need a bootloader__, otherwise you'll have to use ISP again to write new firmware to your keyboard.

## Flashing Your Firmware

Make sure your keyboard is unplugged from any device, and plug in your Teensy.

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

You should see a couple of progress bars, then you should see:

    avrdude: verifying ...
    avrdude: 32768 bytes of flash verified

    avrdude: safemode: Fuses OK

    avrdude done.  Thank you.

Which means everything should be ok! Your board may restart automatically, otherwise, unplug your Teensy and plug in your keyboard - you can leave your Teensy wired to your keyboard while testing things, but it's recommended that you desolder it/remove the wiring once you're sure everything works.

If you have any questions/problems, feel free to [open an issue](https://github.com/qmk/qmk_firmware/issues/new)!
