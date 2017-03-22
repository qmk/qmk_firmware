SSD1306 OLED Display via I2C
======

Features
--------

Some features supported by the firmware:


* I2C connection between the two halves is required as the OLED display will use this connection as well. Note this
  requires pull-up resistors on the data and clock lines.
* OLED display will connect from either side


Wiring
------

The wiring for i2c:

![i2c wiring](imgs/split-keyboard-i2c-schematic.png)

The pull-up resistors may be placed on either half. It is also possible
to use 4 resistors and have the pull-ups in both halves, but this is
unnecessary in simple use cases.

Work in progress...


OLED Configuration
-------------------------------

Work in progress...