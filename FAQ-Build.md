# FAQ/Build

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
Try these.
### 1. make clean
This will be needed when you edit **config.h**.

### 2. Remove Drivers from Device Manager(Windows)
Windows only. Linux, OSX and other OS's doesn't require this. It looks like Windows keeps using driver installed when device was connected first time even after the device changes its configuration. To load proper drivers for new configuration you need to remove existent drivers from **Drvice Manager**.

You will need this after editing `CONSOLE_ENABLE`, `NKRO_ENABLE`, `EXTRAKEY_ENABLE` or `MOUSEKEY_ENABLE` option in **Makefile**.


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