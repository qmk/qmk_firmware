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

If you are using different pinouts for the encoders on each half of a split keyboard, you can define the pinout (and optionally, resolutions) for the right half like this:

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
#define ENCODER_RESOLUTIONS_RIGHT { 2, 4 }
```

## Configuring Input Pins

Rarely, you may want to set the MCU pin hooked up to the encoder to use its internal pull-down or be left floating, instead of the default which is to use an internal pull-up. This is mainly relevant for non-mechanical encoders, such as optical or hall effect. These options can be configured by placing these `#define`s in your `config.h`:

|Define         |Description                                                                                              |
|---------------|---------------------------------------------------------------------------------------------------------|
|`ENC_PUP`      |Toggles on the internal pull-up                                                                          |
|`ENC_PDOWN `   |Toggles on the internal pull-down                                                                        |
|`ENC_FLOAT`    |Leaves the pin as floating                                                                               |

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
