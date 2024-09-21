# Xiaomi Yuemi Pro MK02

A tenkeyless keyboard sold under Xiaomi brand. It uses an STM32F072C8T6 microcontroller and can be flashed with QMK.

LED backlight is currently not supported.

* Keyboard Maintainer: [@xyzz](https://github.com/xyzz)
* Hardware Supported: Xiaomi Yuemi Pro MK02
* Hardware Availability: Aliexpress

Make example for this keyboard (after setting up your build environment):

    make xiaomi/mk02:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Installation

Please understand that following these steps will void your warranty and might irrecoverably damage your keyboard.

### Installing the bootloader

You only need to do this step once (unless you destroy your user bootloader which is not possible so long as you follow these steps correctly).

Unplug the keyboard. Disassemble the keyboard and look at the area around the MCU. Make sure your keyboard looks the same as in the picture and that the chip says STM32F072C8T6 on it:

![mcu](https://i.imgur.com/HM8tUWU.jpg)

Using a piece of wire, connect TP28 (indicated in red) and 3v3 (square pad indicated in green) together with tweezers or a piece of wire. Make sure to not touch the case with your wire when shorting!!! Don't push it all the way through the hole.

Plug the keyboard in with the wire connected. You should see the following device appear:
```
[5067851.560317] usb 2-1.5.3.1: new full-speed USB device number 6 using ehci-pci
[5067851.670006] usb 2-1.5.3.1: New USB device found, idVendor=0483, idProduct=df11, bcdDevice=22.00
[5067851.670010] usb 2-1.5.3.1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[5067851.670013] usb 2-1.5.3.1: Product: STM32  BOOTLOADER
[5067851.670015] usb 2-1.5.3.1: Manufacturer: STMicroelectronics
[5067851.670017] usb 2-1.5.3.1: SerialNumber: FFFFFFFEFFFF
```

If you don't see this, you did something wrong. Disconnect the keyboard and try again.

If you do see this, remove the wire before continuing.

Make a backup of internal flash memory in case you'd like to revert to the original firmware in the future:
```
dfu-util -d 0483:df11 -a 0 -s 0x08000000 -U flash-backup.bin
```

Ensure the dumped flash is correct:
```
strings flash.bin | grep KB
```
(You should see 2 entries of "USB KB")

Finally, flash the bootloader ([jumploader-xiaomi_mk02-padded.bin](https://github.com/xyzz/stm32f072-keyboard-jumploader/releases/download/r1/jumploader-xiaomi_mk02-padded.bin)) with:
```
dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D jumploader-xiaomi_mk02-padded.bin
```

At this point the keyboard should reboot into bootloader mode; if it doesn't, wait a couple seconds and replug the USB cable.

### Installing the firmware

To install QMK, first boot into bootloader mode as detailed below. When the keyboard boots in bootloader mode, you should see the following device:

```
[5067851.560317] usb 2-1.5.3.1: new full-speed USB device number 6 using ehci-pci
[5067851.670006] usb 2-1.5.3.1: New USB device found, idVendor=0483, idProduct=df11, bcdDevice=22.00
[5067851.670010] usb 2-1.5.3.1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[5067851.670013] usb 2-1.5.3.1: Product: STM32  BOOTLOADER
[5067851.670015] usb 2-1.5.3.1: Manufacturer: STMicroelectronics
[5067851.670017] usb 2-1.5.3.1: SerialNumber: FFFFFFFEFFFF
```

Flash the keyboard normally by executing:

```
make xiaomi/mk02:default:flash
```

Warning! If you flash the firmware manually by using `dfu-util`, make sure to use the following arguments:

```
-d 0483:df11 -a 0 -s 0x08002000:leave
```

If you don't, you'll blow away the user bootloader and will have to repeat the installation steps.

## Booting into bootloader

To boot into bootloader, do either of the following:
- map a RESET key in your keymap and tap it, or
- hold spacebar while plugging in the keyboard.

If neither of these work, you must have blown away the user bootloader somehow and will need to repeat the installation guide from the first step.

## Restoring the original firmware

If you wish to restore the original firmware, boot into the bootloader and then execute:

```
dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D flash-backup.bin
```
