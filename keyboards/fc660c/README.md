FC660C Alt Controller
=================

This file and the entire QMK port of this board are based on its TMK implementation: https://github.com/tmk/tmk_keyboard/tree/master/keyboard/fc980c

------------

- Keyboard Maintainer: [Balz Guenat](https://github.com/BalzGuenat)
- Hardware Supported: Hasu's Alt Controller (see below)
- Hardware Availability: https://geekhack.org/index.php?topic=90317.0

Make example for this keyboard (after setting up your build environment):

    make fc660c:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

To flash the firmware, press the reset button on the controller and run:

    sudo make fc660c:default:dfu

--------

Thread on Geekhack: https://geekhack.org/index.php?topic=88439.0

Also: https://geekhack.org/index.php?topic=88720.0


Actuation Point adjustment
--------------------------
You can adjust the actuation point of the keys by setting `ACTUATION_DEPTH_ADJUSTMENT` in `config.h`.
A value above 0 will result in a deeper, less sensitive actuation whereas a value above 1 will result in a more shallow, more sensitive actuation.
Be careful with this setting and use small values (+/-5).
See the `actuation-point-example` keymap of the `fc980c` keyboard for an example.
For more information, inspect the `fc660c_i2c` branch of TMK [here](https://github.com/tmk/tmk_keyboard/tree/fc660c_i2c).
Functionality for writing to the EEPROM has deliberately not been included to reduce the chance of people messing up their boards.


Pinouts
-------

    |Switch  |Controller |
    |  board |     board |Description                           |Schematic  |ATmega32u4
    |--------|-----------|--------------------------------------|-----------|------------
    | 1      |20         | FG                                   |FG         |GND
    | 2      |19         | GND                                  |GND        |GND
    | 3      |18         | GND                                  |GND        |GND
    | 4      |17         | 3.3V                                 |V33        |3.3V/5V
    | 5      |16         | 5V                                   |Vcc        |5V
    | 6      |15         |*Z6-TP1684-4-HYS(o)                   |FBSTB      |PC7
    | 7      |14         |*Z6-TP1684-2-KEY(i)                   |OUT        |PC6
    | 8      |13         |*Z2-AD5258-5-SCL(I2C)                 |SCL        |PD0(TWI)
    | 9      |12         |*Z2-AD5258-4-SDA(I2C)                 |SDA        |PD1(TWI)
    |10      |11         |*Z4-LV4051A-6-~EN(Col 0-7)            |INH_1      |PB4
    |11      |10         |*Z5-LV4051A-6-~EN(Col 8-F)            |INH_2      |PB3
    |12      | 9         |+Z7-LV07A-5 (LV4051A-9-C)             |SEL_C      |PB2
    |13      | 8         |+Z7-LV07A-1 (LV4051A-10-B)            |SEL_B      |PB1
    |14      | 7         |+Z7-LV07A-3 (LV4051A-11-A)            |SEL_A      |PB0
    |15      | 6         |+Z3-LVC138A-3-C                       |COL4       |PD6
    |16      | 5         |+Z3-LVC138A-2-B                       |COL3       |PD5
    |17      | 4         |+Z3-LVC138A-1-A                       |COL2       |PD4
    |18      | 3         |+Z3-LVC138A-4-~G2A  Z6-TP1684-5-~EN   |COL1       |PD7
    |19      | 2         |+Z7-LV07A-11-~InsertLED               |LED1       |PB5
    |20      | 1         |+Z7-LV07A-13-~CapsLED                 |LED2       |PB6

```
* 5V intferface
+ 3.3V interface
```

- Connector on Switch board: https://i.imgur.com/Zi89xO5.jpg
- Connector on Controller board: https://i.imgur.com/9SZUzYo.jpg


Key Matrix
----------
Row5-7 have no key, you can omit scaning on those lines. Topre original controller scans those rows for some reason.

    |    |0   |1   |2   |3   |4   |5   |6   |7   |8   |9   |A   |B   |C   |D   |E   |F   |
    |----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
    |   0|Q   |W   |E   |Tab |R   |U   |T   |Y   |O   |P   |[   |I   |]   |    |\   |Del |
    |   1|1   |2   |3   |Esc |4   |7   |5   |6   |9   |0   |-   |8   |=   |    |BSpc|Ins |
    |   2|    |LWin|LAlt|LCtl|    |    |    |Spc |RAlt|    |RCtl|    |Fn  |Down|Left|Rght|
    |   3|    |Z   |X   |LSft|C   |N   |V   |B   |,   |.   |/   |M   |RSft|Up  |    |    |
    |   4|A   |S   |D   |Caps|F   |J   |G   |H   |L   |;   |'   |K   |    |    |Entr|    |
    |   5|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
    |   6|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
    |   7|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |

Logic analyzer pics:
- http://i.imgur.com/9XoNTev.png
- https://i.imgur.com/5FCP1Ay.png

This code emuluates what original cotnroller does for matrix scan.
- https://github.com/tmk/tmk_keyboard/blob/master/keyboard/fc660c/fc660c.c


### Row designation
LV138A(Z3) selects a row line and gives strobe by enabling with ~G2A(18).

    |Row |A/17|B/16|C/15|
    |----|----|----|----|
    |0   |0   |0   |0   |
    |1   |1   |0   |0   |
    |2   |0   |1   |0   |
    |3   |1   |1   |0   |
    |4   |0   |0   |1   |
    |5   |1   |0   |1   |
    |6   |0   |1   |1   |
    |7   |1   |1   |1   |


### Column designation
LV4051A(Z4, Z5) select one of 16 column lines to sense capacitance of switches.

    |Col |A/14|B/13|C/12|Z4-EN/10|Z5-EN/11|
    |----|----|----|----|--------|--------|
    |0   |0   |0   |0   |0       |1       |
    |1   |1   |0   |0   |0       |1       |
    |2   |0   |1   |0   |0       |1       |
    |3   |1   |1   |0   |0       |1       |
    |4   |0   |0   |1   |0       |1       |
    |5   |1   |0   |1   |0       |1       |
    |6   |0   |1   |1   |0       |1       |
    |7   |1   |1   |1   |0       |1       |
    |8   |0   |0   |0   |1       |0       |
    |9   |1   |0   |0   |1       |0       |
    |A   |0   |1   |0   |1       |0       |
    |B   |1   |1   |0   |1       |0       |
    |C   |0   |0   |1   |1       |0       |
    |D   |1   |0   |1   |1       |0       |
    |E   |0   |1   |1   |1       |0       |
    |F   |1   |1   |1   |1       |0       |


FCC documents
-------------
https://fccid.io/RPKFC660C

- schematic: https://fccid.io/pdf.php?id=1888185
- part list: https://fccid.io/pdf.php?id=1888184


Datasheets
----------
- Hirose DF14A-20P-1.25H: http://www.mouser.com/ds/2/185/DF14_catalog-939195.pdf
- LV07A: http://www.ti.com/lit/ds/symlink/sn74lv07a.pdf
- LV138A: http://www.ti.com/lit/ds/symlink/sn74lvc138a.pdf
- LV4051A: http://www.ti.com/lit/ds/symlink/sn74lv4051a.pdf
- AD5258: http://www.analog.com/media/en/technical-documentation/data-sheets/AD5258.pdf


3.3V power supply
-----------------
LV07A and LVC138A are 5V-tolerant and can be powered with 5V, the keyboard will work only with 5V power supply. It may not be completely safe to operate LV138A with 5V Vcc, its datasheet says:

> Exposure to absolute-maximum-rated conditions for extended periods may affect device reliability.

Digipot AD5258
--------------
Controller can operate AD5258 via I2C to change actuation point of keys. This may make keyboard unusable accidentally and it will be difficult to recovery in some situation. For safety firmware doesn't support it at this point, though.

Lower value of RDAC register causes shallower actuation point.

Resources
---------
- Pics: https://imgur.com/a/UTR8Z
