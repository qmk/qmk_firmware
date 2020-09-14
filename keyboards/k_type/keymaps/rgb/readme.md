# K-Type RGB Matrix Keymap

This is an experimental keymap adding support for RGB Matrix on the K-Type.

The board has two IS31FL3733 LED controllers, but they are each on different I2C buses, which QMK's `i2c_master` implementation currently does not support. As a result, all the keys after the left shift will not be lit.
