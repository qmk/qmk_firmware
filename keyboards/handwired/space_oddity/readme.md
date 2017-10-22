Space Oddity Keyboard
=====================

This firmware is for an Emacs-focused handwired custom keyboard using an Arduino Pro Micro.

As originally designed, the top row consists of 2u keys which are used for user-defined macros. The keys for Shift and Enter are 1.75u.

Some simple example macros are included. To add your own, simply add the number of the macro you want in the appropriate section.

A picture of the finished product can be found here: https://imgur.com/dE9Y4XK

## Pinout

The following pins are used:
- Columns 1-12: B2, B6, B5, B4, E6, D7, C6, D4, D0, D1, D2, D3
- Rows 1-6: F4, F5, F6, F7, B1, B3

## Compiling and loading the firmware

To build the firmware, run `make handwired/space-oddity` from the toplevel directory.

On GNU/Linux, you can flash the default layout onto the microcontroller by using `avrdude -p atmega32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:handwired_space_oddity_default.hex`. Note that the device name under `/dev` may be different. 


This design was conceived by James Taylor. Any requests for further information and/or tips for building your own are welcome!