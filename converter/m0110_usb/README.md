M0110/M0110A to USB keyboard converter
======================================
This firmware converts the protocol of Apple Macintosh keyboard **M0110**, **M0110A** and **M0120** into USB. Target of this project is USB AVR controller like **ATmega32U2** and **ATmega32U4**. Using this converter you can revive these retro keyboards with modern computer.

Read README of top directory too.

Pictures of **M0110 + M0120** and **M0110A**.

![M0110+M0120](http://i.imgur.com/dyvXb2Tm.jpg)
![M0110A](http://i.imgur.com/HuHOEoHm.jpg)


- M0110A support was contributed by [skagon@github](https://github.com/skagon).
- M0120 also is supported. keys(+ * / and ,) on M0120 are recognized as cursor keys.



Update
------
- 2013/08: Change port for signals `PF` to `PD`
- 2013/09: Change port again, it uses inversely `PD0` for data and `PD1` for clock line now.
- 2014/06: Change keymaps
- 2015/03: Add support for "International"(ISO) keyboard(keymap_intl.c)



Building Hardware
-----------------
You need [TMK converter] or AVR dev board like PJRC [Teensy]. Port of the MCU `PD1` is assigned to `CLOCK` line and `PD0` to `DATA` by default, you can change pin configuration with editing `config.h`.

[![M0110 Converter](http://i.imgur.com/4G2ZOegm.jpg)](http://i.imgur.com/4G2ZOeg.jpg)

### 4P4C phone handset cable
Note that original cable used with Mac is **straight** while phone handset cable is **crossover**.

<http://en.wikipedia.org/wiki/Modular_connector#4P4C>

Close-up picture of handset cable. You can see one end of plug has reverse color codes against the other. Click to enlarge.
[![4P4C cable](http://i.imgur.com/3S9P1mYm.jpg?1)](http://i.imgur.com/3S9P1mY.jpg?1)

[Teensy]: http://www.pjrc.com/teensy/
[TMK converter]: https://github.com/tmk/keyboard_converter


### Socket Pinout
- <http://pinouts.ru/Inputs/MacKeyboard_pinout.shtml>

![Jack fig](http://www.kbdbabel.org/conn/kbd_connector_macplus.png)


### Pull-up Resistor
You may need pull-up resistors on signal lines(`CLOCK`, `DATA`) in particular when you have long or coiled cable. **1k-10k Ohm** will be OK for this purpose. In that case the converter may not read signal from keyboard correctly without pull-up resistors.



Building Firmware
-----------------
To compile firmware you need AVR GCC. You can edit *Makefile* and *config.h* to change compile options and pin configuration. Also `KEYMAP` option can be used to select keymap.

    $ git clone git://github.com/tmk/tmk_keyboard.git (or download source)
    $ cd m0110_usb
    $ make -f Makefile clean
    $ make -f Makefile [KEYMAP={default|plain|intl|spacefn|hasu}]

Use `Makefile.teensy` instead for Teensy.



Keymap
------
To create your own keymap copy existent keymap file to `keymap_name.c` and edit it. You can build it like this.

    $ make -f Makefile clean
    $ make -f Makefile KEYMAP=name



Debug
-----
You can use [PJRC HID listen](http://www.pjrc.com/teensy/hid_listen.html) to see debug output. The converter has some functions for debug, press `<Magic>+H` simultaneously to get help.

- Magic combo: `Shift+Option+⌘` or `Shift+Option+Ctrl`(`Shift+Alt+Gui` or `Shift+Alt+Control`)
