# GMMK Numpad macOS keymap

A keymap for the GMMK Numpad tailored for use on macOS.

## Changes from default

- `KC_CALC` is replaced with `KC_MUTE`, since the calculator key doesn't have
  a useful action on macOS.
- The potentiometer slider now auto-calibrates itself. It tracks the minimum
  and maximum raw ADC readings it has seen and scales the output so it can
  reliably reach both 0 and 127, instead of relying on fixed raw ADC bounds
  that didn't match the slider's real electrical range. A small hysteresis
  threshold also filters out ADC noise so the value doesn't jitter when the
  slider is left still.

## Layers

- `_BASE`: the default numpad layout, with `MUTE` in place of the stock
  `CALC` key.
- `_FN`: accessed by holding the `NUM` key. Provides RGB controls
  (`RM_TOGG`, `RM_PREV`/`RM_NEXT`, `RM_VALU`/`RM_VALD`) and `QK_BOOT` for
  entering the bootloader.

## Slider / MIDI

The slider sends MIDI CC messages (channel 2, controller `0x3E`) with a
value from 0-127, scaled from the observed ADC range rather than a fixed
one. This is useful for mapping the slider to a fader or parameter in a DAW
or other MIDI-aware application.
