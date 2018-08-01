Let's Split Vitamins Included
======
![Let's Split Vitamins included, assmebled in 3D printed case](https://i.imgur.com/btl0vNQ.jpg)

This readme and most of the code are from https://github.com/ahtn/tmk_keyboard/


**Hardware files for the Let's Split vitamins included are stored [here](http://github.com/duckle29/let-s-Split-v2/tree/onboardMCU)**

## First Time Setup

Clone the `qmk_firmware` repo and navigate to its top level directory. [Once your build environment is setup](https://docs.qmk.fm/getting_started_build_tools.html), you'll be able to generate the default .hex using the [build/compile instructions](https://docs.qmk.fm/build-compile-instructions) in the docs

If everything worked correctly you will see a file:

```bash
lets_split_vitamins_rev1_YOUR_KEYMAP_NAME.hex
```

If you want, you can flash the hex file to the keyboard right after compilation, by adding `:avrdude` to the end of the make command like so:

```bash
make lets_split_vitamins/rev1:default:avrdude
```

This will both compile the hex, and flash the connected half.

For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/readme.md##customizing-your-keymap) in the main readme.md.


Features
--------

For the full Quantum Mechanical Keyboard feature list, see [the parent readme.md](/readme.md).

Some features supported by the firmware:

* Either half can connect to the computer via USB, or both halves can be used
  independently.
* You only need 3 wires to connect the two halves. One for VCC, one for GND and one
  for serial communication.
* Optional support for I2C connection between the two halves if for some
  reason you require a faster connection between the two halves. Note this
  requires an extra wire between halves and pull-up resistors on the data lines.
  This is supported on the vitamins included.  
  The extra data line can also be used for ws2812 type LEDs.  
  If neither I2C nor RGB underglow is used, a TRS cable can be used instead of the 4wire TRRS cables.

Required Hardware
-----------------
|Amount| Description |
|--|--|
| 1 | PCB kit from novelkeys |
| 48 | MX compatible switches |
| 48 | 1U keycaps
| 2 | Half cases. A 3D model for the left half is available [here](https://cad.onshape.com/documents/c6e5ae250d1e24fe46c9ef6c/w/d69f7049c0921df3d2b241f9/e/ecc2b176ab52a6d77bc55051). Mirror that to get a right-half case. Plate cases will be designed in the future.
| 1 | USB-mini-B cable of your choice |
| 1 | TRS / TRRS cable

Optional Hardware
-----------------

A speaker can be hooked-up to the footprint on the PCBs. It is already enabled in the default firmware from github.

A strip of WS2812 LEDs can be hooked up too, a guide will be written on how to do that once I get mine in the mail.  
The PCB and connectors can safely handle 1A of current, but the USB standard is only rated at 500mA. Keep that in mind when picking the amount of LEDs.


## Using I2C

On  the left half PCB, there's two pads labled ***I2C Pullup*** if you want to use I2C, you need to bridge those two solder jumpers with a soldering iron.

You can change your configuration between serial and i2c by modifying your `config.h` file.

Notes on Software Configuration
-------------------------------

Configuring the firmware is similar to any other QMK project. One thing
to note is that `MATRIX_ROWS` in `config.h` is the total number of rows between
the two halves, so because the let's split vitamins included has 4 rows in each half, it's
`MATRIX_ROWS=8`.

Also, the current implementation assumes a maximum of 8 columns, but it would
not be very difficult to adapt it to support more if required.


## Entering bootloader  
If the keyboard isn't new, and has been flashed before, you need to enter bootloader.
To enter bootloader, either use the assigned keys on the keymap, or if none have been put in the keymap, quickly short the reset to gnd twice. (Bottom pins of programming header, see image) ![Reset pins](https://i.imgur.com/LCXlv9W.png)

If using the default keymap, there's a reset key-combination on each half:  
***Lower (SW23) and left-shift (SW13)*** on the left half, or  
***Raise(SW44) and Enter(SW42)***  on the right half  
It is recommended to add such reset keys to any custom keymaps. It shouldn't be necesarry to have one on each half, but the default layout has that.

The board exits bootloader mode after 8 seconds, if you haven't started flashing.

## EEPROM

If this is the first time you're flashing the boards, you have to flash EEPROM

0. If your keyboard is plugged in, unplug it
1. Open a terminal, and navigate to the qmk_firmware folder
2. Run `ls /dev | grep tty` Note down which ports you see
2. Plug the keyboard in, if it's new, it should enter bootloader, if it's not new, see **Entering bootloader** on how to enter bootloader mode
4. Right after entering bootloader, run `ls /dev | grep tty` again. There should be a new tty, this is the bootloader TTY, note it down. If nothing shows see **Entering bootloader** on how to enter bootloader mode
6. For the left hand side, run  `avrdude -c avr109 -p m32u4 -P /dev/ttyS1 -U eeprom:w:"./quantum/split_common/eeprom-lefthand.eep":a`
Replace ***/dev/ttyS1*** with the port you noted down earlier. If you're on windows using msys2, replace ***/dev/ttyS1*** with COM2, note that the number is one higher than the tty number.  
Do the same For the right hand, but change the file to ***eeprom-righthand.eep***

Your EEPROM should be flashed :)

In the future, you shouldn't need to flash EEPROM (it will in fact wear the eeprom memory, so don't)

## Flashing
If you haven't flashed EEPROM before, do that first.  

To flash keymaps onto the keyboard, use:
```bash
make lets_split_vitamins/rev1:[KEYMAP]:avrdude
```
from the qmk_firmware folder. Default being the default keymap.

You can plug either half into USB and it will work. you can also remove the TRS/TRRS cable, and plug both halves in. (which is why the default layout has reset on both halves)

Enjoy your keyboard! :D
