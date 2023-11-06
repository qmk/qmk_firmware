# Bluetreus - a conversion of an Atreus to use a Bluetooth microcontroller

I have created a keymap for this with Bluetooth control on layer 2 so that you
can switch the keyboard between auto, USB only, and Bluetooth only.  I'm
working on fixing turning on auto by default, but have still not succeeded.

To build it and flash it, do:

```
make atreus/feather:clash:flash
```

## Wiring it up
Physically, SDA to pin 13 on the new board are connected to what 9-1 were
connected to on the old board.  Pin 0 from the old board is brought over to the
other side with a jumper wire to pin a2. TX, RX, A5, A4, A3 on the new board
connect to what a0 to 12 connected to on the old board. GND attaches to g.
You have to bend some of the pins at about a 45 degree angle to make them line up.
Here's a side view of what the most bent pins look like:
![Side View](https://i.imgur.com/S6ngibe.jpg)
Here's a top view, USB port down, wireless antenna up. Note: the USB port orientation is opposite what it used to be.
![Top View](https://i.imgur.com/DBjkxU2.jpg)

### New board:
This is an [Adafruit Feather BLE](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/pinouts)

|QMK | Screen Print | Feather     |SCREEN|QMK REF  |
|----|--------------|-------------|------|---------|
| D1 | SDA          | RADIO       | dfu  |         |
| D0 | SCL          |             | 1/TX | D3      |
| C6 | 5            |             | 0/RX | D2      |
| D7 | 6            |             | MISO | B3/Blue |
| B5 | 9            |             | MOSI | B2/Blue |
| B6 | 10           |             | SCK  | B1/Blue |
| B7 | 11           |             | A5   | F0      |
| D6 | 12           |             | a4   | F1      |
| C7 | 13           |             | a3   | F4      |
|    | usb          |             | a2   | F5      |
|    | e0           |             | a1   | F6      |
|    | bat          |             | a0   |         |
|    | Battery      |             | GND  |         |
|    | Connector    |             | ARf  |         |
|    |  |    |      | USB PORT    | 3V   |         |
|    |  v    v      |             | RST  |         |

### Old board:
This is an A Star, non-flipped

|QMK| Scrn | A   | Scrn|QMK |
|---|------|-----|-----|----|
| b5| 9    | USB | a0  | F7 |
| b4| 8    | port| a1  | F6 |
| e6| 7    |     | 10  | B6 |
| d7| 6    |     | 11  | B7 |
| c6| 5    |     | 12  | D6 |
| d4| 4    |     | rst | RST|
| d0| 3    |     | 3v  | x  |
| d1| 2    |     | 5v  | x  |
| d3| 1    |     | g   | G  |
| d2| 0    |     | v   | x  |
