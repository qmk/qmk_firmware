# The Dora Board

This keyboard was built for QMK exploration big and small. What will you discover next?

![The Dora Board](https://ckeys.org/images/exboard-3.jpg)

## Slides

Slides can be found at: https://ckeys.org/slides/exboard/

## Case Design

The acrylic laser cutter file is coming soon!

## PCB Design

All cKeys PCBs are open source. However, this one has not been posted yet because it needs to be cleaned up a bit! Coming soon!

## Firmware

If you want to reflash the pre-installed firmware, use the `.bin` file for Proton C. Flash with the QMK Toolbox or via the command line.

Building for Proton C: `make ckeys/thedora:default`

## Default Layout

You can find the default layout in `thedora/keymaps/default/keymap.c`

## Rotary Encoder

This is the bit of code at the end of `keymap.c` that needs to changed if you want to change the behavior of the rotary encoder.

```
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_PGDN); // What the rotary encoder repeatedly does when turned right.
    } else {
      tap_code(KC_PGUP); // What it does when turned to the left.
    }
  }
}
```

![The Dora Board](https://ckeys.org/images/exboard-1.jpg)
