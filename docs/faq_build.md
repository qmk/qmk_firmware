## READ FIRST
- https://github.com/qmk/qmk_firmware/blob/master/docs/build_guide.md

In short,

    $ make [-f Makefile.<variant>] [KEYMAP=...] clean
    $ make [-f Makefile.<variant>] [KEYMAP=...]
    $ make [-f Makefile.<variant>] [KEYMAP=...] dfu


## Can't program on Linux and Mac
You will need proper permission to operate a device. For Linux users see udev rules below.
Easy way is to use `sudo` command, if you are not familiar with this command check its manual with `man sudo` or this page on line.

https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man8/sudo.8.html

In short when your controller is ATMega32u4,
    
    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

or just

    $ sudo make dfu

But to run `make` with root privilege is not good idea. Use former method as possible.

## Do 'make clean' before 'make'
You'll need `make clean` after you edit **config.h** or change options like `KEYMAP`.

Frist remove all files made in previous build,

    $ make clean

then build new firmware. 

    $ make [KEYMAP=...]

Also you can always try `make clean` when you get other strange result during build.


## WINAVR is obsolete
It is no longer recommended and may cause some problem.
See [Issue #99](https://github.com/tmk/tmk_keyboard/issues/99).

## USB stack: LUFA or PJRC?
Use **LUFA**.

**PJRC** stack won't be supported actively anymore. There is no reason to hesitate to use LUFA except for binary size(about 1KB lager?). But **PJRC** is still very useful for debug and development purpose.
See also [Issue #50](https://github.com/tmk/tmk_keyboard/issues/50) and [Issue #58](https://github.com/tmk/tmk_keyboard/issues/58).

## Edit configuration but not change
You will need followings after editing `CONSOLE_ENABLE`, `NKRO_ENABLE`, `EXTRAKEY_ENABLE` or `MOUSEKEY_ENABLE` option in **Makefile**.

### 1. make clean
This will be needed when you edit **config.h**.

### 2. Remove Drivers from Device Manager(Windows)
**Windows only.** Linux, OSX and other OS's doesn't require this. It looks like Windows keeps using driver installed when device was connected first time even after the device changes its configuration. To load proper drivers for new configuration you need to remove existent drivers from **Drvice Manager**.

### 3. Build with different VID:PID
**Windows only.** If method 2. does't work fou you try this. Change Vendor ID or Product ID in **config.h** and build firmware. Windows should recognize it as whole new device and start drivers install process.

### 4. Just try other ports
This will be useful and the easiest workaround for **Windows**.



## USB VID and PID
You can use any ID you want with editing `config.h`. Using any presumably unused ID will be no problem in fact except for very least chance of collision with other product.

For example TMK uses following numbers by default.
```
keyboard:
hhkb: FEED:CAFE
gh60: FEED:6060

converter:
x68k: FEED:6800
ps2: FEED:6512
adb: FEED:0ADB
ibm4704: FEED:4704
pc98: FEED:9898
```

Also see this.
https://github.com/tmk/tmk_keyboard/issues/150

You can buy a really unique VID:PID here. I don't think you need this for personal use.
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1


## Linux udev rules
On Linux you need proper privilege to access device file of MCU, you'll have to use `sudo` when flashing firmware. You can circumvent this with placing these files in `/etc/udev/rules.d/`.

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



## Cortex: cstddef: No such file or directory
GCC 4.8 of Ubuntu 14.04 had this problem and had to update to 4.9 with this PPA.
https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded

https://github.com/tmk/tmk_keyboard/issues/212
https://github.com/tmk/tmk_keyboard/wiki/mbed-cortex-porting#compile-error-cstddef
https://developer.mbed.org/forum/mbed/topic/5205/


## 'clock_prescale_set' and 'clock_div_1' not available
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