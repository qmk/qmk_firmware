## READ FIRST
- https://github.com/tmk/tmk_keyboard/blob/master/doc/build.md

In short,

    $ make [-f Makefile.<variant>] [KEYMAP=...] clean
    $ make [-f Makefile.<variant>] [KEYMAP=...]
    $ make [-f Makefile.<variant>] [KEYMAP=...] dfu


## Do 'make clean' before 'make'
You'll need `make clean` after you edit **config.h** or change options like `KEYMAP`.

Frist remove all files made in previous build,

    $ make clean

then build new frimware. 

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