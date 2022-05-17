# Endgame48

![Endgame48](https://i.imgur.com/asU6f9G.jpeg)

Puchi-C based 40% keyboard with rotary encoder and I2C OLED.

* Keyboard Maintainer: Andrew Dunai
* Hardware Supported: Puchi-C handwired
* Hardware Availability: [Keycapsss.com](https://keycapsss.com)


Make example for this keyboard (after setting up your build environment):

    make handwired/endgame48:default:dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Details

- Puchi-C based handwired keyboard
- 2x custom 1.25mm stainless steel plates
- Kailh Choc White (clicky)
- Rotary encoder
- 0.91" 128x32 I<sup>2</sup>C OLED
- WS2812 strip (12 LEDs)
- OLED menu (triggered with encoder press) which allows you to view EEPROM, reset keyboard, toggle RGB, etc.
- Handwiring is fun!

## Pinout

`PS2D` and `PS2C` are PS/2 `DATA` & `CLOCK` lines. They are not used in this revision but are reserved for future.

```
                 ┌────────┐
          ╭──────┤        ├──────╮
     RGB> ┿ D3   │        │  RAW ┿
          │      │        │      │
    PS2D> ┿ D2   └────────┘  GND ┿
          │                      │
          ┿ GND              RST ┿
          │      []      []      │
          ┿ GND              VCC ┿
          │                      │
     I2C> ┿ D1   ||| ||  ||   F4 ┿ <ROW5
          │                      │
     I2C> ┿ D0                F5 ┿ <COL1
          │          ╱╲          │
    ROW1> ┿ D4      ╱  ╲      F6 ┿ <COL2
          │        ╱    ╲        │
    ROW3> ┿ C6     ╲    ╱     F7 ┿ <COL3
          │         ╲  ╱         │
    COL7> ┿ D7       ╲╱       B1 ┿ <COL4
          │                      │
    ENCA> ┿ E6                B3 ┿ <COL5
          │                      │
    ENCB> ┿ B4                B2 ┿ <COL6
          │                      │
    ROW2> │ B5 B7 D5 C7 F1 F0 B6 ┿ <ROW6
          ╰────╂──╂──╂──╂──╂─────╯
               ┃  ┃     ┃  ┃
          ROW4 ┛  ┃     ┃  ┗ ROW8
                  ┃     ┃
             PS2C ┛     ┗ ROW7
```
