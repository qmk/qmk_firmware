# Encoders

Basic encoders are supported by adding this to your `rules.mk`:

```make
ENCODER_ENABLE = yes
```

and this to your `config.h`:

```c
#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }
```

Each PAD_A/B variable defines an array so multiple encoders can be defined, e.g.:

```c
#define ENCODERS_PAD_A { encoder1a, encoder2a }
#define ENCODERS_PAD_B { encoder1b, encoder2b }
```

If your encoder's clockwise directions are incorrect, you can swap the A & B pad definitions.  They can also be flipped with a define:

```c
#define ENCODER_DIRECTION_FLIP
```

Additionally, the resolution, which defines how many pulses the encoder registers between each detent, can be defined with:

```c
#define ENCODER_RESOLUTION 4
```

It can also be defined per-encoder, by instead defining:

```c
#define ENCODER_RESOLUTIONS { 4, 2 }
```

## Split Keyboards

The above is enough for split keyboards that are symmetrical, i.e. the halves have the same number of encoders and they are on the same pins.
If the halves are not symmetrical, you can define the pinout (and optionally, resolutions) of the right half separately.
The left half will use the definitions above.

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
#define ENCODER_RESOLUTIONS_RIGHT { 2, 4 }
```

If only the right half has encoders, you must still define an empty array for the left pads (and resolutions, if you define `ENCODER_RESOLUTIONS_RIGHT`).

```c
#define ENCODERS_PAD_A {  }
#define ENCODERS_PAD_B {  }
#define ENCODER_RESOLUTIONS {  }
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
#define ENCODER_RESOLUTIONS_RIGHT { 2, 4 }
```

## Callbacks

The callback functions can be inserted into your `<keyboard>.c`:

```c
void encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}
```

or `keymap.c`:

```c
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}
```

## Hardware

The A an B lines of the encoders should be wired directly to the MCU, and the C/common lines should be wired to ground.
