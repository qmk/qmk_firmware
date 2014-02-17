IBM 4704 to USB keyboard converter
==================================
This firmware converts IBM 4704 keyboard protocol to USB HID.

Keyboard initialization process takes a few seconds at start up. During that you will hear buzzer from the keyboard. **You need to plug USB cable after hooking up your keyboard to the converter.**


Supported Keyboard
------------------
### IBM capacitive switch models:
- 6019273 Model 100 50-key (grid layout)      http://kishy.dyndns.org/?p=977
- 6019284 Model 200 62-key Alpha(60% layout)  http://kishy.dyndns.org/?p=894
- 6019303 Model 300 77-key Expanded Alpha     http://kbtalking.cool3c.com/article/23272
- 6020218 Model 400 107-key Full key          http://kishy.dyndns.org/?p=980

### Alps switch(vintage Green) models:

- 5954339 Japanese 102-key    http://deskthority.net/post87127.html#p87127
- 6112883 Japanese 102-key    http://geekhack.org/index.php?topic=52888.msg1194489#msg1194489
- 6112884 Japanese 102-key    http://geekhack.org/index.php?topic=50437.msg1193047#msg1193047
- 6341739 Chinese 102-key     http://geekhack.org/index.php?topic=52888.msg1176566#msg1176566


Connector
---------
Keyboard Plug from front:

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
2. Connect CLOCK to PD1 and DATA to PD0. You can change pin with config.h.
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
