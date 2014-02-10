IBM 4704 to USB keyboard converter
==================================
This firmware converts IBM 4704 keyboard protocol to USB HID.


4704 Connector
--------------
    Keyboard Plug from front

    DSUB-9
    -------------
    \ N 2 3 4 5 /
     \ N N N N /
      ---------
    2   GND
    3   VCC 5V
    4   DATA
    5   CLOCK
    N   No connection/No pin.


Connection
----------
In case of using ATMega32U4(Teensy2.0):

1. Supply power with VCC and GND.
2. Connect CLOCK to PD1 and DATA to PD2. You can change pin with config.h.
3. Optionally you may need pull-up register. 1KOhm probably work.


Build Firmware
--------------
Just run `make`:

    $ make

To select keymap:

    $ make KEYMAP=[plain|...]


Keymap
------
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document(you can find in top README.md) and existent keymap files.
