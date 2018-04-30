Orthodox
========

*Please note this guide is a work in progress and is based directly on the Let's Split guide.*

Orthodox is a split ortholinear keyboard with thumb-clusters designed in 2017 by /u/Deductivemonkee, expected to be available in group buys.
Each half has 18 keys in a 3x6 grid and a five key thumb-cluster, of which three use 1.25-unit keycaps.

![Example prototype build by /u/Deductivemonkee](http://i.imgur.com/R4PPKdog.jpg)

Its firmware is based on the Let's Split's.
Each side is controlled by an Arduino Pro Micro (or compatible), and they're connected by a TRRS cable using the serial protocol.
Support for the protocol using TWI (i2c®) is a work-in-progress.


## Revisions

- `Rev.1` Prototype GB version, supporting only Pro Micro in the corner footprint, and using PCB top- and bottom-plates.

Note that the second number after the `Rev.` text is the pcb *order number.* The prototypes will say 1, and the next order of any revision will say 2 and so on.

## Keymaps

[The default layout can be unofficially referred to here.](http://www.keyboard-layout-editor.com/#/gists/f120e2703a22a6a69c7be9a65a9d1342)

The thumb-clusters are an extension of row 2 and row 3 along columns 7, 8, and 9.
Row 2 does not have a physical key in column 8, so when editing keymaps a placeholder constant (`XXXXXXX` or `KC_NO`) must be used in the row2-col8 position.

## Build Guide

[Official build guide by /u/Deductivemonkee](http://imgur.com/a/9c0NP)

For further reading on build- and flashing-procedures for split ortholinear skeleton-case keyboards, please refer to [An Overly Verbose Guide to Building a Let's Split Keyboard](https://github.com/nicinabox/lets-split-guide), much of which can be applied to the Orthodox.

## First Time Setup

Download or clone the whole firmware and navigate to the root directory. Once your dev env is setup, you'll be able to generate the default .hex using:

```
$ make orthodox/rev1:default
```

You will see a lot of output and if everything worked correctly you will see the built hex files in your *root qmk_firmware directory* two levels up:

```
orthodox_rev1_default.hex
```

If you would like to use one of the alternative keymaps, or create your own, copy one of the existing [keymaps](keymaps/) and run make like so:


```
$ make orthodox/rev1:YOUR_KEYMAP_NAME
```

If everything worked correctly you will see a file:

```
orthodox_rev1_YOUR_KEYMAP_NAME.hex
```

For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/readme.md##customizing-your-keymap) in the main readme.md.


Features
--------

For the full Quantum Mechanical Keyboard feature list, see [the parent readme.md](/readme.md).

Some features supported by the firmware:

* Either half can connect to the computer via USB, or both halves can be used
  independently.
* You only need 3 wires to connect the two halves. Two for VCC and GND and one
  for serial communication.


Required Hardware
-----------------

Apart from diodes and key switches for the keyboard matrix in each half, you
will need:

* 2 Arduino Pro Micro's. You can find theses on aliexpress for ≈3.50USD each.
* 2 TRRS sockets and 1 TRRS cable


Notes on Software Configuration
-------------------------------

Configuring the firmware is similar to any other QMK project. One thing
to note is that `MATRIX_ROWS` in `config.h` is the total number of rows between
the two halves, i.e. if your split keyboard has 3 rows in each half, then
`MATRIX_ROWS=6`.


Flashing
-------
From the root directory run `make PROJECT:KEYMAP:avrdude` for automatic serial port resolution and flashing.
Example: `make orthodox/rev2:default:avrdude`


Choosing which board to plug the USB cable into (choosing Master)
--------
Because the two boards are identical, the firmware has logic to differentiate the left and right board.

It uses two strategies to figure things out: look at the EEPROM (memory on the chip) or looks if the current board has the usb cable.

The EEPROM approach requires additional setup (flashing the eeeprom) but allows you to swap the usb cable to either side.

The USB cable approach is easier to setup and if you just want the usb cable on the left board, you do not need to do anything extra.

### Setting the left hand as master
If you always plug the usb cable into the left board, nothing extra is needed as this is the default. Comment out `EE_HANDS` and comment out `I2C_MASTER_RIGHT` or `MASTER_RIGHT` if for some reason it was set.

### Setting the right hand as master
If you always plug the usb cable into the right board, add an extra flag to your `config.h`
```
 #define MASTER_RIGHT
```

### Setting EE_hands to use either hands as master
If you define `EE_HANDS` in your `config.h`, you will need to set the
EEPROM for the left and right halves.

The EEPROM is used to store whether the
half is left handed or right handed. This makes it so that the same firmware
file will run on both hands instead of having to flash [left](../lets_split/eeprom-lefthand.eep) and [right](../lets_split/eeprom-righthand.eep) handed
versions of the firmware to each half. To flash the EEPROM file for the left
half run:
```
avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:eeprom-lefthand.eep
// or the equivalent in dfu-programmer
```
and similarly for right half
```
avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:eeprom-righhand.eep
// or the equivalent in dfu-programmer
```

NOTE: replace `$(COM_PORT)` with the port of your device (e.g. `/dev/ttyACM0`)

After you have flashed the EEPROM, you then need to set `EE_HANDS` in your config.h, rebuild the hex files and reflash.

Note that you need to program both halves, but you have the option of using
different keymaps for each half. You could program the left half with a QWERTY
layout and the right half with a Colemak layout using bootmagic's default layout option.
Then if you connect the left half to a computer by USB the keyboard will use QWERTY and Colemak when the
right half is connected.


Notes on Using Pro Micro 3.3V
-----------------------------

Do update the `F_CPU` parameter in `rules.mk` to `8000000` which reflects
the frequency on the 3.3V board.

Also, if the slave board is producing weird characters in certain columns,
update the following line in `matrix.c` to the following:

```
// _delay_us(30);  // without this wait read unstable value.
_delay_us(300);  // without this wait read unstable value.
```
