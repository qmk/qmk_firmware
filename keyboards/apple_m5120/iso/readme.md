# Apple M5120 with Teensy   

Old Apple keyboard from Apple Macintosh M5120 laptop with Teensy controller.

Some technicals details about Wiring:

Original Pinout:
| 2   | 4  | 6  | 8  | 10 | 12  | 14 | 16 |   18   | 20 | 22   | 24   | 26  | 28  | 30  | 32  | 34  |
|-----|----|----|----|----|-----|----|----|--------|----|------|------|-----|-----|-----|-----|-----|
| X0  | X2 | X4 | X6 | X8 | X10 | Y1 | Y3 |   Y5   | Y7 | SHFT | OPT  | GND | VCC | BTN | ID2 | GND |
| GND | X1 | X3 | X5 | X7 | X9  | Y0 | Y2 |   Y4   | Y6 | CAPS | CTRL | CMD | GND | FBD | ID1 |     |
|     |    |    |    |    |     |    |    | _MARK_ |    |      |      |     |     |     |     |     |

Keys placement:
|    | X0 | X1 | X2 | X3 | X4 | X5 | X6 | X7 | X8 | X9 | X10 |
|----|----|----|----|----|----|----|----|----|----|----|-----|
| Y0 |    |    |    |    |    |    | 1  | 5  | 6  | 7  | 13  |
| Y1 |    |    |    |    |    |    | 2  | 57 | 20 | 8  | 12  |
| Y2 |    |    |    |    |    |    | 3  | 34 | 21 | 9  | 11  |
| Y3 |    |    |    |    |    |    | 4  | 28 | 26 | 10 | 24  |
| Y4 | 15 | 16 | 17 | 18 | 19 | 59 | 23 | 37 | 25 | 27 |     |
| Y5 | 60 |    | 63 | 32 | 61 | 22 | 14 | 38 | 39 | 40 | 41  |
| Y6 | 30 | 31 | 62 |    | 33 | 47 | 35 | 36 | 50 | 52 | 51  |
| Y7 |    | 43 | 44 | 45 | 46 | 58 |    | 48 | 49 |    |     |

Keys placement: http://www.keyboard-layout-editor.com/#/gists/8187745cf7d43ac8b80211c1d8074b8e

On J2 connector I have connected some pins togheter:

* CAPS_LOCK <=> Y0
* CONTROL <=> Y1
* COMMAND <=> Y2
* SHIFT <=> Y3
* OPTION <=> Y4

Both shift are wired on the same Col/Row.

34Pin <=> Teensy
* Y0: F0
* Y1: F1
* Y2: F4
* Y3: F5
* Y4: F6
* Y5: F7
* Y6: B6
* Y7: B5
* X0: B0
* X1: B1
* X2: B2
* X3: B3
* X4: B7
* X5: D0
* X6: D1
* X7: D2
* X8: D3
* X9: C6
* X10: C7
* GND (pin 26): D5
