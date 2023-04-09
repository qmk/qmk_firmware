# Dactyl Manuform

the [Dactyl-Manuform](https://github.com/tshort/dactyl-keyboard) is a split curved keyboard based on the design of [adereth dactyl](https://github.com/adereth/dactyl-keyboard) and thumb cluster design of the [manuform](https://geekhack.org/index.php?topic=46015.0) keyboard, the hardware is similar to the let's split keyboard. all information needed for making one is in the first link.
![Imgur](https://i.imgur.com/7y0Vbyd.jpg)

## First Time Setup

Download or clone the `qmk_firmware` repo and navigate to its top level directory. Once your build environment is setup, you'll be able to complie the default .hex using:

Depending on your keymap, chose one of the following commands:

```
$ make handwired/dactyl_manuform/YOUR_LAYOUT:YOUR_KEYMAP_NAME
```

example:

```
$ make handwired/dactyl_manuform/4x5:default
```

If everything worked correctly you will see a file:

```
dactyl_manuform_YOUR_LAYOUT_YOUR_KEYMAP_NAME.hex
```

For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/docs/faq_keymap.md) in the main readme.md.

## Keymaps

### Default

The default functional layout, based on QWERTY, and every variant has this keymap; used as a starting point/template for custom keymaps and for debugging purposes when soldering key matrix to controller.

### Via
Similar to Default but adds support for the [Via](https://www.caniusevia.com/) keymap configurator. Reduces the number of layers to 4 to comply with Via defaults, and remaps some keys to accomodate that constraint.

Variants with keymap for Via:
- 4x6
- 5x6_5
- 5x7

### Manna-harbour_miryoku

For more information on this layout schematic, please see the [Miryoku Reference Manual](https://github.com/manna-harbour/miryoku/tree/master/docs/reference).  
For QMK specifics, please see [Miryoku QMK](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku) 

Variants with keymap for Miryoku:  
- 4x5
- 4x5_5
- 4x6
- 4x6_5
- 5x6

Variants with support for Miryoku without a specific keymap:  
- 3x5_3

## Required Hardware

Apart from diodes and key switches for the keyboard matrix in each half, you will need:
-   2 Arduino Pro Micro controllers. You can find these on AliExpress for ≈3.50USD each.
-   2 TRRS sockets and 1 TRRS cable (for 4 wire communication), or 2 TRS sockets and 1 TRS cable (for 3 wire communication)

Alternatively, you can use any matching cable and socket type that has at least 3
wires. If you want to use I2C to communicate between halves, you will need a
cable with at least 4 wires and 2x 4.7kΩ pull-up resistors.

## Wiring

The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and digital pin 3 (i.e.
PD0 on the ATmega32u4) between the two Pro Micros.

Next, wire your key matrix to any of the remaining 17 IO pins of the pro micro
and modify the `matrix.c` accordingly.

The wiring for serial:

![serial wiring](https://i.imgur.com/C3D1GAQ.png)

The wiring for i2c:

![i2c wiring](https://i.imgur.com/Hbzhc6E.png)

The pull-up resistors may be placed on either half. It is also possible
to use 4 resistors and have the pull-ups in both halves, but this is
unnecessary in simple use cases.

You can change your configuration between serial and i2c by modifying your `config.h` file. [Split Keyboard documentation](https://docs.qmk.fm/#/feature_split_keyboard)

## Optional Hardware

A speaker can be hooked-up to either side to the `5` (`C6`) pin and `GND`, and turned on via `AUDIO_ENABLE`.

## Non-Pro Micro Controller Compilation

If building a Dactyl Manuform with a controller that isn't a pro micro, the Converter feature of QMK will allow compilation of firmware for the intended variant and supported controller without having to create a new QMK keyboard/keymap.  
Please see [Converters documentation](https://docs.qmk.fm/#/feature_converters?id=supported-converters) for list of controllers that are supported converting from `promicro` and conversion implementation.

## Flashing

To flash your firmware take a look at: [Flashing Instructions and Bootloader Information](https://docs.qmk.fm/#/flashing)

## Choosing which board to plug the USB cable into (choosing Master)

Because the two boards are identical, the firmware has logic to differentiate the left and right board.

It uses two strategies to figure things out: looking at the EEPROM (memory on the chip) or looking if the current board has the usb cable.

The EEPROM approach requires additional setup (flashing the eeprom) but allows you to swap the usb cable to either side.

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
make handwired/dactyl_promicro:default:dfu-split-left
make handwired/dactyl_promicro:default:dfu-split-right
```

After you have flashed the EEPROM, you then need to set `EE_HANDS` in your config.h, rebuild the hex files and reflash.

Note that you need to program both halves, but you have the option of using
different keymaps for each half. You could program the left half with a QWERTY
layout and the right half with a Colemak layout using bootmagic's default layout option.
Then if you connect the left half to a computer by USB the keyboard will use QWERTY and Colemak when the
right half is connected.

## Notes on Using Pro Micro 3.3V

Do update the `F_CPU` parameter in `rules.mk` to `8000000` which reflects
the frequency on the 3.3V board.

Also, if the slave board is producing weird characters in certain columns,
update the following line in `matrix.c` to the following:

```
// wait_us(30);  // without this wait read unstable value.
wait_us(300);  // without this wait read unstable value.
```