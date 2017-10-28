The Nyquist Keyboard
====================

The Nyquist is a 60% split ortholinear board by [Keebio](https://keeb.io). It has been designed in a similar manner to the Let's Split v2 by /u/wootpatoot. Each half of the keyboard is arranged in a 5x6 grid. There is an option to use a 2u key with PCB mounted MX stablizers, in place of the two innermost 1u keys on the bottom row.


## Build Guide

Since the design is very similar to the Let's Split v2, the build guide for that can be used while the build guide for the Nyquist is being fully developed. A build guide for putting together the Let's Split v2 can be found here: [An Overly Verbose Guide to Building a Let's Split Keyboard](https://github.com/nicinabox/lets-split-guide)

There is additional information there about flashing and adding RGB underglow.

## First Time Setup

Download or clone the whole firmware and navigate to the keyboards/nyquist directory. Once your development environment is setup, you'll be able to generate the default .hex using:

```
$ make serial
```

You will see a lot of output and if everything worked correctly you will see the built hex file:

```
nyquist_rev1_serial.hex
```

If you would like to use one of the alternative keymaps, or create your own, copy one of the existing [keymaps](keymaps/) and run make like so:


```
$ make YOUR_KEYMAP_NAME
```

If everything worked correctly you will see a file:

```
nyquist_rev1_YOUR_KEYMAP_NAME.hex
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
* Optional support for I2C connection between the two halves if for some
  reason you require a faster connection between the two halves. Note this
  requires an extra wire between halves and pull-up resistors on the data lines.

### 2u Support
In place of the two innermost 1u keys on the bottom row, a single 2u key can be used. If you choose to use this option, then in your keymap, set the innermost key on the bottom row to what you want the 2u key to be. For example, if using the 2u key on the left half of the board, set the keycode for the lower right key.

Required Hardware
-----------------

Apart from diodes and key switches for the keyboard matrix in each half, you
will need:

* 2 Arduino Pro Micro's. You can find theses on aliexpress for ≈3.50USD each.
* 2 TRRS sockets and 1 TRRS cable, or 2 TRS sockets and 1 TRS cable

Alternatively, you can use any sort of cable and socket that has at least 3
wires. If you want to use I2C to communicate between halves, you will need a
cable with at least 4 wires and 2x 4.7kΩ pull-up resistors

Optional Hardware
-----------------

A speaker can be hooked-up to either side to the `5` (`C6`) pin and `GND`, and turned on via `AUDIO_ENABLE`.

Wiring
------

The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and digital pin 3 (i.e.
PD0 on the ATmega32u4) between the two Pro Micros.

Then wire your key matrix to any of the remaining 17 IO pins of the pro micro
and modify the `matrix.c` accordingly.

The wiring for serial:

![serial wiring](http://imgur.com/BnCGU1Y)

The wiring for i2c:

![i2c wiring](http://imgur.com/5eiArDA)

The pull-up resistors may be placed on either half. It is also possible
to use 4 resistors and have the pull-ups in both halves, but this is
unnecessary in simple use cases.

Flashing
-------
From the keymap directory run `make SUBPROJECT-KEYMAP-avrdude` for automatic serial port resolution and flashing.
Example: `make rev1-serial-avrdude`


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
file will run on both hands instead of having to flash left and right handed
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
