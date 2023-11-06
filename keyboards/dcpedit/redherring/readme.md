# Red Herring Firmware
This branch contains OLED drivers for the SH/SSD1107 display from:
https://github.com/qmk/qmk_firmware/compare/master...sigprof:oled-driver-new-hardware-support-v2 

## Vial:

Build Vial firmware:

`make dcpedit/redherring:vial`

Use Vial software to set keymap and rotary encoder:
https://get.vial.today/
    
## Bootloader
https://github.com/coseyfannitutti/discipline/tree/master/doc/bootloader

[QMK's ISP Flashing Guide](https://github.com/qmk/qmk_firmware/blob/master/docs/isp_flashing_guide.md)

Edit Makefile.inc and replace the `/dev/tty.usbmodem123451` with the path QMK Toolbox displays when you plug in your AVR-ISP programmer:

`PROGRAMMER = -c avrisp -P /dev/tty.usbmodem123451`

### Commands

`make` (build)

`make flash` (flashes makefile)

`make fuse` (sets fuses for microcontroller)


The usbasploader build available on [hsgw's repository](https://github.com/hsgw/USBaspLoader/tree/plaid) will work if you need to flash a new and unprepared replacement microcontroller. To flash this onto your fresh microcontroller, you will need to use the provided ISP headers and an external ISP programmer.

In order to put the board into bootloader mode you must first hold the boot button (labeled BOOT) and while holding the boot button, press the reset button (labeled RESET) and release it. Wait for another second, then release the boot button as well. The microcontroller will now be in bootloader mode if the bootloader is present and prepared correctly. Continue to flash as you normally would from this point (ie. QMK Toolbox). If you have autoflash enabled on QMK Toolbox, it will do it automatically now. Reset the board once more in order to use the new firmware (you can do this by unplugging and replugging it or by pressing and releasing the reset button.)

By default, keyboard firmware has bootmagic enabled (lite). This means that instead of holding or pressing either of the small buttons, you are able to unplug the keyboard, hold the F1 key, plug the keyboard back in, and then release the F1. This will work the same to put the keyboard into bootloader mode. For more information, see the [bootmagic feature page](https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_bootmagic). Reset the board once more in order to use the new firmware (you can do this by unplugging and replugging it or by pressing and releasing the reset button.)



See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
