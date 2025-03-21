# Teensy LC onekey

To trigger keypress, short together pins *D5* and *B2* (marked on the PCB as *20* and *19*).

## Hardware

### Pins
When setting matrix pins, you need to use the MCU definitions instead of what is printed on the PCB. Sourced from <https://www.pjrc.com/teensy/schematic_lc.gif>. The following table can be used to convert between the two.

|  PCB   | MCU | Notes |
|------- |-----|-------|
| 0      | B16 |       |
| 1      | B17 |       |
| 2      | D0  |       |
| 3      | A1  |       |
| 4      | A2  |       |
| 5      | D7  |       |
| 6      | D4  |       |
| 7      | D2  |       |
| 8      | D3  |       |
| 9      | C3  |       |
| 10     | C4  |       |
| 11     | C6  |       |
| 12     | C7  |       |
| 13/LED | C5  |       |
| 14/A0  | D1  |       |
| 15/A1  | C0  |       |
| 16/A2  | B0  |       |
| 17/A3  | B1  |       |
| 18/A4  | B3  |       |
| 19/A5  | B2  |       |
| 20/A6  | D5  |       |
| 21/A7  | D6  |       |
| 22/A8  | C1  |       |
| 23/A9  | C2  |       |
| 24/A10 | E20 |       |
| 25/A11 | E21 |       |
| 26/A12 | E30 |       |