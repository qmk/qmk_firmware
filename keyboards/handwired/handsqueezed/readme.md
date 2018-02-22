<img align="right" src="https://i.imgur.com/swEUv9K.png" width="36px" />

# Hand-squeezed

Hand-wired Planck with Bluetooth squeezed into official OLKB [high profile wood case](https://olkb.com/planck/hi-pro-wooden-milled-bottom). The keyboard is also, *ahem*, squeezed onto as few pins as possible using a 6x8 matrix instead of the typical 4x12.

**Keyboard Maintainer:** Jamie Rolfs / [gh](https://github.com/jrolfs) / [site](https://jamie.rolfs.sh)

**Hardware Supported**: [Feather 32u4 Bluefruit](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/) 

## Wiring

```

                ┌────┬─────┬────┐
                │ ◯  └─────┘ ◯  │
                │ ⚬ RST         │
                │ ⚬ 3V     ┌────┤
                │ ⚬ AREF   │    │
                │ ⚬ GND    └────┤
      {1}[F7] → │ ⚬ A0    BAT ⚬ │
      {2}[F6] → │ ⚬ A1    LED ⚬ │
      {3}[F5] → │ ⚬ A2    USB ⚬ │
      {4}[F4] → │ ⚬ A3     13 ⚬ │ ← [C7](4)
      {5}[F1] → │ ⚬ A4     12 ⚬ │ ← [D6](8)
      {6}[F0] → │ ⚬ A5     11 ⚬ │ ← [B7](3)
                │ ⚬ SCK    10 ⚬ │ ← [B6](7)
                │ ⚬ MOSI    9 ⚬ │
                │ ⚬ MISO    6 ⚬ │ ← [D7](6)
                │ ⚬ RX ────┐5 ⚬ │ ← [C6](2)
                │ ⚬ TX    SCL ⚬ │ ← [D0](5)
                │ ⚬ DFU   SDA ⚬ │ ← [D1](1)
                │ ◯  │─────│ ◯  │
                └────┴─────┴────┘


          [F7] [F6] [F5] [F4] [F1] [F0]
          {01} {02} {03} {04} {05} {06}
         ┌────┬────┬────┬────┬────┬────┐
  [D1](1)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [C6](2)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [B7](3)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [C7](4)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [D0](5)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [D7](6)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [B6](7)│    │    │    │    │    │    │
         ├────┼────┼────┼────┼────┼────┤
  [D6](8)│    │    │    │    │    │    │
         └────┴────┴────┴────┴────┴────┘

```
