IBM 4704 to USB keyboard converter
==================================
This firmware converts IBM 4704 keyboard protocol to USB HID.

Keyboard initialization process takes a few seconds at start up. During that you will hear buzzer from the keyboard. **You need to plug USB cable after hooking up your keyboard to the converter.**


Update
------
- 2015/09/07  Added keymap for Alps 102-key. Thanks, tai @ geekhack!
- 2015/05/05  Added keymaps for 107-key, 77-key and 50-key. Thanks, orihalcon @ geekhack!
- 2015/05/19  Fixed a protocol handling bug.



Supported Keyboard
------------------
### IBM capacitive switch models:
- 6019273 Model 100 50-key (grid layout)      http://kishy.ca/?p=894
- 6019284 Model 200 62-key Alpha(60% layout)  http://kishy.ca/?p=894
- 6019303 Model 300 77-key Expanded Alpha     http://deskthority.net/photos-f62/ibm-6019303-t8502.html
- 6020218 Model 400 107-key Full key          http://kishy.ca/?p=894

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
In case of using ATMega32U4/U2

1. Supply power with VCC and GND.
2. Connect CLOCK to PD1 and DATA to PD0. You can change pin with config.h.
3. Optionally you may need pull-up register. 1KOhm probably work.

TMK Converter can supports IBM 4704.
https://github.com/tmk/keyboard_converter


Build Firmware
--------------
Just run `make`:

    $ make -f <makefile>

For TMK Converter rev.1 use `Makefile.tmk_rev1` as makefile:

    $ make -f Makefile.tmk_rev1

For TMK Converter rev.2 use `Makefile.tmk_rev2` as makefile:

    $ make -f Makefile.tmk_rev2

To select keymap:

    $ make -f <makefile> KEYMAP=[plain|...]

To indentify your TMK Converter revision see [this](https://github.com/tmk/keyboard_converter#pcb-revisions).


Keymap
------
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document(you can find in top README.md) and existent keymap files.

Use `KEYMAP_ALPS102()` to define your keymap for Alps models.
