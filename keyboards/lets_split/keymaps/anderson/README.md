# Stuff for my "Let's Split"

Featuring:

- Custom highlights (including custom knight-rider-like one which I've named DMC-12 by mistake.)
- `LOW_ESC` key (LOWER on hold, ESC on tap.)
- Rotary encoder knob for horizontal/vertical scrolling & volume control.

# Knob inscructions

**Important:** disable KNOB_ENABLED in `config.h` when flashing the right split (or simply do not use `knob_*` functions for right split.)

## V1 (deprecated, see V2)

I've used pins 4 & 5 (PD4 & PC6) to read digital value from the rotary encoder because Let's Split doesn't use them (Split keyboards FTW! Moar precious free pins!)

See `knob.c` for implementation & usage info.

**Note:** If you scroll too fast, the scroll becomes laggy. Unfortunately there's no way to deal with this as `matrix_scan_user` isn't called frequently enough and some signals from encoder are simply lost.

## V2

This method uses pins PD1 (2) & PD4 (4).

Seems like port PD4 has an ADC (ADC8) attached! I've added a `knob_v2` that does this, but uses port PD1 (pin 2).

# Schematics

![Knob layout](./encoder.png)

