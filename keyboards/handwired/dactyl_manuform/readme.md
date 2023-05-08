# Dactyl ManuForm

![Imgur](https://i.imgur.com/7y0Vbyd.jpg)
*Pair of Dactyl Manuform 4x6*

Forked from the [Dactyl](/keyboards/handwired/dactyl), the [Dactyl-ManuForm](https://github.com/tshort/dactyl-keyboard) is a parameterized, handwired, split bodied, tented, concave key-well design that incorporates the thumb cluster from the [ManuForm](https://geekhack.org/index.php?topic=46015.0). Bill of Materials (BoM), case files, and wiring guide for making this keyboard is in the second link.

## Variants

*Dactyl ManuForm's* are built in variations that cater for different row and column counts, and thumb clusters.  

As standard: 
- The finger keywell bottom row has 2 keys, 1 each in ring and middle columns
    - Exception to this rule is the `5x7` variant - that has two additional keys, per half, in this row
- The thumb cluster has 6 keys, arranged in a staggered 2 columns by 3 rows 

Variants are denoted as `RowCount`*x*`ColumnCount`*(_`Alteration`)*

### Row
| Count | Description |
| :---: | :---: |
| 4 | Three rows, typically for alphabet and some puncuation characters, with 2 key (finger keywell) bottom row |
| 5 | As *4 row* with number row above |
| 6 | As *5 row* with function row above |

### Column
| Count | Description |
| :---: | :---: |
| 5 | A column for each finger with additional column for first finger |  
| 6 | As *5 column* with additional pinky finger column |
| 7 | As *6 column* with either an additional first finger column (`5x7`) or additional pinky column (`6x7`) |  

### Alteration
| Code | Description |
| :---: | :---: |
| 3 | Default thumb cluster replaced with three key thumb cluster of [Dactyl Manuform Tight](https://github.com/okke-formsma/dactyl-manuform-tight) |
| 5 | Default thumb cluster replaced with five key thumb cluster of [Dactyl Manuform Mini](https://github.com/l4u/dactyl-manuform-mini-keyboard) | 
| 2_5 | Same as code *5* with two additional keys added to finger key-well bottom row |
| kinesis | Thumb cluster keys are arranged to resemble the Kinesis Advantage keyboard thumb cluster |

## First Time Setup

Download or clone the `qmk/qmk_firmware` repo and navigate to its top level directory. Once your build environment is setup, you'll be able to compile a firmware file.

 `qmk compile -kb handwired/dactyl_manuform/`*variant*` -kb `*keymap*`

Example:
```
qmk compile -kb handwired/dactyl_manuform/4x6 -km default
```
If everything worked correctly you will see a file named, in the case of the above example:
```
handwired_dactyl_manuform_4x6_default.hex
```

## Keymaps

### Default

The default functional layout, based on QWERTY, and every variant has this keymap; used as a starting point/template for custom keymaps and for debugging purposes when soldering key matrix to controller.

### VIA
Similar to *Default* but adds support for the [VIA](https://usevia.app/) keymap configurator. Layers count set to 4 to comply with VIA defaults, and remaps keys to accommodate this constraint, if applicable.

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

### Custom Keymaps

For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/docs/faq_keymap.md) in the main readme.md.

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

The wiring for serial:

![serial wiring](https://i.imgur.com/C3D1GAQ.png)

The wiring for i2c:

![i2c wiring](https://i.imgur.com/Hbzhc6E.png)

The pull-up resistors may be placed on either half. It is also possible
to use 4 resistors and have the pull-ups in both halves, but this is
unnecessary in simple use cases.

You can change your configuration between serial and i2c by modifying your `config.h` file. [Split Keyboard documentation](https://docs.qmk.fm/#/feature_split_keyboard).

Next, wire the switch matrix in sequence as specified by the chosen variant's column and row definitions.

## Optional Hardware

A speaker can be hooked-up to either side to the `5` (`C6`) pin and `GND`, and turned on via `AUDIO_ENABLE`.

## Non-Pro Micro Controller Compilation

If building a Dactyl Manuform with controllers that aren't a pro micro, the Converter feature of QMK will allow compilation of firmware for the intended variant and supported controller without having to create a new QMK keyboard/keymap.  
Please see [Converters documentation](https://docs.qmk.fm/#/feature_converters?id=supported-converters) for list of controllers that are supported converting from `promicro` and conversion implementation.

## Flashing

To flash your board with generated firmware file, please see [Flashing Instructions and Bootloader Information](https://docs.qmk.fm/#/flashing)

## Choosing which half to plug host cable

Because the two halves are identical, the firmware has logic to differentiate.  
It uses two strategies to figure things out: Checking EEPROM or has defined which half the host cable should be plugged into.

The EEPROM approach requires additional setup but allows you to swap the host cable to either half.

Half defined approach is easier to setup and if you just want the host cable on the left half, you do not need any additional configuration.

### Setting left half as master

If you always plug the host cable into the left half, nothing extra is needed as this is the default. Comment out in `config.h` file `EE_HANDS`, `I2C_MASTER_RIGHT`, and `MASTER_RIGHT` if for some reason they are defined.

### Setting right half as master

If you always plug the host cable into the right half, add the following into the respective variant's `config.h` file:

```
 #define MASTER_RIGHT
```

### Setting EE_hands to use either half as master

You will need to flash the EEPROM for the left and right halves.

The EEPROM in each half is flashed to code, into controller, their half designation.
This requires a firmware file compiled and flashed for each half.

To flash the EEPROM file for the **left** half, run:

```
make handwired/dactyl_promicro:default:dfu-split-left
```
For the **right** half, run:
```
make handwired/dactyl_promicro:default:dfu-split-right
```

After you have flashed the EEPROM for both havles, you then need to set EE_HANDS in `config.h` file,
```
#define EE_HANDS
```
re-compile the firmware (.hex) file as normal, and flash board as normal.

### Handedness configurations

See [Handedness](https://docs.qmk.fm/#/config_options?id=setting-handedness) documentation for more information on configuring handedness.

## VIA Configuration 

Variants with a `via` keymap are VIA capable. 
Compile firmware, for capable variant, with it's `via` keymap and flash board with this firmware file.
```
qmk compile -kb handwired/dactyl_manuform/4x6 -km via
```
