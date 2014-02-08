IBM 4704 to USB keyboard converter
=======----=======================
This firmware converts IBM 4704 keyboard protocol to USB HID.


Connect Wires
-------------
In case of Teensy2.0(ATMega32U4):

1. Connect Vcc and GND.
2. Connect Clock and Data line. 
    - Clock is on PD1 and Data on PD2.
3. Optionally you need pull-up register. 1KOhm is OK?

To change pin configuration edit config.h.


Build Firmware
--------------
Just run `make`:

    $ make

To select keymap:

    $ make KEYMAP=[plain|...]


Keymap
------
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document(you can find in top README.md) and existent keymap files.
