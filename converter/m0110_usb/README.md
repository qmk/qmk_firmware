M0110/M0110A to USB keyboard converter
======================================
This firmware converts the protocol of Apple Macintosh keyboard M0110/M0110A into USB.
Target board of this project is [PJRC Teensy](http://www.pjrc.com/teensy/), though,
you can use other board with USB AVR like `ATmega32U4` and `AT90USB`.

![M0110](https://github.com/tmk/tmk_keyboard/raw/master/m0110_usb/doc/m0110.jpg)

M0110A support was contributed by [skagon@github](https://github.com/skagon).



Connection
----------
You need 4P4C plug and cable to connect Teensy or other AVR dev board into the keyboard.
Teensy port `PF0` is assigned for `CLOCK` line and `PF1` for `DATA` by default,
you can change pin configuration with editing *config.h*.

You can find 4P4C plugs on telephone handset cable. Note that it is *crossover* connection
while Macintosh keyboard cable is *straight*.

[![Conection](http://i.imgur.com/vJoVOm.jpg)](http://i.imgur.com/vJoVO.jpg)

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
    $ make

and program your Teensy with [PJRC Teensy loader](http://www.pjrc.com/teensy/loader.html).



Keymap
------
You can change keymaps by editing *keymap.c*.

### M0110
#### *Default*
    ,---------------------------------------------------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs|
    |---------------------------------------------------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \|
    |---------------------------------------------------------|
    |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return|
    |---------------------------------------------------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift   |
    `---------------------------------------------------------'
         |Ctr|Alt |         Space               |Gui |Ctr|
         `-----------------------------------------------'
#### *HHKB/WASD Layer*
    ,---------------------------------------------------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet|
    |---------------------------------------------------------|
    |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |   |Ins|
    |---------------------------------------------------------|
    |Fn0   |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return|
    |---------------------------------------------------------|
    |Shift   |End|   |PgD|   |VoD|VoU|Mut|End|PgD|Dow|Shift   |
    `---------------------------------------------------------'
         |Ctr|Alt |         Space               |Gui |Ctr|
         `-----------------------------------------------'

### M0110A
#### *Default*
    ,---------------------------------------------------------. ,---------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Gui|  =|  /|  *|
    |---------------------------------------------------------| |---------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
    |-----------------------------------------------------'   | |---------------|
    |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
    |---------------------------------------------------------| |---------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft|Up | |  1|  2|  3|   |
    |---------------------------------------------------------| |-----------|Ent|
    |Ctrl |Alt    |         Space             |  \|Lft|Rgt|Dn | |      0|  .|   |
    `---------------------------------------------------------' `---------------'
#### *HHKB/WASD/mousekey  Layer*
    ,---------------------------------------------------------. ,---------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|Mb1|Mb3|Mb2|
    |---------------------------------------------------------| |---------------|
    |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |   |   | |MwD|McU|MwU|MwU|
    |-----------------------------------------------------'   | |---------------|
    |Fn0   |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return| |McL|McD|McR|MwD|
    |---------------------------------------------------------| |---------------|
    |Shift   |End|   |PgD|   |VoD|VoU|Mut|End|PgD|Dow|Shif|Up | |MwL|McD|MwR|   |
    |---------------------------------------------------------| |-----------|Mb2|
    |Ctrl |Alt    |         Space             |Ins|Lft|Rgt|Dn | |    Mb1|Mb3|   |
    `---------------------------------------------------------' `---------------'



Debug
-----
You can use [PJRC HID listen](http://www.pjrc.com/teensy/hid_listen.html) to see debug output.

The converter has some functions for debug, press `<magickey>+H` simultaneously to get help.
These function is totally undocumented, tentative, inconsistent and buggy.

magickey: Shift+Option+Command(Shift+Alt+Gui or Shift+Alt+Control)
