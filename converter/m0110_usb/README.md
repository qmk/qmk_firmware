M0110/M0110A to USB keyboard converter
======================================
This firmware converts the protocol of Apple Macintosh keyboard **M0110**, **M0110A** and **M0120** into USB. Target of this project is USB AVR controller **ATmega32U4**. Using this converter you can revive these retro keyboards with modern computer.

Pictures of **M0110 + M0120** and **M0110A**.

![M0110+M0120](http://i.imgur.com/dyvXb2Tm.jpg)
![M0110A](http://i.imgur.com/HuHOEoHm.jpg)


- M0110A support was contributed by [skagon@github](https://github.com/skagon).
- M0120 also is supported. keys(+ * / and ,) on M0120 are recognized as cursor keys.



Update
------
- 2013/08: Change port for signals `PF` to `PD`
- 2013/09: Change port again, it uses inversely `PD0` for data and `PD1` for clock line now.



Building Hardware
-----------------
You need **4P4C** cable and **ATMega32U4** board like PJRC [Teensy]. Port of the MCU `PD1` is assigned to `CLOCK` line and `PD0` to `DATA` by default, you can change pin configuration with editing `config.h`.

[![M0110 Converter](http://i.imgur.com/4G2ZOegm.jpg)](http://i.imgur.com/4G2ZOeg.jpg)

### 4P4C phone handset cable
Note that original cable used with Mac is **straight** while phone handset cable is **crossover**.

<http://en.wikipedia.org/wiki/Modular_connector#4P4C>

Close-up picture of handset cable. You can see one end of plug has reverse color codes against the other. Click to enlarge.
[![4P4C cable](http://i.imgur.com/3S9P1mYm.jpg?1)](http://i.imgur.com/3S9P1mY.jpg?1)

[Teensy]: http://www.pjrc.com/teensy/


### Socket Pinout
- <http://pinouts.ru/Inputs/MacKeyboard_pinout.shtml>

![Jack fig](http://www.kbdbabel.org/conn/kbd_connector_macplus.png)


### Pull-up Resistor
You may need pull-up resistors on signal lines(`CLOCK`, `DATA`) in particular when you have long or coiled cable. **1k-10k Ohm** will be OK for this purpose. In that case the converter may not read signal from keyboard correctly without pull-up resistors.



Building Firmware
-----------------
To compile firmware you need AVR GCC. You can edit *Makefile* and *config.h* to change compile options and pin configuration.

    $ git clone git://github.com/tmk/tmk_keyboard.git (or download source)
    $ cd m0110_usb
    $ make -f Makefile clean
    $ make -f Makefile

and program your Teensy with [PJRC Teensy loader](http://www.pjrc.com/teensy/loader.html).



Keymap
------
You can change keymaps by editing *keymap.c*.

### M0110 & M0120
#### *Default Layer*
    ,---------------------------------------------------------.     ,---------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs|     |Clr|  -|Lft|Rgt|
    |---------------------------------------------------------|     |---------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \|     |  7|  8|  9| Up|
    |---------------------------------------------------------|     |---------------|
    |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter |     |  4|  5|  6| Dn|
    |---------------------------------------------------------|     |---------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift   |     |  1|  2|  3|   |
    `---------------------------------------------------------'     |-----------|Ent|
         |Ctl|Gui |         Space               |Alt |Ctl|          |      0|  .|   |
         `-----------------------------------------------'          `---------------'

- `Space` and  `Enter` also work as `Fn` layer switch key when holding down.

#### *Function Layer(WASD/HHKB)*
    ,---------------------------------------------------------.     ,---------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet|     |Nlk|  -|Lft|Rgt|
    |---------------------------------------------------------|     |---------------|
    |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |Ins|  \|     |  7|  8|  9| Up|
    |---------------------------------------------------------|     |---------------|
    |Caps  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Enter |     |  4|  5|  6| Dn|
    |---------------------------------------------------------|     |---------------|
    |Shift   |End|   |PgD|   |   |   |   |End|PgD|Dow|Shift   |     |  1|  2|  3|   |
    `---------------------------------------------------------'     |-----------|Ent|
         |Ctl|Gui |         Space               |Alt |Ctl|          |      0|  .|   |
         `-----------------------------------------------'          `---------------'


### M0110A
#### *Default Layer*
    ,---------------------------------------------------------. ,---------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Clr|  =|  /|  *|
    |---------------------------------------------------------| |---------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
    |-----------------------------------------------------'   | |---------------|
    |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter | |  4|  5|  6|  +|
    |---------------------------------------------------------| |---------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft| Up| |  1|  2|  3|   |
    |---------------------------------------------------------| |-----------|Ent|
    |Ctrl |Gui    |         Space             |  \|Lft|Rgt|Dwn| |      0|  .|   |
    `---------------------------------------------------------' `---------------'

- `Space` and  `Enter` also work as `Fn` layer switch key when holding down.
- `Backslash(\)` also works as `Alt` when holding down.

#### *Function Layer(WASD/HHKB)*
    ,---------------------------------------------------------. ,---------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
    |---------------------------------------------------------| |---------------|
    |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |Ins|   | |  7|  8|  9|  -|
    |-----------------------------------------------------'   | |---------------|
    |Caps  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Enter | |  4|  5|  6|  +|
    |---------------------------------------------------------| |---------------|
    |Shift   |End|   |PgD|   |   |   |   |End|PgD|Dow|Shif|PgU| |  1|  2|  3|   |
    |---------------------------------------------------------| |-----------|Ent|
    |Ctrl |Gui    |         Space             |  \|Hom|End|PgD| |      0|  .|   |
    `---------------------------------------------------------' `---------------'



Debug
-----
You can use [PJRC HID listen](http://www.pjrc.com/teensy/hid_listen.html) to see debug output. The converter has some functions for debug, press `<Command>+H` simultaneously to get help.

- Command: `Shift+Option+Command`(`Shift+Alt+Gui` or `Shift+Alt+Control`)
