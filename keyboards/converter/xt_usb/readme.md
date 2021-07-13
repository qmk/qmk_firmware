XT to USB keyboard converter
==============================
This is a port of TMK's converter/xt_usb to QMK.

This firmware converts XT keyboard protocol to USB.(It supports Scan Code Set 1.)


Connect Wires
-------------
1. Connect **Vcc** and **GND**.
2. Connect **Clock** and **Data** line. **Clock** is on `PD1`,  **Data** on `PD0` by default. And optionally you can use `PB7` for **Reset**.(Compatible to Soarer's converter) To change pin configuration edit `config.h`.
3. You need pull-up resistor. **1K-10K Ohm** will be OK.


XT keyboard protocol  resource
------------------------------
https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol
