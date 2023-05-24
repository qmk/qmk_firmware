# Jpe230's CRKBD Layout

## Layers
The four layers:
- BASE Layer: QWERTY
- LOWER Layer: Numbers + Arrows
- RAISE Layer: Symbols
- ADJUST Layer: Numpad + Media Keys + Fn keys

## OLED
-Master: Renders layer state + keylog
-Slave : Renders an animation of a cat that varies its animation speed based on the current WPM

## Flashing
Flash using `qmk compile -kb crkbd -km jpe230` for Pro Micro
