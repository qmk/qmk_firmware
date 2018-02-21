# Frequently Asked Build Questions

This page covers questions about building QMK. If you haven't yet done so, you should read the [Build Environment Setup](getting_started_build_tools.md) and [Make Instructions](getting_started_make_guide.md) guides.

## Can't Program on Linux
You will need proper permissions to operate a device. For Linux users, see the instructions regarding `udev` rules, below. If you have issues with `udev`, a work-around is to use the `sudo` command. If you are not familiar with this command, check its manual with `man sudo` or [see this webpage](https://linux.die.net/man/8/sudo).

An example of using `sudo`, when your controller is ATMega32u4:

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

or just:

    $ sudo make <keyboard>:<keymap>:dfu

Note that running `make` with `sudo` is generally *not* a good idea, and you should use one of the former methods, if possible.

## Linux `udev` Rules
On Linux, you'll need proper privileges to access the MCU. You can either use
`sudo` when flashing firmware, or place these files in `/etc/udev/rules.d/`.

**/etc/udev/rules.d/50-atmel-dfu.rules:**
```
# Atmel ATMega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
# Atmel USBKEY AT90USB1287
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", MODE:="0666"
# Atmel ATMega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", MODE:="0666"
```

**/etc/udev/rules.d/52-tmk-keyboard.rules:**
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```

## WINAVR is Obsolete
It is no longer recommended and may cause some problem.
See [TMK Issue #99](https://github.com/tmk/tmk_keyboard/issues/99).

## USB VID and PID
You can use any ID you want with editing `config.h`. Using any presumably unused ID will be no problem in fact except for very low chance of collision with other product.

Most boards in QMK use `0xFEED` as the vendor ID. You should look through other keyboards to make sure you pick a unique Product ID.

Also see this.
https://github.com/tmk/tmk_keyboard/issues/150

You can buy a really unique VID:PID here. I don't think you need this for personal use.
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

## Cortex: `cstddef: No such file or directory`
GCC 4.8 of Ubuntu 14.04 had this problem and had to update to 4.9 with this PPA.
https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded

https://github.com/tmk/tmk_keyboard/issues/212
https://github.com/tmk/tmk_keyboard/wiki/mbed-cortex-porting#compile-error-cstddef
https://developer.mbed.org/forum/mbed/topic/5205/

## `clock_prescale_set` and `clock_div_1` Not Available
Your toolchain is too old to support the MCU. For example WinAVR 20100110 doesn't support ATMega32u2.

```
Compiling C: ../../tmk_core/protocol/lufa/lufa.c
avr-gcc -c -mmcu=atmega32u2 -gdwarf-2 -DF_CPU=16000000UL -DINTERRUPT_CONTROL_ENDPOINT -DBOOTLOADER_SIZE=4096 -DF_USB=16000000UL -DARCH=ARCH_AVR8 -DUSB_DEVICE_ONLY -DUSE_FLASH_DESCRIPTORS -DUSE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)" -DFIXED_CONTROL_ENDPOINT_SIZE=8  -DFIXED_NUM_CONFIGURATIONS=1 -DPROTOCOL_LUFA -DEXTRAKEY_ENABLE -DCONSOLE_ENABLE -DCOMMAND_ENABLE -DVERSION=unknown -Os -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing -Wall -Wstrict-prototypes -Wa,-adhlns=obj_alps64/protocol/lufa/lufa.lst -I. -I../../tmk_core -I../../tmk_core/protocol/lufa -I../../tmk_core/protocol/lufa/LUFA-git -I../../tmk_core/common -std=gnu99 -include config.h -MMD -MP -MF .dep/obj_alps64_protocol_lufa_lufa.o.d  ../../tmk_core/protocol/lufa/lufa.c -o obj_alps64/protocol/lufa/lufa.o
../../tmk_core/protocol/lufa/lufa.c: In function 'setup_mcu':
../../tmk_core/protocol/lufa/lufa.c:575: warning: implicit declaration of function 'clock_prescale_set'
../../tmk_core/protocol/lufa/lufa.c:575: error: 'clock_div_1' undeclared (first use in this function)
../../tmk_core/protocol/lufa/lufa.c:575: error: (Each undeclared identifier is reported only once
../../tmk_core/protocol/lufa/lufa.c:575: error: for each function it appears in.)
make: *** [obj_alps64/protocol/lufa/lufa.o] Error 1
```


## BOOTLOADER_SIZE for AVR
Note that Teensy2.0++ bootloader size is 2048byte. Some Makefiles may have wrong comment.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 2048
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=2048
```
