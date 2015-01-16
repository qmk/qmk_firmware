Alternative Controller for HHKB Pro
===================================
I wanted to add some features like vi cursor and mouse keys to my [HHKB][HHKB] but its controller is not programmable and firmware source code is not open, of course. This means customizing this keyboard needs to replace original controller with programmable one.

This controller can work with HHKB **Professional**, **Professional** 2, **JP** and **Type-S**.

See [this thread][AltController] in geekhack.org.

[HHKB]: http://www.pfu.fujitsu.com/hhkeyboard/
[AltController]: http://geekhack.org/index.php?topic=12047.0


## Update
* Bluetooth module RN-42 is supported.(2015/01)
* V-USB and iWRAP are no longer supported now, but still it'll works with a little fix. See not_supported directory.(2015/01)


##Features
* Customizable keymap
* More keymap layers(more Fn keys)
* Mouse keys
* USB NKRO
* Bluetooth(RN-42)

See README of [tmk_keyboard] for more.

[tmk_keyboard]: http://github.com/tmk/tmk_keyboard
 
###Pros
* No risks: Everything is all reversible
* No need for PCB trace patching, case cutting or any other destructive mod
* Can keep original controller intact
* Can change all HHKB behavior as you like

###Cons
* Void your warranty
* Lose USB hub function of Pro2

##DISCLAIMER
I'm not a professional of electronics nor MCU programming. This may damage your HHKB.
And my English writing is poor, I'm not sure I can convey my notions accurately.


##Documents
See [doc/HHKB.txt](doc/HHKB.txt) and files under [doc/](doc/) for internal of HHKB and this controller.


##Build Firmware & Program
See [this document](../../doc/build.md) first.

### Configuration
If your target is **HHKB JP** you need to set `HHKB_JP` build option in `Makefile` or use `Makefile.jp` instead of `Makefile`.

If you use other than **TMK Alt Controller Board** set proper `MCU`, `BOOTLOADER_SIZE` and other build options in `Makefile` and `config.h`. At least PJRC Teensy requires changing `BOOTLOADER_SIZE` to 512.

### Build 
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. Just `make` with `KEYMAP` option like:

    $ make -f Makefile.<jp|pjrc|rn42> KEYMAP=(hasu|hhkb|spacefn|<name>)

You can omit `-f` option when you use `Makefile`. `Makefile` is used for **Pro2 and Pro**, `Makefile.jp` fits for **JP** model and `Makefile.rn42` supports Bluetooth module **RN-42**. `Makefile.pjrc` uses **PJRC** as output protocol instead of **LUFA**.


### Program
First, push reset button on board to start bootloader.

This command programs the controller with [dfu-programmer] if the tool is installed and configured properly.

    $ make -f Makefile.<variant> KEYMAP=<name> dfu

Or you can also use [FLIP] command to program. Also the tool should be installed and configured properly. FLIP GUI application is also available.

    $ make -f Makefile.<variant> KEYMAP=<name> flip

Use [Teensy Loader] if your controller is Teensy/Teensy++.


##Keymap
To define your own keymap create file named `keymap_<name>.c` and see [keymap document](../../doc/keymap.md) and existent keymap files.


##Hardware
You have some options for hardware. Development boards with USB AVR family(ATMega32U4, AT90USB1286) like Teensy will work while MegaAVR with [V-USB] library is also cheaper option for DIY.

###1. TMK Alt Controller Board
Design files are available at [Keyboard Controller Board for HHKB(KiCad project)](https://github.com/tmk/HHKB_controller) and see [Controller Distribution thread](http://geekhack.org/index.php?topic=56494.0) if you get an assembled one.


###2. PJRC Teensy
See [this thread](http://geekhack.org/index.php?topic=57008.0).


###3. V-USB version
See [V-USB controller for HHKB](doc/V-USB.md).


[LUFA]: http://www.fourwalledcubicle.com/LUFA.php
[PJRC]: http://www.pjrc.com/teensy/usb_keyboard.html
[dfu-programmer]: http://dfu-programmer.sourceforge.net/
[FLIP]: http://www.atmel.com/tools/FLIP.aspx
[Teensy Loader]: http://www.pjrc.com/teensy/loader.html
[V-USB]: http://www.obdev.at/products/vusb/index.html
