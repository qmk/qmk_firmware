# QMK Keyboard Firmware for HHKB

Run the following from the QMK firmware project root:

    $ make hhkb-cinaeco-dfu

## Modifications

### HHKB Fn Layer

Added some Media keys.

### Utility Layer (SpaceFN)

Hold `Space` for:

- Vi-style direction keys.
- WASD-style mouse keys.
- Dynamic macro playback on `1` and `2`.
- Layout selection on `-`, `=` and `\`(Qwerty/Colemak/Dvorak)

### Dynamic Macros

Hold `q` and press:

- `1` or `2` to record macro 1 or 2.
- `s` to stop recording.
