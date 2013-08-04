M0110/M0110A to USB keyboard converter
======================================
This firmware converts the protocol of Apple Macintosh keyboard M0110/M0110A into USB.
Target board of this project is [PJRC Teensy](http://www.pjrc.com/teensy/), though,
you can use other board with USB AVR like `ATmega32U4` and `AT90USB`.

![M0110](https://raw.github.com/tmk/tmk_keyboard/master/converter/m0110_usb/doc/m0110.jpg)

- M0110A support was contributed by [skagon@github](https://github.com/skagon).
- M0120 also is supported. keys(+ * / and ,) on M0120 are recognized as cursor keys.



Update
------
- 2013/08   Change port for signals PF to PD



Connection
----------
You need 4P4C plug and cable to connect Teensy or other AVR dev board into the keyboard.
Teensy port `PD0` is assigned for `CLOCK` line and `PD1` for `DATA` by default,
you can change pin configuration with editing *config.h*.

You can find 4P4C plugs on telephone handset cable. Note that it is *crossover* connection
while Macintosh keyboard cable is *straight*.

[![Conection](https://raw.github.com/tmk/tmk_keyboard/master/converter/m0110_usb/doc/teensy.jpg)]

In this pic:

1. `GND`(Black)
2. `CLOCK`(Red)
3. `DATA`(Green)
4. `+5V`(Yellow)

Note that wire colors may vary in your cable.


### Pinout
- <http://pinouts.ru/Inputs/MacKeyboard_pinout.shtml>
- <http://en.wikipedia.org/wiki/Modular_connector#4P4C>

![Jack fig](http://www.kbdbabel.org/conn/kbd_connector_macplus.png)


### Pull-up Registor
You may need pull-up registors on signal lines(`CLOCK`, `DATA`) in particular
when you have long or coiled cable. 1k-10k Ohm will be OK for this purpose.
In some cases MCU can't read signal from keyboard correctly without pull-up resistors.



Building Frimware
-----------------
To compile firmware you need AVR GCC. You can use [WinAVR](http://winavr.sourceforge.net/) on Windows.
You can edit *Makefile* and *config.h* to change compile options and pin configuration.

    $ git clone git://github.com/tmk/tmk_keyboard.git (or download source)
    $ cd m0110_usb
    $ make -f Makefile clean
    $ make -f Makefile

and program your Teensy with [PJRC Teensy loader](http://www.pjrc.com/teensy/loader.html).



Keymap
------
You can change keymaps by editing *keymap.c*.

### M0110 & M0120
#### *Default*
    ,---------------------------------------------------------. ,---------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Ctl|  -|Lft|Rgt|
    |---------------------------------------------------------| |---------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \| |  7|  8|  9| Up|
    |---------------------------------------------------------| |---------------|
    |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6| Dn|
    |---------------------------------------------------------| |---------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift   | |  1|  2|  3|   |
    `---------------------------------------------------------' |-----------|Ent|
         |Ctl|Alt |         Space               |Gui |Ctl|      |      0|  .|   |
         `-----------------------------------------------'      `---------------'
#### *HHKB/WASD Layer(WASD/IJKL)*
    ,---------------------------------------------------------. ,---------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  -|Lft|Rgt|
    |---------------------------------------------------------| |---------------|
    |Caps |Hom| Up|PgU|   |   |   |PgU| Up|Hom|Psc|Slk|Pau|Ins| |  7|  8|  9| Up|
    |---------------------------------------------------------| |---------------|
    |Fn0   |Lef|Dow|Rig|   |   |   |Lef|Dow|Rig|   |   |Return| |  4|  5|  6| Dn|
    |---------------------------------------------------------| |---------------|
    |Shift   |End|   |PgD|   |   |   |PgD|   |End|   |Shift   | |  1|  2|  3|   |
    `---------------------------------------------------------' |-----------|Ent|
         |Ctl|Alt |         Space               |Gui |Ctl|      |      0|  .|   |
         `-----------------------------------------------'      `---------------'

### M0110A
#### *Default*
    ,---------------------------------------------------------. ,---------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Ctl|  =|  /|  *|
    |---------------------------------------------------------| |---------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
    |-----------------------------------------------------'   | |---------------|
    |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
    |---------------------------------------------------------| |---------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft| Up| |  1|  2|  3|   |
    |---------------------------------------------------------| |-----------|Ent|
    |Alt  |Gui    |         Space             |  \|Lft|Rgt| Dn| |      0|  .|   |
    `---------------------------------------------------------' `---------------'
#### *Cursor  Layer(WASD/IJKL)*
    ,---------------------------------------------------------. ,---------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
    |---------------------------------------------------------| |---------------|
    |Caps |Hom| Up|PgU|   |   |   |PgU| Up|Hom|Psc|Slk|Pau|   | |  7|  8|  9|  -|
    |-----------------------------------------------------'   | |---------------|
    |Fn0   |Lef|Dow|Rig|   |   |   |Lef|Dow|Rig|   |   |Return| |  4|  5|  6|  +|
    |---------------------------------------------------------| |---------------|
    |Shift   |End|   |PgD|   |   |   |PgD|   |End|   |Shif|PgU| |  1|  2|  3|   |
    |---------------------------------------------------------| |-----------|Ent|
    |Alt  |Gui    |         Space             |Ins|Hom|End|PgD| |      0|  .|   |
    `---------------------------------------------------------' `---------------'



Debug
-----
You can use [PJRC HID listen](http://www.pjrc.com/teensy/hid_listen.html) to see debug output.

The converter has some functions for debug, press `<magickey>+H` simultaneously to get help.
These function is totally undocumented, tentative, inconsistent and buggy.

magickey: Shift+Option+Command(Shift+Alt+Gui or Shift+Alt+Control)
