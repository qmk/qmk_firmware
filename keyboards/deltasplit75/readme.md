DeltaSplit75
======

This readme and most of the code are from https://github.com/ahtn/tmk_keyboard/ and https://github.com/qmk/qmk_firmware/tree/master/keyboards/lets_split

Credit to ahtn and wootpatoot for work on the split keyboard firmware

Split keyboard firmware for Arduino Pro Micro or other ATmega32u4
based boards.

## Case Files
Files are available here: https://github.com/xyxjj/DeltaSplit75-Case-files

## Build Guide
The build guide should be found at https://qmk.fm/deltasplit75


## First Time Setup

Download or clone the whole firmware and navigate to the keyboards/deltasplit75 directory. Once your dev env is setup, you'll be able to generate the .hex using:

```
make v2

or

make v2-YOUR_KEYMAP_NAME (if you make a folder for your keymap)

or

make protosplit (if you have one of the prototype PCBs)
```

You will see a lot of output and if everything worked correctly you will see the built hex files:

```
deltasplit75_v2_protosplit.hex 

or

deltasplit74_v2_YOUR_KEYMAP_NAME.hex

or

deltasplit75_v2_default.hex

```


For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/readme.md##customizing-your-keymap) in the main readme.md.

### DeltaSplit75 V2
The PCBs available in groupbuy are all v2, if you've bought one of my prototype PCBs (it says DeltaSplit65 on the silkscreen instead of 75), use the code make protosplit instead

Features
--------

For the full Quantum Mechanical Keyboard feature list, see [the parent readme.md](/readme.md).

Some features supported by the firmware:

* Either half can connect to the computer via USB, or both halves can be used
  independently.
* 75% formfactor
* Support for multiple Bottom Rows
* RGB underglow support
* Split Backspace and ISO support


Flashing
-------
I personally use xLoader to upload my hex files to the keyboard, though any other working software is fine too


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
