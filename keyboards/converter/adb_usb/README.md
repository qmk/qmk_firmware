ADB to USB keyboard converter
=============================
Based on the [TMK](https://github.com/tmk/tmk_keyboard/tree/master/converter/adb_usb) converter.
This firmware converts Apple ADB keyboard protocol to USB, you can use it to plug old ADB keyboard into modern computer.


Wiring
------
Connect ADB pins to controller just by 3 lines(Vcc, GND, Data). By default Data line uses port PD0.

ADB female socket from the front:

      ,--_--.
     / o4 3o \      1: DATA
    | o2   1o |     2: Power SW
     -  ===  -      3: VCC
      `-___-'       4: GND

The female socket's pcb might also have the pin numbers printed on next to the wire.  
 
This converter uses AVR's internal pull-up, but it seems to be too weak, in particular when you want to use a long or coiled cable. The external pull-up resistor(1K-10K Ohm) on Data is necessary.

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


Define following macros for ADB connection in config.h if you use other than port PD0 (Pin3 on the ProMicro).

    ADB_PORT, ADB_PIN, ADB_DDR, ADB_DATA_BIT


Keymap
------
Predefined keymaps are in the *iso* and *ansi* folders.
For your own keymap, use `LAYOUT_EXT_ISO` or `LAYOUT_EXT_ANSI` respectively. Any qmk keycode will work.


Locking CapsLock
----------------
Many of old ADB keyboards have mechanical push-lock switch for Capslock key and this converter supports the locking Capslock key by default using the `KC_LCAP` keycode.

Also you may want to remove locking pin from the push-lock switch to use capslock as a normal momentary switch.


Notes
-----
Not-extended ADB keyboards have no discrimination between right modifier and left one,
you will always see left control even if you press right control key.
Apple Extended Keyboard and Apple Extended Keyboard II can discriminate both side
modifiers except for GUI key(Windows/Command).

And most ADB keyboard has no diodes in its matrix so they are not NKRO,
though ADB protocol itself supports it.

If keyboard has ISO layout you may have swapped keys problem (\` and / on UK ISO). Adjust the layout definition in adb_usb.h if necessary.