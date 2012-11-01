Alternative Controller for HHKB Pro
===================================
I wanted to add some features like vi cursor and mouse keys to my [HHKB][HHKB] but its controller is not programmable and
firmware source code is not open, of course. This means customizing this keyboard needs to replace original 
controller with programmable one. For this purpose I used PJRC [Teensy++][Teensy] as alternative controller.

[HHKB]: http://www.pfu.fujitsu.com/hhkeyboard/
[Teensy]: http://www.pjrc.com/teensy/


My keyboard firmware source tree is here: http://github.com/tmk/tmk_keyboard
See directory keyboard/hhkb to build firmware for HHKB.


##Features
* Customizable keymap
* More keymap layers(more Fn keys)
* Mouse keys
* USB NKRO

###Pros
* Without PCB trace cutting, case mod or any destructives
* Can keep original controller intact
* Can change all HHKB behaviour as you like

###Cons
* Void your warranty
* Lose USB hub function in case of Pro2

##DISCLAIMER
I'm not a professional of electronics or MCU programming. This may damage your HHKB.
And my English writing is poor, I'm not sure I can convey my notions accurately.






##Build Firmware
You can choose some combination of MCU and USB protocol stack.

### Teensy++(AVR USB family) with [LUFA]
0. Edit **matrix.c** to use your pin configuration. See doc/HHKB.txt for detail.

1. Edit **keymap.c** to use your favoirte keymap.

2. Edit **Makefile** if you want to use other `MCU` than Teensy++ 2.0.

3. Build firmware binary file:
    `$ make -f Makefile.lufa`

4. Program MCU with PJRC [Teensy Loader] tool. If you install command line version of the loader just run:
    `$  make -f Makefile.lufa teensy`

[LUFA]: http://www.fourwalledcubicle.com/LUFA.php
[Teensy Loader]: http://www.pjrc.com/teensy/loader.html


###AVR Mega with [V-USB]
Follow below if you want to use AVR with V-USB as .

0. Edit **matrix.c** to use your pin configuration. See doc/HHKB.txt for detail.

1. Edit **keymap.c** to use your favoirte keymap.

2. Edit **usbconfig.h** to configure V-USB options. 

3. Edit **Makefile.vusb** to define `MCU` and `F_CPU`.

4. Build firmware binary file:
    `$ make -f Makefile.vusb`

5. Program MCU with AVR programmer like AVRISPmkII. If you already have [USBaspLoader] on MCU just run:
    `$  make -f Makefile.vusb program`

[V-USB]: http://www.obdev.at/products/vusb/index.html
[USBaspLoader]: http://www.obdev.at/products/vusb/usbasploader.html


###How to Customize Keymap
Later...
See **keymap.c**.


##Hardware

###Teensy++ installation
Angled USB mini B adapter is used to install Teensy++ laterally.
![Teensy install](hhkb/doc/HHKB_img/teensy_install.jpg)

Bread baord wires are used to connect Teensy++.
![Teensy wiring](hhkb/doc/HHKB_img/teensy_wiring.jpg)
![Connector](hhkb/doc/HHKB_img/connector_contact.jpg)


###PJRC Teensy++ 2.0 connection
                            +---------------+
                            |   Teensy++    |
                            |               |
                            |               |        HHKB
                            |               |        ~~~~
                            |          PB0-2|------->ROW(6-8)
                            |          PB3-5|------->COL(9-11)
                            |            PB6|------->ENABLE(12)
                            |            PE6|<-------KEY(4)
                            |            PE7|------->PREV(5)
                            |               |
                            |               |
                            |               |
                            +---------------+


###V-USB circuit
                    +---+   +---------------+
    USB            GND  |   |   ATmega168   |
    ~~~                 C3  |               |
    5V <-------+--------+---|Vcc,AVCC       |        HHKB
               R1           |               |        ~~~~
    D- <----+--+-----R2-----|INT1      PB2-4|------->ROW(6-8)
    D+ <----|---+----R3-----|INT0      PC0-2|------->COL(9-11)
            Z1  Z2          |            PC3|------->ENABLE(12)
    GND<----+---+-----------|GND         PB0|<-------KEY(4)
                            |            PB1|------->PREV(5)
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
    X1:     Crystal 20MHz(16MHz/12MHz)
    SW:     Push Switch(Optional for bootloader)
