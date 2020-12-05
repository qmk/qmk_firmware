ADB-to-USB Keyboard Converter
=============================
This firmware converts Apple Desktop Bus (ADB) keyboard protocol to USB so that you can use an ADB keyboard on a modern computer. It works on the PJRC Teensy 2.0 and other USB AVR MCUs (ATMega32U4, AT90USB64/128, etc) and needs at least 10KB of flash memory.


This is a port of the TMK ADB-to-USB converter to QMK. For information on QMK, please consult the following:
https://github.com/qmk/qmk_firmware  
https://docs.qmk.fm


Wiring
------
Connect the VCC, GND, and DATA lines of the ADB keyboard to the controller (Teensy 2.0 or similar). By default the DATA line uses port PD0. The Power SW line is unused by the converter.

ADB female socket from the front:

      ,--_--.
     / o4 3o \      1: DATA
    | o2   1o |     2: Power SW
     -  ===  -      3: VCC
      `-___-'       4: GND

This converter uses AVR's internal pull-up, but it seems to be too weak, in particular when you want to use a long or coiled cable. Using an external pull-up resistor (1K-10K Ohm) between the DATA and VCC lines is strongly recommended.

Pull-up resistor:

    Keyboard       Converter
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


Building the Firmware
------------------------------------------
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


Keymap
------
To build the default keymap run this command:

    $ make converter/adb_usb:default

You may add your own keymap to the converter/adb_usb/keymaps directory, as you would with any other QMK-powered keyboard.

To build your custom keymap, change the build command to:

    $ make converter/adb_usb:my_keymap

Where 'my_keymap' is the name of your custom keymap directory.


Locking Caps Lock
----------------
Many old ADB keyboards use a locking switch for the caps lock key. This converter supports the locking caps lock key by default.


Notes
-----
Non-extended ADB keyboards make no distinction between the left and right modifiers,
i.e. the keycode for the left modifier will be sent even if the right modifier

The Apple Extended Keyboard and Apple Extended Keyboard II can differentiate between the left and right modifiers except for the GUI key (Windows/Command).

Most ADB keyboards have no diodes in its matrix so they are not NKRO,
though the ADB protocol itself supports it. See protocol/adb.c for more info.


QMK Port Changelog
---------
- 2018/09/16 - Initial release.
- 2018/12/23 - Fixed lock LED support.
