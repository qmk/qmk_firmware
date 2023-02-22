# Viet's Kinesis + Pro Micro

July 2020

This work is inspired by `alvicstep`'s solution. Instead of hooking up the Kinesis to a Teensy 2, this one hooks it up to a Pro Micro.

## Kinesis Board Layout
The following is a reinterpretation of [@chrisandreae](https://github.com/chrisandreae/keyboard-firmware/blob/public/hardware/kinesis.h)'s work.

### Used Pins
* 8 columns mapped to output pins 21 - 28
* 16 rows mapped to 4 input pins: pin 39 - 36. Rows are traversed by iterating and setting 16 values from 0000 to 1111. 
* 4 leds (e.g. capslock) mapped to input pin 1 - 4
* keypad key mapped to pin 5
* program key mapped to pin 6
* `VCC` mapped to pin 40

### Matrix Configuration
The matrix configuration of the columns and rows on my Advantage is as follows:

|        | row 0  | row 1  | row 2  | row 3  | row 4  | row 5  | row 6  | row 7  | row 8  | row 9  | row A  | row B  | row C  | row D  | row E  | row F |
|  ----- | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | -----  | ----- |
|  col0  | F6     | F8     | F7     | 5%     | 4$     | 3#     | 2@     | 1!     | =+     |        |        |        |        |        |        |       |
|  col1  | F3     | F5     | F4     | T      | R      | E      | W      | Q      | Tab    |        |        |        |        |        |        |       |
|  col2  | Esc    | F2     | F1     | G      | F      | D      | S      | A      | CapsLk |        |        |        |        |        |        |       |
|  col3  | F9     | F11    | F10    | B      | V      | C      | X      | Z      | LShift | Up     |        | Down   |        | [{     | ]}     |       |
|  col4  | F12    | ScrLk  | PrtSc  | Right  |        | Left   | Insert | ~      |        | 6^     | 7&     | 8*     |        | 9(     | 0)     | -_    |
|  col5  | Pause  |        |        | LAlt   |        | Home   |        | End    |        | Y      | U      | I      |        | O      | P      | `\|`  |
|  col6  |        |        |        | LCtrl  | Delete | Bksp   | RCtrl  | Enter  | Space  | H      | J      | K      |        | L      | ;:     | '"    |
|  col7  |        |        |        |        | RGUI   |        | PageUp |        | PageDn | N      | M      | ,<     |        | .>     | /?     | RShift |

(this is a modified copy from [@alvicstep](https://github.com/qmk/qmk_firmware/blob/master/keyboards/kinesis/alvicstep/alvicstep.h))

In the code, keypad and program keys are mapped respectively to col0 and col1 of row C, the 12th row.  

### Omitted Pins
There are pins that we currently omit:
* serial eeprom clock line mapped to pin 7
* serial eeprom data line mapped to pin 8
* EEPROM write protect mapped to pin 10.
* foot switch 1 mapped to pin 11 
* PS/2 clock mapped to pin 12
* PS/2 data mapped to pin 13
* foot switch 2 mapped to pin 17
* foot switch 3 mapped to pin 15
* audio mapped to pin 32

### DIP Socket
Here's an ASCII drawing of the 40 pin DIP socket. 
```
   DL2   1  40  VCC
   DR1   2  39  A
   DR2   3  38  B
   DL1   4  37  C
   KPD   5  36  G
   PGM   6  35
   SCL   7  34
   SDA   8  33
   RST   9  32  BUZZ
    WP  10  31  EA
   FS1  11  30  ALE
 CLOCK  12  29  PSEN
  DATA  13  28  r8
        14  27  r7
   FS3  15  26  r6
        16  25  r5
   FS2  17  24  r4
 XTAL1  18  23  r3
 XTAL2  19  22  r2
   GND  20  21  r1
```
(this is copied from [@wjanssens](https://raw.githubusercontent.com/wjanssens/tmk_keyboard/master/keyboard/kinesis/doc/readme.txt))

## Pin Mapping to Pro Micro

The following table is ordered by physical Arduino pin order.

| Arduino | Kinesis | Meaning |
| ------- | ------- | ------- |
| D3      | 36      | G       |
| D2      | 37      | C       |
| GND     |         |         |
| GND     |         |         |
| D1      | 38      | B       |
| D0      | 39      | A       |
| D4      | 1       | DL2     |
| C6      | 2       | DR1     |
| D7      | 3       | DR2     |
| E6      | 4       | DL1     |
| B4      | 5       | KPD     |
| B5      | 6       | PGM     |
| B6      | 21      | r1      |
| B2      | 22      | r2      |
| B3      | 23      | r3      |
| B1      | 24      | r4      |
| F7      | 25      | r5      |
| F6      | 26      | r6      |
| F5      | 27      | r7      |
| F4      | 28      | r8      |
| VCC     | 40      |         |
| RESET   |         |         |
| GND     | 20      |         |
| RAW     |         |         |

## Notes

* The rows are multiplexed. Instead of reading them out, one sets the row value and corresponding column values are returned through r1-r8.
* On my keyboard, the keypad and program key have dedicated pins. Since row 12 had no mapping in the physical matrix, there's a code override injects the keypad and program pins to the first two bits in the matrix.
* I've experimented with debouncing approaches. The current setting delivers a snappier feeling than Kinesis's factory default for me.
