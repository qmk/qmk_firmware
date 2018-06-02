

FC980C Alt Controller
=====================

This file and the entire QMK port of this board are based on its TMK implementation: https://github.com/tmk/tmk_keyboard/tree/master/keyboard/fc980c

------------

- Keyboard Maintainer: [Balz Guenat](https://github.com/BalzGuenat)
- Hardware Supported: Hasu's Alt Controller (see below)
- Hardware Availability: https://geekhack.org/index.php?topic=90104.0

Make example for this keyboard (after setting up your build environment):

    make fc980c:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

To flash the firmware, press the reset button on the controller and run:

    sudo make fc980c:default:dfu

-----------

This controller replaces original controller of Leopold FC980C and makes the keyboard programmable.

Discuss this here: https://geekhack.org/index.php?topic=90681.0

The keyboard is very similar electronically to its sibling model FC660C you can also refer this.

FC660C Alt Controller: https://geekhack.org/index.php?topic=88439.0


Actuation Point adjustment
--------------------------
You can adjust the actuation point of the keys by setting `ACTUATION_DEPTH_ADJUSTMENT` in `config.h`.
A value above 0 will result in a deeper, less sensitive actuation whereas a value above 1 will result in a more shallow, more sensitive actuation.
Be careful with this setting and use small values (+/-5).
See the `actuation-point-example` keymap for an example.
For more information, inspect the `fc660c_i2c` branch of TMK [here](https://github.com/tmk/tmk_keyboard/tree/fc660c_i2c).
Functionality for writing to the EEPROM has deliberately not been included to reduce the chance of people messing up their boards.


Hardware
--------
This project uses common and familiar ATmega32u4 but any microcontroller with 5V I/O will work.

- Schematic of Alt controller: schematic.pdf


Pin configuration
-----------------
Connector bridging between switch board and controller is Hirose DF14A-20P-1.25H.

    |Switch  |Controller |
    |  board |     board |Description                           |Function   |ATmega32u4
    |--------|-----------|--------------------------------------|-----------|------------
    | 1      |20         | FG                                   |FG         |GND
    | 2      |19         | GND                                  |GND        |GND
    | 3      |18         | GND                                  |GND        |GND
    | 4      |17         | 3.3V                                 |V33        |3.3V/5V
    | 5      |16         | 5V                                   |Vcc        |5V
    | 6      |15         |*Z6-TP1684-4-HYS(o)                   |KEY_HYS    |PC7
    | 7      |14         |*Z6-TP1684-2-KEY(i)                   |KEY_STATE  |PC6
    | 8      |13         |*Z7-AD5258-5-SCL(I2C)                 |I2C_SCL    |PD0(TWI)
    | 9      |12         |*Z7-AD5258-4-SDA(I2C)                 |I2C_SDA    |PD1(TWI)
    |10      |11         |*Z5/4-LV4051A-6-~EN(Lo:Z5 Hi:Z4)      |COL_bit3   |PB3
    |11      |10         |+Z3-LV07A-5 (LV4051A-9-C)             |COL_bit2   |PB2
    |12      | 9         |+Z3-LV07A-1 (LV4051A-10-B)            |COL_bit1   |PB1
    |13      | 8         |+Z3-LV07A-3 (LV4051A-11-A)            |COL_bit0   |PB0
    |14      | 7         |+Z1-LVC138A-3-C                       |ROW_bit2   |PD6
    |15      | 6         |+Z1-LVC138A-2-B                       |ROW_bit1   |PD5
    |16      | 5         |+Z1-LVC138A-1-A                       |ROW_bit0   |PD4
    |17      | 4         |+Z1-LVC138A-4-~G2A  Z6-TP1684-5-~EN   |KEY_ENABLE |PD7
    |18      | 3         |+Q4-NPN-B-NumLock_LED(Hi:On)          |LED_NUML   |PB4
    |19      | 2         |+Q3-NPN-B-CapsLock_LED(Hi:On)         |LED_CAPS   |PB5
    |20      | 1         |+Q2-NPN-B-ScrollLock_LED(Hi:On)       |LED_SCRL   |PB6

```
* 5V intferface
+ 3.3V interface
```


Switch matrix
-------------

    |    |0   |1   |2   |3   |4   |5   |6   |7   |8   |9   |A   |B   |C   |D   |E   |F   |
    |----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
    |   0|Left|RCtl|RAlt|    |Down|P.  |Righ|P0  |X   |LGui|`   |V   |    |Esc |M   |Spc |
    |   1|Fn  |.   |    |    |P1  |PEnt|P2  |P3  |Z   |LAlt|LCtl|C   |K   |    |N   |B   |
    |   2|'   |/   |,   |    |P4  |P+  |P5  |P6  |D   |A   |LSft|F   |J   |F1  |H   |G   |
    |   3|RSft|;   |L   |]   |Up  |    |    |    |S   |Q   |Caps|R   |I   |F3  |U   |T   |
    |   4|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
    |   5|=   |-   |0   |\   |NLck|BSpc|P/  |P*  |3   |2   |    |4   |9   |F2  |7   |6   |
    |   6|[   |P   |O   |Ent |P7  |P-  |P8  |P9  |W   |1   |Tab |E   |8   |F4  |Y   |5   |
    |   7|F11 |F10 |F9  |F12 |Del |PgDn|Ins |PgUp|    |    |    |    |F8  |F5  |F7  |F6  |


Row designation
---------------
LV138A(Z1) selects one of 8 row lines and gives strobe by enabling with ~G2A(17).

    |ROW |bit0|bit1|bit2|
    |----|----|----|----|
    |0   |0   |0   |0   |
    |1   |1   |0   |0   |
    |2   |0   |1   |0   |
    |3   |1   |1   |0   |
    |4   |0   |0   |1   |
    |5   |1   |0   |1   |
    |6   |0   |1   |1   |
    |7   |1   |1   |1   |


Column designation
------------------
LV4051A(Z4, Z5) select one of 16 column lines to sense capacitance of switches.

    |COL |bit0|bit1|bit2|bit3|
    |----|----|----|----|----|
    |0   |0   |0   |0   |0   |
    |1   |1   |0   |0   |0   |
    |2   |0   |1   |0   |0   |
    |3   |1   |1   |0   |0   |
    |4   |0   |0   |1   |0   |
    |5   |1   |0   |1   |0   |
    |6   |0   |1   |1   |0   |
    |7   |1   |1   |1   |0   |
    |8   |0   |0   |0   |1   |
    |9   |1   |0   |0   |1   |
    |A   |0   |1   |0   |1   |
    |B   |1   |1   |0   |1   |
    |C   |0   |0   |1   |1   |
    |D   |1   |0   |1   |1   |
    |E   |0   |1   |1   |1   |
    |F   |1   |1   |1   |1   |


Firmware
--------
Just `make` to build firmware. And consult with wiki for further information.

- https://github.com/tmk/tmk_keyboard/tree/master/keyboard/fc660c
- https://github.com/tmk/tmk_keyboard/wiki


Datasheets
----------
- Hirose DF14A-20P-1.25H: http://www.mouser.com/ds/2/185/DF14_catalog-939195.pdf
- LV07A: http://www.ti.com/lit/ds/symlink/sn74lv07a.pdf
- LV138A: http://www.ti.com/lit/ds/symlink/sn74lvc138a.pdf
- LV4051A: http://www.ti.com/lit/ds/symlink/sn74lv4051a.pdf
- AD5258: http://www.analog.com/media/en/technical-documentation/data-sheets/AD5258.pdf
- JST S5B-PH-SM4: http://www.jst-mfg.com/product/pdf/eng/ePH.pdf
- Hirose UX60SC-MB-5S8: https://www.hirose.com/product/en/products/UX/UX60SC-MB-5S8%2880%29/
- Tr(E42) for LED?: http://cj-elec.com/txUpfile/2013614923661845.pdf
- TYU TU1252WNR-05S: http://php2.twinner.com.tw/files/goodjob/TY1252series.pdf


3.3V power supply
-----------------
LV07A and LVC138A are 5V-tolerant and can be powered with 5V, the keyboard will work only with 5V power supply. It may not be completely safe to operate LV138A with 5V Vcc, its datasheet says:

> Exposure to absolute-maximum-rated conditions for extended periods may affect device reliability.


Digipot AD5258
--------------
Controller can operate AD5258 via I2C to change actuation point of keys. This may make keyboard unusable accidentally and it will be difficult to recovery in some situation. For safety firmware doesn't support it at this point, though.

Lower value of RDAC register causes shallower actuation point.


USB connector board
-------------------
The keyboard has USB receptacle on small separate 1.0mm-thick PCB. USB receptacle is Hirose UX60SC-MB-5S8 while wire-to-PCB connector is TYU TU1252WNR-05S.

http://i.imgur.com/Nucn6h9.jpg


Resources
---------
- Pics: http://imgur.com/a/HhyIq
