Kmini keyboard firmware
======================

The Revo Kmini is a 65% keyboard with an additional two columns on the left. It is programmed with the 'KMAC key map', which only works on Windows and according to a [user](https://www.keebtalk.com/t/programming-revo-kmini/2107/7) it cannot map media controls or change the capslock key.

## Hardware
Columns 0, 1 and 10-16 and rows 0-4 are wired directly to the ATmega32u4, and columns 2-9 are wired to the [74HC237D demultiplexer](https://www.mouser.de/datasheet/2/916/74HC237-1319445.pdf). Capslock is on E2 and also triggers a reset if held when plugging the cable in. There are three possible places for leds, which are the capslock key and the two keys above the right arrow key. All three of them are individually controllable. The ATmega32u4 runs on an external crystal on 8mhz, so you'll have to change the bitclock on the ISP programmer if you're unable to read or write the chip.

## How to build
Please read the [documentation](https://docs.qmk.fm).

## How to flash
Hold the capslock key while plugging in the USB and flash the .hex file using QMK Toolbox or Atmel FLIP.