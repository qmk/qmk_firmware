Alternative Controller for HHKB Pro
===================================
I wanted to add some features like vi cursor and mouse keys to my [HHKB][HHKB] but its controller is not programmable and
firmware source code is not open, of course. This means customizing this keyboard needs to replace original 
controller with programmable one. This controller can work with HHKB Professional and Professional 2 model.

See [this thread][AltController] in geekhack.org.

[HHKB]: http://www.pfu.fujitsu.com/hhkeyboard/
[AltController]: http://geekhack.org/index.php?topic=12047.0
[Teensy]: http://www.pjrc.com/teensy/


##Features
* Customizable keymap
* More keymap layers(more Fn keys)
* Mouse keys
* USB NKRO

See README of [tmk_keyboard] for more.

[tmk_keyboard]: http://github.com/tmk/tmk_keyboard
 
###Pros
* No risk: Everything is all reversible
* Without PCB trace cutting, case mod or any destructives
* Can keep original controller intact
* Can change all HHKB behaviour as you like

###Cons
* Void your warranty
* Lose USB hub function of Pro2

##DISCLAIMER
I'm not a professional of electronics nor MCU programming. This may damage your HHKB.
And my English writing is poor, I'm not sure I can convey my notions accurately.


##Documents
See [doc/HHKB.txt](doc/HHKB.txt) and files under [doc/](doc/) for internal of HHKB and this controller.


##Build Firmware & Program
You can choose some combination of hardware and USB protocol stack([LUFA], [PJRC]).

### Install Tools
See [this document](../../doc/build.md).

### TMK Alt Controller Board
    $ make -f Makefile.tmk

This programs the controller with [dfu-programmer] if the tool is intalled and configured properly.

    $ make -f Makefile.tmk dfu

Push reset button and program with [FLIP]. The tool should be intalled and configured properly.

    $ make -f Makefile.tmk flip

Or you can also program with FLIP GUI.

[dfu-programmer]: http://dfu-programmer.sourceforge.net/
[FLIP]: http://www.atmel.com/tools/FLIP.aspx


### PJRC Teensy++
Build with [LUFA] USB stack:

    $ make -f Makefile.lufa

or with [PJRC] USB stack:

    $ make -f Makefile.pjrc

Push reset button and program with [Teensy Loader(command line)]. The tool should be intalled and configured properly.

    $  make -f Makefile.lufa teensy
    $  make -f Makefile.pjrc teensy

Or you can also program with [Teensy Loader(GUI)].

[LUFA]: http://www.fourwalledcubicle.com/LUFA.php
[PJRC]: http://www.pjrc.com/teensy/usb_keyboard.html
[Teensy Loader(command line)]: http://www.pjrc.com/teensy/loader_cli.html
[Teensy Loader(GUI)]: http://www.pjrc.com/teensy/loader.html


###AVR Mega with [V-USB]
Build:
    $ make -f Makefile.vusb

Program [USBaspLoader] on MCU with AVR programmer like [AVRISPmkII] and tool like [avrdude].

You can programs with [avrdude] once you have programmed [USBaspLoader] on MCU.
    $  make -f Makefile.vusb program

[AVRISPmkII]: http://www.atmel.com/tools/AVRISPMKII.aspx
[avrdude]: http://www.nongnu.org/avrdude/


##How to Customize
See [tmk_keyboard] documents.


##Hardware
You have some options for hardware. Development boards with USB AVR family(ATMega32U4, AT90USB1286) like Teensy will work while MegaAVR with V-USB library is also cheapear option for DIY.

###1. TMK Alt Controller Board
TMK designed [Keyboard Controller Board for HHKB Pro2(KiCad project)](https://github.com/tmk/HHKB_controller).
See [this post](http://geekhack.org/index.php?topic=12047.msg948923#msg948923).


###2. PJRC Teensy++ 2.0 connection
    +---------------+
    |   Teensy++    |
    |               |
    |               |               HHKB pro    HHKB pro2
    |               |               ~~~~~~~~    ~~~~~~~~~
    |          PB0-2|------->ROW    (6-8)       (5-7)
    |          PB3-5|------->COL    (9-11)      (8-10)
    |            PB6|------->ENABLE (12)        (11)
    |            PE6|<-------KEY    (4)         (3)
    |            PE7|------->PREV   (5)         (4)
    |               |
    |               |   5V---       (1-3)       (1-2)
    |               |  GND---       (13-14)     (12-13)
    +---------------+

- NOTE: PJRC [Teensy](http://www.pjrc.com/teensy/)
[Teensy Loader]: http://www.pjrc.com/teensy/loader.html

###3. V-USB connection
                    +---+   +---------------+
    USB            GND  |   |   ATmega328p  |
    ~~~                 C3  |               |
    5V <-------+--------+---|Vcc,AVCC       |               HHKB pro    pro2
               R1           |               |               ~~~~~~~~    ~~~~
    D- <----+--+-----R2-----|INT1      PB2-4|------->ROW    (6-8)       (5-7)
    D+ <----|---+----R3-----|INT0      PC0-2|------->COL    (9-11)      (8-10)
            Z1  Z2          |            PC3|------->ENABLE (12)        (11)
    GND<----+---+-----------|GND         PB0|<-------KEY    (4)         (3)
                            |            PB1|------->PREV   (5)         (4)
                            |               |
                GND+-C2--+--|XTAL1       RXD|------->Debug Console
                         X1 |            TXD|<-------Debug Console
                GND+-C3--+--|XTAL2       RST|---SW--+GND
                            +---------------+
    R1:     1.5K Ohm
    R2,R3:  68 Ohm
    Z1,Z2:  Zener 3.6V
    C1,C2:  22pF
    C3:     0.1uF
    X1:     Crystal 12MHz
    SW:     Push Switch(for bootloader)

- NOTE: See [V-USB] documentation for more detail of hardware and the USB stack.
- NOTE: [USBaspLoader] is very useful for firmware update.

[V-USB]: http://www.obdev.at/products/vusb/index.html
[USBaspLoader]: http://www.obdev.at/products/vusb/usbasploader.html
