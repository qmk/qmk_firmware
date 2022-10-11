# Jpe230's CRKBD Layout

## Layers
The four layers:
- BASE Layer: QWERTY
- LOWER Layer: Numbers + Arrows
- RAISE Layer: Symbols
- ADJUST Layer: Numpad + Media Keys + Fn keys
## OLED
The graphics for the OLED varies depending on the target platform:

| Half   | RP2040                               | Pro Micro                            |
|--------|--------------------------------------|--------------------------------------|
| Master | ![](https://i.imgur.com/FF0EuWoh.png) | ![](https://i.imgur.com/stxRevvh.png) |
| Slave  | ![](https://i.imgur.com/hyjdDITh.png) | ![](https://i.imgur.com/UrTCd2sh.png) |


## Flashing
For Arduino Pro Micro:
- `qmk compile -kb crkbd -km jpe230`

For Pro Micro Compatible board (See [Converters](https://docs.qmk.fm/#/feature_converters?id=converters)):
- `qmk compile -kb crkbd -km jpe230 -e CONVERT_TO<target>`
