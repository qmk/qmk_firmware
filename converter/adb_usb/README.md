ADB to USB keyboard converter
=============================
This firmware converts ADB keyboard protocol to USB.
You can use TMK Converter, PJRC Teensy2.0 and other USB AVR MCU(ATMega32U4, AT90USB64/128 or etc) for this. But binary size is probably more than 10KB and it won't fit into 8K flash.

Discuss: http://geekhack.org/showwiki.php?title=Island:14290



README FIRST
------------
https://github.com/tmk/tmk_keyboard
https://github.com/tmk/tmk_keyboard/tree/master/converter/adb_usb

Also check these when you are in trouble.

https://github.com/tmk/tmk_keyboard/wiki
https://github.com/tmk/tmk_keyboard/labels/NOTE


Wiring
------
Connect ADB pins to controller just by 3 lines(Vcc, GND, Data). By default Data line uses port PD0.

ADB female socket from the front:

      ,--_--.
     / o4 3o \      1: DATA
    | o2   1o |     2: Power SW
     -  ===  -      3: VCC
      `-___-'       4: GND

This converter uses AVR's internal pull-up, but it seems to be too weak, in particular when you want to use a long or coiled cable. The external pull-up resistor(1K-10K Ohm) on Data is strongly recommended.(It is almost must!)
https://github.com/tmk/tmk_keyboard/wiki/FAQ#pull-up-resistor

Pull-up resister:

    Keyboard       Conveter
                   ,------.
    5V------+------|VCC   |
            |      |      |
           [R]     |      |
            |      |      |
    Signal--+------|PD0   |
                   |      |
    GND------------|GND   |
                   `------'
    R: 1K Ohm resistor


Define following macros for ADB connection in config.h if you use other than port PD0.

    ADB_PORT, ADB_PIN, ADB_DDR, ADB_DATA_BIT


Build firmware and Program microcontroller
------------------------------------------
See [doc/build.md](../../tmk_core/doc/build.md).

To build firmware:

    $ make -f Makefile clean
    $ make -f Makefile

You can select keymap(ansi is default) like this:

    $ make -f Makefile KEYMAP=[ansi|iso|hasu]

To program TMK Converter:

    $ make -f Makefile dfu

To program Teensy2.0:

    $ make -f Makefile.teensy teensy

Use **Makefile.rev1** for TMK Converter rev.1 and **Makefile.teensy** for Teensy2.0 instead of **Makefile**. For TMK Converter rev.2 just use **Makefile**.


Keymap
------
You can change a keymap by editing code of keymap_[ansi|iso|hasu|yours].c.
How to define the keymap is probably obvious. You can find key symbols in common/keycode.h. And see [doc/keymap.md](../../tmk_core/doc/keymap.md) for more detail.


Magic command
-------------
To get help press `h` holding Magic key. Magic key is `Power key`.


Locking CapsLock
----------------
Many of old ADB keyboards have mechanical push-lock switch for Capslock key and this converter supports the locking Capslock key by default. See README in top directory for more detail about this feature.
https://github.com/tmk/tmk_keyboard/blob/master/README.md#mechanical-locking-support

Also you may want to remove locking pin from the push-lock switch to use capslock as a normal momentary switch.


Mouse support
-------------
ADB mouse support was added by @mek-apelsin on Apr,2015. It supports only one button as of now.
https://github.com/tmk/tmk_keyboard/pull/207


Notes
-----
Not-extended ADB keyboards have no discrimination between right modifier and left one,
you will always see left control even if you press right control key.
Apple Extended Keyboard and Apple Extended Keyboard II can discriminate both side
modifiers except for GUI key(Windows/Command).

And most ADB keyboard has no diodes in its matrix so they are not NKRO,
though ADB protocol itself supports it. See protocol/adb.c for more info.

If keyboard has ISO layout you need to use ISO keymap with `make KEYMAP=iso`. With ANSI
keymap you will suffer from swapped keys problem.

https://github.com/tmk/tmk_keyboard/issues/35

EOF
