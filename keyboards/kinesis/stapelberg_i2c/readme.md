# I2C support for Kinesis Advantage with Stapelberg controller

## Context
The Kinesis Advantage / Advantage Pro / Advantage 2 is an ergonomic keyboard by Kinesis Ergo (https://kinesis-ergo.com/). The Stapelberg controller is a snap-in replacement controller based on a Teensy 2.0+. It's created by Michael Stapelberg for the Advantage and Advantage Pro keyboard (https://michael.stapelberg.ch/posts/2013-03-21-kinesis_custom_controller/). The PCB design can be found on OSHPark (https://oshpark.com/shared_projects/BwWRYP5c)

The Advantage 2 keyboard has different connectors for the thumb cluster, but a modified Stapelberg controller is available ( https://www.reddit.com/r/MechanicalKeyboards/comments/8o2yzt/dropin_pcb_replacement_to_support_qmk_for_kinesis/). The PCB design can be found here: https://github.com/joeyjyliu/kinesis_adv2_qmk

## I2C support

The Teensy 2.0+ supports I2C on pins D0 and D1. Unfortunately the Stapelberg controller uses these pins to map key columns. In this configuration I moved the first two column pins from D0 and D1 to E6 and E7 respectively.

To use this configuration, be sure remove the connection between pins D0 and D1 and the PCB (desolder, then remove both pins). Then route D0 and D1 from the Stapelberg PCB to Teensy pins E6 and E7 respectively.

Now you can use I2C to connect an OLED screen or some other awesome stuff!

Run `make kinesis/stapelberg-i2c:default` while in the QMK directory to test.

## Used pins

|Pins|Description|
|-|-|
|F6, F7, D2, D3, D4, D5, D6, D7, C0, C1, C2, C3, C4, C5, C6|Rows|
|B0, B1, B2, B3, B4, B5, B6|Columns|
|B7|Can be used as speaker|
|D0|SCL: I2C Clock|
|D1|SDA: I2C Data|
|F0|Keypad LED|
|F1|Scroll lock LED|
|F2|Numlock LED|
|F3|Capslock LED|

Maurice de Bijl 2019
